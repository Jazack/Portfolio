import room
import creatures
import random

def setCharAt(board, x, y, ch):
    line = board[y + 1]
    line = line[:x + 1] + ch + line[x + 2:]
    board[y + 1] = line

def breakAt(string, length):
    ret = []
    while len(string) > length:
        br = length
        while string[br] not in ' ':
            br -= 1
        ret.append(string[:br])
        string = string[br+1:]
    ret.append(string)
    return ret

class Game:
    def __init__(self):
        self.pc = creatures.pc()
        self.room = room.room(self.pc)
        self.event = {}
        self.event['error'] = ''
        self.event['pillar'] = False
        self.event['mondmg'] = 0
        self.event['mondead'] = False
        self.event['itemname'] = ''
        self.event['used'] = ''
        self.event['burdened'] = False
        self.event['died'] = False
        self.dir = '^'

    def getBoard(self):
        x = self.pc.x
        y = self.pc.y
        w = self.room.x
        h = self.room.y
        levelstr = f'Level {self.room.getLevel()}'
        board = ['+=|' + levelstr + '|' + '=' * (w - len(levelstr) - 3) + '+'] + ['|' + ' ' * w + '|'] * h + ['+' + '=' * w + '+']
        for ob in self.room.getPillars():
            setCharAt(board, ob[0], ob[1], '*')
        for item in self.room.getItems():
            setCharAt(board, item.x, item.y, item.symbol)
        montypes = {'orc': '0', 'spider': 's', 'skeleton': 'k'}
        for mon in self.room.getMonsters():
            setCharAt(board, mon.x, mon.y, montypes[mon.getType()])
        if self.room.getEndCondition():
            exitPos = self.room.returnExit()
            setCharAt(board, exitPos[0], exitPos[1], '#')
        setCharAt(board, x, y, self.dir)
        return board

    def getMessages(self):
        msgs = ''
        if len(self.event['error']) > 0:
            msgs = f'ERROR: {self.event["error"]}'
        if self.event['pillar']:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += 'Ouch! You can\'t go that way!'
        if self.event['mondmg'] > 0:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += f'You attacked a {self.event["montype"]} for {self.event["mondmg"]} damage.'
            if self.event['mondead']:
                msgs += f' You destroyed the {self.event["montype"]}!'
        if len(self.event['itemname']) > 0:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += f'You picked up a {self.event["itemname"]}.'
        if len(self.event['used']) > 0:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += f'Just used a {self.event["used"]}.'
        if self.event['burdened']:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += f'You have too much stuff! Drink a potion, cast a spell, drop trash, something!'
        if self.event['died']:
            if(len(msgs) > 0):
                msgs += ' '
            msgs += 'You died. Yet the world continues. A new adventurer enters another dungeon'
        return msgs

    def sendCommand(self, cmd):
        self.event['error'] = ''
        self.event['pillar'] = False
        self.event['mondmg'] = 0
        self.event['mondead'] = False
        self.event['itemname'] = ''
        self.event['used'] = ''
        self.event['burdened'] = False
        self.event['died'] = False
        x = self.pc.x
        y = self.pc.y
        ox = x
        oy = y
        w = self.room.x
        h = self.room.y
        if len(cmd) > 4 and cmd[:4] == "USE ":
            diradj = {'^': [0 ,-1],
                      'v': [0 , 1],
                      '<': [-1, 0],
                      '>': [ 1, 0]}
            inum = int(cmd[4:])
            inv = self.pc.getInventory()
            if inum <= len(inv):
                self.event['used'] = inv[inum - 1].getName()
                dmg = inv[inum - 1].useItem(self.pc)
                if dmg > 0:
                    mx = x + diradj[self.dir][0]
                    my = y + diradj[self.dir][1]
                    for mon in self.room.getMonsters():
                        if mon.x == mx and mon.y == my:
                            self.event['mondmg'] = dmg
                            self.event['montype'] = mon.getType()
                            self.event['mondead'] = self.room.damageMonster(mon.getID(), dmg)
                            break
                if self.pc.getHP() < 0:
                    self.room.reset()
                    self.event['died'] = True

        if len(cmd) > 7 and cmd[:7] == "REMOVE ":
            inum = int(cmd[7:])
            inv = self.pc.getInventory()
            if(inum <= len(inv)):
                self.pc.removeInventory(inv[inum - 1])
        if cmd == "RIGHT" and x < w - 1:
            self.dir = '>'
            x += 1
        if cmd == "LEFT" and x > 0:
            self.dir = '<'
            x -= 1
        if cmd == "DOWN" and y < h - 1:
            self.dir = 'v'
            y += 1
        if cmd == "UP" and y > 0:
            self.dir = '^'
            y -= 1
        if self.room.getEndCondition():
            endPos = self.room.returnExit()
            if x == endPos[0] and y == endPos[1]:
                self.room.createNewRoom()
                return True
        for ob in self.room.getPillars():
            if ob[0] == x and ob[1] == y:
                x = ox
                y = oy
                self.event['pillar'] = True
                break
        for mon in self.room.getMonsters():
            if mon.x == x and mon.y == y:
                x = ox
                y = oy
                dmgToMon = self.pc.attack()
                self.event['mondmg'] = dmgToMon
                self.event['montype'] = mon.getType()
                self.event['mondead'] = self.room.damageMonster(mon.getID(), dmgToMon)
                break
        for item in self.room.getItems():
            if item.x == x and item.y == y:
                if len(self.pc.getInventory()) < 9:
                    self.room.pickupItem(x, y)
                    self.event['itemname'] = item.getName()
                else:
                    self.event['burdened'] = True
        self.pc.x = x
        self.pc.y = y
        if self.room.monstersTurn():
            self.room.reset()
            self.event['died'] = True
        return True
    def getStats(self):
        ret = {}
        ret['hp'] = self.pc.getHP()
        stat = self.pc.getStats()
        ret['str'] = stat[0]
        ret['dex'] = stat[1]
        ret['wis'] = stat[2]
        ret['exp'] = self.pc.exp
        ret['inv'] = [n.getName() for n in self.pc.getInventory()]
        wep = self.pc.getEquipped()
        ret['wep'] = wep.getName() if wep else "None"
        return ret
