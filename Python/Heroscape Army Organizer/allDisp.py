# Name: Benjamin Jones
# Program: allDisp.py
# purpose: display the general information, as well as win loss ratio, of each card

# import elements
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial
import sys
# import additional scripts
import CardDatabaseMaker
import pointEval
import Gather
import Display
import popup
    
class allDisp:
    __slots__ = ['db', 'gt', 'pu', 'pe',
                 'generals', 'tabs', 'first', 't0abs',
                 'set', 'perPage', 'description','database',
                 'opt','unit','sortBy','displayer',
                 'records', 'specSetup','general', 'toSet', 'once']

    def __init__(self, db="units.db", given = False):
        # [self.unit, self.set, self.sortBy, self.general, self.perPage]
        self.database = db
        self.db = CardDatabaseMaker.ReadFiles(db)#initialize the database
        self.gt = Gather.GatherItems(db) # initialize gathering items
        self.pu = popup.PopUp() # if I need popups
        self.pe = pointEval.worthEval(db) # to figure out point worths
        self.first = True
        self.generals = {
            "JANDAR" : 1,
            "ULLAR" : 2,
            "VYDAR" : 3,
            "EINAR" : 4,
            "UTGAR" : 5,
            "VALKRILL" : 6,
            "AQUILLA" : 7,
            "MARVEL" : 8,
            } # the generals
        self.sortBy = {
            'group' : 0, # 0 is name, 1 is general, 12 is points, 14 is quantity, 10 is wins, 11 is losses, 8 is ratio, 9 is worth
            'descend' : False, # True is Z to A, False is A to Z
            }
        self.displayer = []
        self.records = self.db.getAllRecords()
        self.set = 0
        self.perPage = 10
        self.description = ''
        self.opt = False
        self.unit = False
        self.specSetup = False
        self.general = []
        self.toSet = []
        self.once = True
        if given:
            self.set = given[1]
            self.sortBy = given[2]
            self.toSet = given[3]
            self.perPage = given[4]

    # function: disp
    #
    # purpose: set up and run the GUI for the display
    def disp(self, window):
        def end():
            window.quit()
        def setGenerals():
            for gen in self.toSet:
                if gen in self.generals:
                    generalMenu.invoke(self.generals[gen])
        def loadUnit(name):
            self.opt = 1 # displays code
            self.unit = name
            window.quit()
            return
        def buildTable():
            for wid in middle.winfo_children():
                wid.destroy()
            showMin = self.set
            showMax = self.set + self.perPage
            if showMax > len(self.displayer):
                showMax = len(self.displayer)
            self.description.set('Showing ' + str(showMin + 1) + ' - ' + str(showMax) + ' out of ' + str(len(self.displayer)))
            fields = []
            for i in range(showMin, showMax):
                name = ''
                if self.specSetup:
                    name = self.records[i][0]
                else:
                    name = self.displayer[i][0]
                record = self.gt.winLoss(name)
                disp = self.db.display(name)
                if not record:
                    self.pe.formula(self.displayer[i][0])
                    record = self.gt.displayRecord(self.displayer[i][0])
                tempB = Button(
                    middle,
                    text = disp[0],
                    command = partial(loadUnit, disp[0]),
                    height = 1,
                    width = 45,
                    )
                labelG = Button(
                    middle,
                    text = disp[1],
                    width = sizes,
                    state = DISABLED,
                    )
                labelP = Button(
                    middle,
                    text = disp[12],
                    width = sizes,
                    state = DISABLED,
                    )
                labelQ = Button(
                    middle,
                    text = disp[14],
                    width = sizes,
                    state = DISABLED,
                    )
                labelW = Button(
                    middle,
                    text = record[1],
                    width = sizes,
                    state = DISABLED,
                    )
                labelL = Button(
                    middle,
                    text = record[2],
                    width = sizes,
                    state = DISABLED,
                    )
                lRatio = Button(
                    middle,
                    text = record[3],
                    width = sizes,
                    state = DISABLED,
                    )
                lWorth = Button(
                    middle,
                    text = record[4],
                    width = sizes,
                    state = DISABLED,
                    )
                fields.append([tempB, labelG, labelP, labelQ, labelW, labelL, lRatio, lWorth])
            ro = 0
            
            for unit in fields:
                ro = ro + 1
                co = 0
                for item in unit:
                    item.grid(row = ro, column = co, sticky = N+E+W+S)
                    co = co + 1
            return
        """ END OF buildTable setups """
        def sorter(sortBy):
            if sortBy == self.sortBy['group']:
                if self.sortBy['descend']:
                    self.sortBy['descend'] = False
                else:
                    self.sortBy['descend'] = True
            else:
                self.sortBy['group'] = sortBy
                self.sortBy['descend'] = False
            self.set = 0
            sorting = lambda x : (x[self.sortBy['group']], x[0]) #always uses name as a basis
            self.displayer = sorted(self.displayer, key = sorting, reverse = self.sortBy['descend'])
            self.specSetup = False
            buildTable()
        def specialSort(sortBy):
            if sortBy == self.sortBy['group']:
                if self.sortBy['descend']:
                    self.sortBy['descend'] = False
                else:
                    self.sortBy['descend'] = True
            else:
                self.sortBy['group'] = sortBy
                self.sortBy['descend'] = False
            self.set = 0
            keys = {
                8 : 3, # ratio
                9 : 4, # worth
                10 : 1, # wins
                11 : 2, # losses
                }
            sorting = lambda x : (x[keys[self.sortBy['group']]], x[0])
            self.records = sorted(self.records, key = sorting, reverse = self.sortBy['descend'])
            self.specSetup = True
            buildTable()
