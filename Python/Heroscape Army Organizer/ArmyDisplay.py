# Name: Benjamin Jones
# Program: ArmyDisplay
# Purpose: create a GUI for the database

# import elements
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial
import sys
# import additional scripts
import CardDatabaseMaker
import Gather
import popup

class ArmyDisplay:
    __slots__ = ['gt', 'db', 'pu', 'generals', 'text','points', 'limit', 'count', 'ret', 'finished', 'wins', 'losses']

    def __init__(self, db = 'units.db'):
        self.db = CardDatabaseMaker.ReadFiles(db)
        self.gt = Gather.GatherItems(db)
        self.pu = popup.PopUp()
        self.text = {}
        self.points = 0
        self.count = 0
        self.limit = 15
        self.ret = ''
        self.finished = False
        self.generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]
        self.wins = 0
        self.losses = 0

    """
    armyView: shows the information of the army

    parameters:
    self ----- this can be ignored
    """
    def armyView(self, window):
        title = "Heroscape Armies"
        firstRun = True # this likely will not be used, but who knows
        bWidth = 16
        """
        standard functions
        """        
        def destroy():
            window.quit()
            return
        def load(idd):
            empty()
            band = self.db.getBand(idd)
            setName.delete("1.0", END)
            setName.insert("1.0", band[0])
            tWins.config(state = NORMAL)
            tWins.delete("1.0", END)
            tWins.insert("1.0", band[1])
            self.wins = band[1]
            tWins.config(state = DISABLED)
            tLoss.config(state = NORMAL)
            tLoss.delete("1.0", END)
            tLoss.insert("1.0", band[2])
            self.losses = band[2]
            tLoss.config(state = DISABLED)
            
            # set up text
            for i in range(4, len(band), 2):
                if band[i] == 'None':
                    break
                self.text[band[i]] = int(band[i + 1])
            # set up points
            keys = list(self.text.keys())
            keys = sorted(keys)
            for unit in keys:
                use = self.db.display(unit)
                self.points += int(use[12]) * int(self.text[unit])
            # adjust
            adjust()
        def configArmies():
            groups = self.db.getAllBands()
##            print(groups)
            for group in groups:
                bands = group[0]
##            bands = sorted(bands)
##            print(bands)
            groups = sorted(groups)
            armies.delete(0, 'last')
            for item in groups:
                armies.add_command(
                    label = item[0],
                    command = partial(load, item[0])
                    )
            return
        def empty():
            self.text = {}
            self.points = 0
            adjust()
            setName.delete("1.0", END)
            tWins.config(state = NORMAL)
            tWins.delete("1.0", END)
            tWins.insert("1.0", '0')
            tWins.config(state = DISABLED)
            tLoss.config(state = NORMAL)
            tLoss.delete("1.0", END)
            tLoss.insert("1.0", '0')
            tLoss.config(state = DISABLED)
        def add():
            item = varUnit.get()
            if item == 'SELECT':
                return
            use = self.db.display(item)
            if item not in self.text:
                if self.count >= self.limit:
                    return
                self.text[item] = 1
                self.count += 1
            else:
                if 'UNIQUE' in use[3]:
                    return
                self.text[item] += 1
            self.points += use[12]
            adjust()
            return
        def remove():
            item = varUnit.get()
            if item == 'SELECT' or item not in self.text:
                return
            self.text[item] -= 1
            if self.text[item] == 0:
                del self.text[item]
                self.count -= 1
            use = self.db.display(item)
            self.points -= use[12]
            adjust()
            return
        def save():
            # need to get a name
            name = setName.get('1.0', END)
            name = name.replace('\n', '')
            win = int(tWins.get("1.0", END))
            loss = int(tLoss.get("1.0", END))
            self.wins = win - self.wins
            self.losses = loss - self.losses
            ratio = 'N/A'
            if win != 0 or loss != 0:
                ratio = str(win) + '/' + str(win + loss)
            if name == '':
                return
            # order all items from self.text
            keys = list(self.text.keys())
            keys = sorted(keys)
            # set up what to send
            send = []
            send.append(name)
            send.append(win)
            send.append(loss)
            send.append(ratio)
            for unit in keys:
                send.append(unit)
                send.append(self.text[unit])
                self.db.updateRecord(unit, self.wins, self.losses)
            self.db.addBands(send)
            configArmies()
            return
        def delete():
            name = setName.get('1.0', END)
            name = name.replace('\n', '')
            self.db.removeBands(name)
            configArmies()
            return
        
        def adjust ():
            keys = list(self.text.keys())
            keys = sorted(keys)
            write = ""
            for key in keys:
                write += key + ': ' + str(self.text[key]) + '\n'
            write += 'Points: ' + str(self.points)
            view.config(state = NORMAL)
            view.delete("1.0", END)
            view.insert("1.0", write)
            view.config(state = DISABLED)
            return
        
        # items for adding wins and losses
        def addWL():
            do = optFirst.get()
            if do == AW:
                tWins.config(state = NORMAL)
                num = int(tWins.get("1.0", END)) + 1
                tWins.delete("1.0", END)
                tWins.insert("1.0", num)
                tWins.config(state = DISABLED)
            elif do == AL:
                tLoss.config(state = NORMAL)
                num = int(tLoss.get("1.0", END)) + 1
                tLoss.delete('1.0', END)
                tLoss.insert("1.0", num)
                tLoss.config(state = DISABLED)
            elif do == RW:
                num = int(tWins.get("1.0", END))
                if num == 0:
                    return
                num -= 1
                tWins.config(state = NORMAL)
                tWins.delete('1.0', END)
                tWins.insert("1.0", num)
                tWins.config(state = DISABLED)
            elif do == RL:
                num = int(tLoss.get("1.0", END))
                if num == 0:
                    return
                num -= 1
                tLoss.config(state = NORMAL)
                tLoss.delete('1.0', END)
                tLoss.insert("1.0", num)
                tLoss.config(state = DISABLED)
