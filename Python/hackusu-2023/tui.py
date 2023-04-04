#!/usr/bin/python3
import sys
import os
from game import Game
from getch import getch

def send_command(game, ch):
    cmd = {
            'w': "UP",
            'a': "LEFT",
            's': "DOWN",
            'd': "RIGHT",
            'u': "USE",
            'r': "REMOVE"
          }
    ret = True
    if ch in cmd:
        cmdword = cmd[ch]
        if cmdword == "USE" or cmdword == "REMOVE":
            inv = game.getStats()['inv']
            print(f"What shall we {cmdword} (1-{len(inv)})? ", end='')
            sys.stdout.flush()
            try:
                inum = int(getch())
            except:
                inum = 0
            if inum < 1 or inum > len(inv):
                return
            cmdword += ' ' + str(inum)
        ret = game.sendCommand(cmdword)

    return ret

def play_step(game):
    board = game.getBoard()
    os.system('clear')
    for line in board:
        print(line)
    print(game.getMessages())
    stats = game.getStats()
    print(f"HP: {stats['hp']:.1f}, Str: {stats['str']:.0f}, Dex: {stats['dex']:.0f}, Wis: {stats['wis']:.0f}, Exp: {stats['exp']:.0f}")
    inv = ''
    for i in range(len(stats['inv'])):
        item = stats['inv'][i]
        if len(inv) > 0:
            inv += ', '
        inv += f'{i + 1}:{item}'
    print(f'Inventory: {inv}')
    print("Whatcha wanna do? ", end = "")
    sys.stdout.flush()
    ch = getch()
    print(ch)
    if ch == 'q':
        print("See ya!")
        return False
    return send_command(game, ch)

def run_game():
    game = Game()
    while play_step(game):
        pass

if __name__ == '__main__':
    run_game()