##            sorting = lambda x : (x[
        def increment():
            if (self.set + self.perPage * 2) < len(self.displayer):
                self.set += self.perPage
            else:
                self.set = len(self.displayer) - self.perPage
            buildTable()
            return
        def decrement():
            if (self.set - self.perPage) >= 0:
                self.set -= self.perPage
            else:
                self.set = 0
            buildTable()
            return
        def start():
            self.set = 0
            buildTable()
        def lastItem():
            self.set = len(self.displayer) - self.perPage
            buildTable()
        def changeSet(perPage):
            if self.perPage == perPage:
                return
            self.perPage = perPage
            if self.set % self.perPage != 0:
                self.set -= self.set % self.perPage
            if self.set + self.perPage > len(self.displayer):
                self.set = len(self.displayer) - self.perPage
            buildTable()
        def setGeneral(general):
            if general[0] in self.general:
                self.general.remove(general[0])
            else:
                self.general.append(general[0])
            self.displayer = []
            self.records = []
            if self.general == []:
                everything = self.db.getAll()
            else:
                everything = self.db.gatherGeneral(tuple(self.general))
            for unit in everything:
                self.displayer.append(self.db.display(unit))
                self.records.append(self.gt.displayRecord(unit))
            self.sortBy['descend'] = not self.sortBy['descend']
            if self.sortBy['group'] >= 8 and self.sortBy['group'] <= 11:
                specialSort(self.sortBy['group'])
            else:
                sorter(self.sortBy['group'])
        lSize = 16
        mSize = 10
        sSize = 6
        everything = self.db.getAll()
        
        firstPass = True
        if self.first:
            self.first = False
            for unit in everything:
                self.displayer.append(self.db.display(unit))
            self.displayer.sort()
        # window
