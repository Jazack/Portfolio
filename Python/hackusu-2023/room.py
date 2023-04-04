'''
class for room

it will need:
x y sizes
pillar locations
monsters
pc
end condition
level
items
'''
import random
import creatures
import items
class room:
    __slots__ = ['x', 'y', 'pillars', 'pc', 'endCondition', 'monsters', 'level', 'items', 'exit']
    def __init__(self, pc):
        self.level = 0
        self.pc = pc
        self.createNewRoom()
    def createNewRoom(self):
        # set up room size and level
        self.x = random.randint(20, 35)
        self.y = random.randint(10, 15)
        # set up pillars
        create = random.randint(1,20)
        self.pillars = []
        for i in range(create):
            tempX = random.randint(1, self.x-1)
            tempY = random.randint(1, self.y-1)
            if [tempX,tempY] not in self.pillars:
                self.pillars.append([tempX, tempY])
        # set up player and location
        looking = True
        while (looking):
            tempX = random.randint(1, self.x-1)
            tempY = random.randint(1, self.y-1)
            if [tempX, tempY] not in self.pillars:
                looking = False
        self.pc.setX(tempX)
        self.pc.setY(tempY)
        # set up where to avoid
        avoid = self.pillars.copy()
        avoid.append([tempX, tempY])
        # set up end condition
        self.endCondition = False
        # set up monsters
        create = random.randint(1,10)
        created = 0
        self.monsters = []
        while (created < create):
            looking = True
            while (looking):
                tempX = random.randint(1, self.x-1)
                tempY = random.randint(1, self.y-1)
                if [tempX, tempY] not in avoid:
                    looking = False
                    avoid.append([tempX,tempY])
            mon = creatures.randomMonster(self.level, created, tempX, tempY)
            mon = mon.getStore()
            self.monsters.append(mon)
            created += 1
        # set up items
        ids = created
        create = random.randint(1,10)
        created = 0
        self.items = []
        while (created < create):
            looking = True
            while (looking):
                tempX = random.randint(1, self.x-1)
                tempY = random.randint(1, self.y-1)
                if [tempX, tempY] not in self.pillars:
                    looking = False
                    avoid.append([tempX,tempY])
            item = items.createItems(self.level, ids, tempX, tempY).getStore()
            self.items.append(item)
            created += 1
            ids += 1
        self.level += 1
        self.exit = False
    # getters and setters
    def getPillars(self):
        return self.pillars
    def getMonsters(self):
        return self.monsters
    def getItems(self):
        return self.items
    def getLevel(self):
        return self.level
    def getEndCondition(self):
        return self.endCondition
    def returnExit(self):
        return self.exit
    def setupExit(self):
        avoid = []
        avoid.append(self.pc.getPosition())
        avoid += self.pillars
        use = self.getItems()
        for i in use:
            avoid.append(i)
        looking = True
        while (looking):
            tempX = random.randint(1, self.x-1)
            tempY = random.randint(1, self.y-1)
            if [tempX, tempY] not in avoid:
                looking = False
                avoid.append([tempX,tempY])
                self.exit = [tempX,tempY]
    def removeMonster(self, monsterID):
        deleted = False
        for i in range(0,len(self.monsters)):
            if self.monsters[i].getID() == monsterID:
                deleted = True
                exp = self.monsters[i].getExp()
                self.pc.addExperience(exp)
                self.monsters.pop(i)
                break
        
        if len(self.monsters) <= 0:
            self.endCondition = True
            self.setupExit()
        return True
    def removeItem(self, itemID):
        deleted = False
        for i in range(0,len(self.items)):
            if self.items[i].getID() == itemID:
                deleted = True
                self.items.pop(i)
                break
        if not deleted:
            raise('ATTEMPTING TO REMOVE AN ITEM THAT DOES NOT EXIST')
        return True
    def damageMonster(self, monsterID, damage):
        for i in self.monsters:
            if i.id == monsterID:
                i.wound(damage)
                if i.getHP() <= 0:
                    self.removeMonster(monsterID)
                    return True
        return False
    def pickupItem(self, x, y):
        for i in self.items:
            if i.x == x and i.y == y:
                self.pc.addInventory(i)
                self.removeItem(i.getID())
                return True
        raise('ATTEMPTING TO PICK UP AN ITEM THAT DOES NOT EXIST')
    def monstersTurn(self):
        for mon in self.monsters:
            avoid = self.pillars.copy()
            for i in self.monsters:
                if i.getID() != mon.getID():
                     avoid.append(i.getPosition())
            # avoid is now set up
            moves = 0
            pcPos = self.pc.getPosition()
            while moves < mon.getMove():
                 monPos = mon.getPosition()
                 prev = monPos.copy()
                 if self.calcDistance([monPos[0],monPos[1]+1], pcPos) < self.calcDistance([monPos[0],monPos[1]-1], pcPos):
                     try1 = [monPos[0],monPos[1]-1]
                     try2 = [monPos[0],monPos[1]+1]
                 else:
                     try1 = [monPos[0],monPos[1]+1]
                     try2 = [monPos[0],monPos[1]-1]
                 if self.calcDistance([monPos[0]+1,monPos[1]], pcPos) < self.calcDistance([monPos[0]-1,monPos[1]], pcPos):
                     try3 = [monPos[0]-1,monPos[1]]
                     try4 = [monPos[0]+1,monPos[1]]
                 else:
                     try3 = [monPos[0]+1,monPos[1]]
                     try4 = [monPos[0]-1,monPos[1]]
                 if self.calcDistance(try1, pcPos) < self.calcDistance(try3, pcPos) and try1 not in avoid:
                     if try1[0] == pcPos[0] and try1[1] == pcPos[1]:
                          damage = mon.attack()
                          self.pc.wound(damage)
                          if self.pc.getHP() <= 0:
                               return True
                     else:
                          mon.setX(try1[0])
                          mon.setY(try1[1])
                 elif try3 not in avoid:
                     if try3[0] == pcPos[0] and try3[1] == pcPos[1]:
                          damage = mon.attack()
                          self.pc.wound(damage)
                          if self.pc.getHP() <= 0:
                               return True
                     else:
                          mon.setX(try3[0])
                          mon.setY(try3[1])
                 elif try1 not in avoid:
                     mon.setX(try1[0])
                     mon.setY(try1[1])
                 if self.calcDistance(try2, pcPos) < self.calcDistance(try4, pcPos) and try1 not in avoid:
                     mon.setX(try2[0])
                     mon.setY(try2[1])
                 elif try4 not in avoid:
                     mon.setX(try4[0])
                     mon.setY(try4[1])
                 elif try2 not in avoid:
                     mon.setX(try2[0])
                     mon.setY(try2[1])
                 moves += 1
            if self.calcDistance(pcPos, mon.getPosition()) == 0:
                 mon.setX(prev[0])
                 mon.setY(prev[1])
                 damage = mon.attack()
                 self.pc.wound(damage)
                 if self.pc.getHP() <= 0:
                     return True
        return False
    def calcDistance(self, loc1, loc2):
        return ((loc1[0]-loc2[0])**2 + (loc1[1]-loc2[1])**2)**(1/2)
    def reset(self):
        self.level = 0
        self.createNewRoom()
        self.pc.inventory = []
        self.pc.resetEquipped()
        self.pc.resetHealth()