##            setUp()
        AW = "ADD WIN"
        AL = "ADD LOSS"
        RW = "REMOVE WIN"
        RL = "REMOVE LOSS"
        """
        start of tkinter window
        """
        # constants for window
        # window
        firstTime = True
##        window = Tk()
        window.geometry("500x305")
##        window.columnconfigure(0, weight = 1)
##        window.columnconfigure(1, weight = 1)
##        window.columnconfigure(2, weight = 1)
##        window.columnconfigure(3, weight = 1)
        window.title(title)
        leftSide = Frame(window, height = 305, width = 250)
        leftSide.grid(row = 0, column = 0, sticky = N+E+W+S)
        rightSide = Frame(window, height = 305, width = 250)
        rightSide.grid(row = 0, column = 1, sticky = N+E+W+S)
        # menu system
        menu = Menu(window)
        window.config(menu = menu)
        file = Menu(menu, tearoff = 0)
        armies = Menu(menu, tearoff = 0)

        menu.add_cascade(label='File', menu = file)
        file.add_command(label='New', command = empty)
        file.add_command(label='Save', command = save)
        file.add_command(label='Exit', command = destroy)

        menu.add_cascade(label='Armies', menu = armies)
        
        
        # left side items
        lUnits = Label(
            leftSide,
            text = "UNIT:",
            width = 34,
            )
        lUnits.grid(row = 0, column = 0, columnspan = 5, sticky = N+E+W+S)
        unitButtonOptions = [['SELECT']]
        for gen in self.generals:
            unitButtonOptions.append([gen])
            everything = self.db.gatherGeneral([gen])
            for unit in everything:
                unitButtonOptions[-1].append(unit)
        varUnit = StringVar(value = unitButtonOptions[0][0])
        menuButton = Menubutton(
            leftSide,
            textvariable = varUnit,
            indicatoron = True,
            borderwidth = 1,
            relief = 'raised',
            width = 34,
            )
        unitMenu = Menu(menuButton, tearoff = 0)
        menuButton.configure(menu=unitMenu)
        for item in unitButtonOptions:
            menu = Menu(unitMenu, tearoff = 0)
            if item == ['SELECT']:
                unitMenu.add_radiobutton(value = item[0], label = item[0], variable = varUnit)
            else:
                unitMenu.add_cascade(label = item[0], menu = menu)
                item.pop(0)
                item.sort()
                for value in item:
                    menu.add_radiobutton(value = value, label = value, variable = varUnit)
        menuButton.grid(row = 1, column = 0, columnspan = 5, sticky = N+E+W+S)

        bRemove = Button(
            leftSide,
            text = 'REMOVE',
            width = bWidth,
            height = 1,
            command = remove,
            )
        bAdd = Button(
            leftSide,
            text = 'ADD UNIT',
            width = bWidth,
            height = 1,
            command = add,
            )
        topWidgits = [bAdd,bRemove]
        co = 0
        for item in topWidgits:
            item.grid(row = 3, column = co, sticky = N+S)
            co += 1
        # WIN LOSS SECTIOn
        options = [AW, AL, RW, RL]
        optFirst = StringVar(window)
        optFirst.set(options[0])
        myOptions = OptionMenu(
            leftSide,
            optFirst,
            *options,
            )
        myOptions.config(width = 12)
        lWins = Label (leftSide, text = "WINS:")
        lLoss = Label (leftSide, text = "LOSSES:")
        
        tWins = Text(
            leftSide,
            state = 'disabled',
            height = 1,
            width = bWidth,
            wrap = 'none',
            )
        tLoss = Text(
            leftSide,
            state = 'disabled',
            height = 1,
            width = bWidth,
            wrap = 'none',
            )
        adder = Button(
            leftSide,
            text = "ADD RECORD",
            width = bWidth,
            height = 1,
            command = addWL
            )
        buttons = [myOptions, adder]
        textBoxes = [tWins, tLoss]
        labels = [lWins, lLoss]
        adding = [buttons, labels, textBoxes]
        ro = 4
        for arr in adding:
            co = 0
            for item in arr:
                item.grid(row = ro, column = co, sticky = N+E+W+S)
                co += 1
            ro += 1
        # EXIT SECTION
        bExit = Button(
            leftSide,
            text = 'EXIT',
            width = bWidth,
            height = 1,
            command = destroy,
            )
        bSave = Button(
            leftSide,
            text = 'SAVE',
            width = bWidth,
            height = 1,
            command = save,
            )
        bDelete = Button(
            leftSide,
            text = 'DELETE',
            width = bWidth,
            height = 1,
            command = delete,
            )
        bottomWidgits = [bDelete, bSave]
        co = 0
        for item in bottomWidgits:
            item.grid(row = ro, column = co, sticky = N+S, pady = 10)
            co += 1
        ro += 1
        bExit.grid(row = ro, column = 0, columnspan = 2, sticky = N+S, pady = 10, padx = 10)
        # text box for right side
        labelName = Label(
            rightSide,
            text = 'NAME:'
            )
        setName = Text(
            rightSide,
            height = 1,
            width = 31,
            )
        view = Text(
            rightSide,
            wrap="word",
            height = 16,
            width = 31,
            state = DISABLED,
            )
        rightWidgits = [labelName, setName, view]
        if firstTime:
            configArmies()
            empty()
        ro = 0
        for item in rightWidgits:
            item.grid(row = ro, column = 0)
            ro += 1
    
        mainloop()
        