##        window = Tk()
        window.geometry('')
        top = Frame(window, width = 200, height = 1)
        top.grid(row = 0, column = 0)
        middle = Canvas(window, width = 200, height = 100)
        middle.grid(row = 1, column = 0)
        bottom = Frame(window, width = 200, height = 1)
        bottom.grid(row = 2, column = 0)
        window.title("Unit Stats")
        """
        The menu system
        """
        menu = Menu(window)
        window.config(menu=menu)
        mainMenu = Menu(
            menu,
            tearoff = 0
            )
        editMenu = Menu(
            menu,
            tearoff = 0
            )
        generalMenu = Menu(
            menu,
            tearoff = 0,
            )
        menu.add_cascade(label='File', menu = mainMenu)
        menu.add_cascade(label='View', menu = editMenu)
        menu.add_cascade(label='Generals', menu = generalMenu)
        mainMenu.add_command(label = 'EXIT', command = end)

        editMenu.add_command(label = 'UNITS PER PAGE:', state = DISABLED)
        editMenu.add_command(label = '10', command = partial(changeSet, 10))
        editMenu.add_command(label = '15', command = partial(changeSet, 15))
        editMenu.add_command(label = '20', command = partial(changeSet, 20))
        editMenu.add_command(label = '25', command = partial(changeSet, 25))

        generalMenu.add_command(label = 'Only Show:', state = DISABLED)
        generalMenu.add_checkbutton(label = 'JANDAR', command = partial(setGeneral, ['JANDAR']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'ULLAR', command = partial(setGeneral, ['ULLAR']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'VYDAR', command = partial(setGeneral, ['VYDAR']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'EINAR', command = partial(setGeneral, ['EINAR']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'UTGAR', command = partial(setGeneral, ['UTGAR']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'VALKRILL', command = partial(setGeneral, ['VALKRILL']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'AQUILLA', command = partial(setGeneral, ['AQUILLA']), onvalue = 1, offvalue = 0)
        generalMenu.add_checkbutton(label = 'MARVEL', command = partial(setGeneral, ['MARVEL']), onvalue = 1, offvalue = 0)

        self.description = StringVar()
        sizes = 10
##        scrollbar = Frame(window)
        # order buttons
        bName = Button(
            top,
            text = "NAME",
            width = 45,
            command = partial(sorter, 0),
            )
        bGeneral = Button(
            top,
            text = "GENERAL",
            width = sizes,
            command = partial(sorter, 1),
            )
        bPoints = Button(
            top,
            text = "POINTS",
            width = sizes,
            command = partial(sorter, 12)
            )
        bQuantity = Button(
            top,
            text = "QUANTITY",
            width = sizes,
            command = partial(sorter, 14)
            )
        bWins = Button(
            top,
            text = "WINS",
            width = sizes,
            command = partial(specialSort, 10)
            )
        bLosses = Button(
            top,
            text = "LOSSES",
            width = sizes,
            command = partial(specialSort, 11)
            )
        bRatio = Button(
            top,
            text = "RATIO",
            width = sizes,
            command = partial(specialSort, 8)
            )
        bWorth = Button(
            top,
            text = "WORTH",
            width = sizes,
            command = partial(specialSort, 9)
            )
        # table setup
##        self.tabs = []
##        self.tabs.append(Frame(window))
##        self.tabs[0].grid(row = 1, column = 0, columnspan = 
        
        # grid setup
        myButtons = [
            bName,
            bGeneral,
            bPoints,
            bQuantity,
            bWins,
            bLosses,
            bRatio,
            bWorth
            ]
        co = 0
        for item in myButtons:
            item.grid(row = 0, column = co, sticky = N+E+W+S)
            co = co + 1
            
        # bottom
        bExit = Button(
            bottom,
            text = 'EXIT',
            width = sizes,
            command = end
            )
        bExit1 = Button(
            bottom,
            text = 'EXIT',
            width = sizes,
            command = end
            )
        bLast = Button(
            bottom,
            text = 'LAST',
            width = sizes,
            command = lastItem,
            )
        bFirst = Button(
            bottom,
            text = 'FIRST',
            width = sizes,
            command = start,
            )
        bNext = Button(
            bottom,
            text = 'NEXT',
            width = sizes,
            command = increment
            )
        bBack = Button(
            bottom,
            text = 'BACK',
            width = sizes,
            command = decrement
            )
        lSection = Label(
            bottom,
            textvariable = self.description,
            )
        botItems = [
            bExit,
            bFirst,
            bBack,
            lSection,
            bNext,
            bLast,
            bExit1,
            ]
        ro = 0
        co = 0
        for unit in botItems:
            unit.grid(row = ro, column = co, sticky = N+E+W+S)
            co += 1
        if firstPass:
            firstPass = False
            setGenerals()
            buildTable()
        mainloop()
        if self.unit:
            return [self.database, self.opt, [self.unit, self.set, self.sortBy, self.general, self.perPage]]
        return [False, True]
