from pyscript import Element
from pyodide.ffi import create_proxy
from game import Game
from collections import Counter


def onKeyPress(event):
    event.preventDefault()
    send_command(gameObject, event.key) 



def send_command(game, ch):
    cmd = {
            'w': "UP",
            'a': "LEFT",
            's': "DOWN",
            'd': "RIGHT",
            'ArrowUp': "UP",
            'ArrowLeft': "LEFT",
            'ArrowDown': "DOWN",
            'ArrowRight': "RIGHT",
            'i': "INVENTORY",
            '1': "USE 1",
            '2': "USE 2",
            '3': "USE 3",
            '4': "USE 4",
            '5': "USE 5",
            '6': "USE 6",
            '7': "USE 7",
            '8': "USE 8",
            '9': "USE 9",
            '!': "REMOVE 1",
            '@': "REMOVE 2",
            '#': "REMOVE 3",
            '$': "REMOVE 4",
            '%': "REMOVE 5",
            '^': "REMOVE 6",
            '&': "REMOVE 7",
            '*': "REMOVE 8",
            '()': "REMOVE 9"
        }
    if ch in cmd:
        cmdword = cmd[ch]
        if cmdword == "INVENTORY":
            draw_messages(game, Element("console"), ch)
        elif cmdword[:-2] == "USE" or cmdword[:-2] == "REMOVE":
            commandString = cmdword
            game.sendCommand(commandString)
        else:
            game.sendCommand(cmdword)
        draw_board(game, Element("game-screen"))
        draw_stats(game, Element("stats"))
        draw_messages(game, Element("console"), ch)

def draw_board(game, window):
    board = game.getBoard()
    stringBoard = ""
    for line in board:
        stringBoard += "\n" + line
    window.write(stringBoard)

def draw_stats(game, window):
    playerStats = game.getStats()
    stringStats = ""
    for key in playerStats:
        value = playerStats[key]
        if key != "inv":
            stringStats += "\n" + key + " : " + str(value)
        else:
            stringStats += f"\n{key} : {len(value)} of 9"
    window.write(stringStats)

def draw_messages(game, window, ch):
    if ch != "i":
        messages = game.getMessages()
        window.write(messages)
    else:
        inv = game.getStats()["inv"]
        inventoryString = "Your Inventory\n"
        counter = 1
        for thing in inv:
            if counter <= 9:
                inventoryString += f"({counter}) {thing} | "
                counter += 1
        # inventoryDict = Counter(inv)
        # inventoryString = "Your Inventory : | "
        # counter = 1
        # for thing, count in inventoryDict.items():
        #     if counter <= 9:
        #         inventoryString += f"({counter}) {count} {thing} | "
        #         counter += 1
        window.write(inventoryString)


gameObject = Game()
draw_board(gameObject, Element("game-screen"))
draw_stats(gameObject, Element("stats"))

js.document.addEventListener('keydown', create_proxy(onKeyPress))