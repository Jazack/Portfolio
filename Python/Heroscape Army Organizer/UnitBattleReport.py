# import elements
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
import tkinter as tk
from functools import partial
import sys
# import additional scripts
import Gather
import popup
import pointEval
import CardDatabaseMaker

class battleReport:

    __slots__ = ['gt', 'db', 'pe', 'generals', 'disp']
    
    def __init__ (self, db = 'units.db'):
        self.db = CardDatabaseMaker.ReadFiles(db)
        self.gt = Gather.GatherItems(db)
        self.pe = pointEval.worthEval(db)
        self.disp = []
        self.generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]

    def display(self, window):
        def destroy():
            window.quit()
        def setUp():
            self.disp = self.gt.displayRecord(varUnit.get())
            tWins.config(state = NORMAL)
            tWins.delete("1.0", END)
            tWins.insert("1.0", str(self.disp[1]))
            tWins.config(state = DISABLED)
            tLoss.config(state = NORMAL)
            tLoss.delete("1.0", END)
            tLoss.insert("1.0", str(self.disp[2]))
            tLoss.config(state = DISABLED)
        def empty():
            tWins.config(state = NORMAL)
            tWins.delete("1.0", END)
            tWins.config(state = DISABLED)
            tLoss.config(state = NORMAL)
            tLoss.delete("1.0", END)
            tLoss.config(state = DISABLED)
        def add():
            if varUnit.get() == 'SELECT':
                return
            do = optFirst.get()
            if do == AW:
                # get worth
                ratio = str(self.disp[1] + 1) + '/' + str(self.disp[1] + self.disp[2] + 1)
                worth = self.pe.formula(varUnit.get(), self.disp[1] + 1, self.disp[2])
                self.gt.addWinLoss(varUnit.get(), worth,  self.disp[1] + 1, self.disp[2], ratio)
            elif do == AL:
                ratio = str(self.disp[1]) + '/' + str(self.disp[1] + self.disp[2] + 1)
                worth = self.pe.formula(varUnit.get(), self.disp[1], self.disp[2] + 1)
                self.gt.addWinLoss(varUnit.get(), worth,  self.disp[1], self.disp[2] + 1, ratio)
            elif do == RW:
                if self.disp[1] <= 0:
                    return
                if self.disp[1] == 1 and self.disp[2] == 0:
                    ratio = 'N/A'
                else:
                    ratio = str(self.disp[1] - 1) + '/' + str(self.disp[1] + self.disp[2] - 1)
                worth = self.pe.formula(varUnit.get(), self.disp[1] - 1, self.disp[2])
                self.gt.addWinLoss(varUnit.get(), worth,  self.disp[1] - 1, self.disp[2], ratio)
            elif do == RL:
                if self.disp[2] <= 0:
                    return
                if self.disp[1] == 0 and self.disp[2] == 1:
                    ratio = 'N/A'
                else:
                    ratio = str(self.disp[1]) + '/' + str(self.disp[1] + self.disp[2] - 1)
                worth = self.pe.formula(varUnit.get(), self.disp[1], self.disp[2] - 1)
                self.gt.addWinLoss(varUnit.get(), worth,  self.disp[1], self.disp[2] - 1, ratio)
            setUp()
        AW = "ADD WIN"
        AL = "ADD LOSS"
        RW = "REMOVE WIN"
        RL = "REMOVE LOSS"
##        window = Tk()
        window.geometry("300x150")
        window.title("UNIT REPORT")

        options = [AW, AL, RW, RL]
        optFirst = StringVar(window)
        optFirst.set(options[0])
        # Labels
        lUnits = Label(window, text="UNIT:")
        lOptions = Label (window, text="ADJUST:")
        lTitle = Label(window, text = "UNIT BATTLE REPORT")
        lWins = Label (window, text = "WINS:")
        lLoss = Label (window, text = "LOSSES:")

        tWins = Text(
            window,
            state = 'disabled',
            height = 1,
            width = 15,
            wrap = 'none',
            )
        tLoss = Text(
            window,
            state = 'disabled',
            height = 1,
            width = 15,
            wrap = 'none',
            )
        # Menus
        # objects
        
        unitButtonOptions = [['SELECT']]
        for gen in self.generals:
            unitButtonOptions.append([gen])
            everything = self.db.gatherGeneral([gen])
            for unit in everything:
                unitButtonOptions[-1].append(unit)
        varUnit = StringVar(value = unitButtonOptions[0][0])
        menuButton = Menubutton(
            window,
            textvariable = varUnit,
            indicatoron = True,
            borderwidth = 1,
            relief = 'raised',
            width = 20,
            )
        unitMenu = Menu(menuButton, tearoff = 0)
        menuButton.configure(menu=unitMenu)
        for item in unitButtonOptions:
            menu = Menu(unitMenu, tearoff = 0)
            if item == ['SELECT']:
                unitMenu.add_radiobutton(value = item[0], label = item[0], variable = varUnit, command = empty)
            else:
                unitMenu.add_cascade(label = item[0], menu = menu)
                item.pop(0)
                item.sort()
                for value in item[:]:
                    menu.add_radiobutton(value = value, label = value, variable = varUnit, command = setUp)
##        
##        units = OptionMenu(
##            window,
##            pFirst,
##            *progs,
##        )
        options = OptionMenu(
            window,
            optFirst,
            *options,
        )
        # buttons
        load = Button(
            window,
            text = "ADD",
            width = 15,
            height = 1,
            command = add
            )
        ex = Button(
            window,
            text = "Exit",
            width = 15,
            height = 1,
            command = destroy
            )
        co = 1
        lTitle.grid(row = 0, column = co, columnspan = 3, sticky = W+E)
        lUnits.grid(row=1, column=co, sticky =N+W+E+S)
        menuButton.grid(row=2, column=co, sticky =N+W+E+S)
        lWins.grid(row=3, column=co, sticky = N+E+W+S)
        tWins.grid(row=4, column=co, sticky = N+E+W+S)
        load.grid(row=5, column = co, sticky = N+W+E+S)
        co = co + 1
        lOptions.grid(row = 1, column = co, sticky = N+W+E+S)
        options.grid(row = 2, column = co, sticky = N+W+E+S)
        lLoss.grid(row=3, column=co, sticky = N+E+W+S)
        tLoss.grid(row=4, column=co, sticky = N+E+W+S)
        ex.grid(row=5, column = co, sticky = N+W+E+S)
#--------------------------------------------END OF TKINTER WINDOW--------------------------------------------
        mainloop()
