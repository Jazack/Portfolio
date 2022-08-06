import numpy as np
import random
import threading
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial

import Gather
import pointEval
import CardDatabaseMaker

"""
Class to build armies based on point values
"""
class buildArmy:

    __slots__ = ['gt','pe','db','pointTotal', 'generals', 'allowed', 'units',
                 'unitWorth', 'dicL', 'chosen', 'currentPoints', 'estimate', 'theory',
                 'generals', 'text', 'learning', 'stopThreads']
    
    def __init__ (self, db = 'units.db'):
        self.theory = False # for theoretical builds
        self.db = CardDatabaseMaker.ReadFiles(db)
        self.gt = Gather.GatherItems(db)
        self.pe = pointEval.worthEval(db)
        self.chosen = {}
        self.currentPoints = 0
        self.estimate = 0
        self.pointTotal = 0 # point cost to build in
        self.generals = [] # the generals allowed to use
        self.allowed = [] # units allowed to use
        self.unitWorth = []
        self.dicL = []
        self.generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]
        self.stopThreads = False
        self.learning = 0

    """
    controller: used to determine basic variables and set up the section

    Parameters:
    self ----- this can be ignored
    """
    def controller(self, points = 500, firstChar = 'RANDOM STARTER',
                   generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"],
                   theoretical = False, singleton = False, learning = 0):
        #set up
        self.theory = theoretical
        self.setPoints(points)
        self.setLearning(learning)
##        self.setGenerals(generals)
        if not self.setAllowed():
            print('error in first setAllowed()')
            return
        if not self.removeEmpty(theoretical):
            print('error in first removeEmpty()')
            return
        if not self.setWorth():
            print('error in first setWorth()')
            return
        if not self.setUnitPoints(singleton):
            print('error in first setUnitPoints()')
            return
        self.removeTooExpensive()
        if firstChar == 'RANDOM STARTER':
            unit = self.randSelect()
##            print(unit)
        else:
            notIn = True
            for unitInfo in self.unitWorth:
                if firstChar in unitInfo:
                    unit = unitInfo
                    notIn = False
                    break
            if notIn:
                return
        subscriptable = [str, tuple, list]
        if type(unit) not in subscriptable:
            return
        self.sortWorth()
        return unit
##        print("First, has a random selection, greedy knapsack")
##        print("Character is: " + unit[0])
##        self.greedyKnapsack1(unit)
##        print('Army 1:')
##        print(self.chosen)
##        print('estimate worth is: ', self.estimate)
       
    """
    Setters
    """
    def setLearning(self, learn):
        self.learning = learn
    def setPoints(self, point):
        self.pointTotal = point
    def setGenerals(self, generals):
        self.generals = generals
    def setAllowed(self): # should only happen once
        if self.generals == []:
            return False
        self.allowed = self.db.gatherGeneral(self.generals)
        if not self.theory:
            self.removeEmpty()
        return True
    def setWorth(self): # should only happen once
        if self.allowed == []:
            return False
        for unit in self.allowed:
            if self.stopThreads:
                return
            item = self.gt.displayRecord(unit) # gets the unit's record
            self.unitWorth.append([unit, item[4]])
        return True
    def setUnitPoints(self, singleton = False):
        if self.allowed == [] or self.unitWorth == []:
            return False
        for unit in self.unitWorth:
            if self.stopThreads:
                return
            use = self.db.display(unit[0])
            unit.append(use[12])
            if not singleton:
                if 'UNIQUE' in use[3]:
                    unit.append('u')
                else:
                    unit.append('c')
            else:
                unit.append('u')
        return True
    def reset(self):
        self.chosen = {}
        self.currentPoints = 0
        self.estimate = 0
        self.pointTotal = 0 # point cost to build in
##        self.generals = [] # the generals allowed to use
        self.allowed = [] # units allowed to use
        self.unitWorth = []
        self.dicL = []
    """
    Sorters
    """
    def sortWorth(self):
        random.shuffle(self.unitWorth)
        sorting = lambda x : (x[1]) #always uses name as a basis, already used points once to judge
        self.unitWorth = sorted(self.unitWorth, key = sorting)
    """
    removeEmpty: removes units that have no units in them

    parameters:
    self ----- this can be ignored
    """
    def removeEmpty(self, theory = False):
        if self.allowed == []:
            return False
        if theory:
            return True
        changed = True
        while changed:
            if self.stopThreads:
                return
            changed = False
            for unit in self.allowed:
                use = self.db.display(unit)
                if use[14] == 0:
                    self.allowed.remove(unit)
                    changed = True
        return True
    """
    threadUpdateWorth
    """
    def threadUpdateWorth(self, using, start):
        units = using[start::2]
        locs = []
        for unit in units:
            if self.stopThreads:
                return
            for item in self.unitWorth:
                if unit in item:
                    locs.append(self.unitWorth.index(item))
                    break
        worth = []
        # if self.chosen[chosen] doesn't have the second element of the array, add it
        for unit in units:
            if self.stopThreads:
                return
            use = []
            use = self.db.displayRecord(unit)
            if use == []:
                print ('ERROR WITH UNIT: ', end = '')
                print (unit)
            else:
                worth.append(self.pe.higherFormula(use[0], self.chosen))
        for i in range(len(locs)):
            if self.stopThreads:
                return
            self.unitWorth[locs[i]][1] = worth[i]
    """
    updateWorth: updates the worth of all of the units available to be picked
    """
    def updateWorth(self, chosen):
        items = self.gt.abilGet(chosen)
        units = []
        for group in items:
            if self.stopThreads:
                return
            do = True
            for item in group:
                if type(item) is tuple and len(item) > 1:
##                    print('the tuple is:')
                    if item[1] == 'A':
                        do = True
                    else:
                        do = False
                elif do:
                    temp = []
                    temp.append(item)
                    if type(item) is tuple:
                        if len(item):
                            temp = item[0]
                        else:
                            item = False
                            break
                    if temp[0]:
                        units.append(temp[0])
        # add length of affected units from abilities
        if len(self.chosen[chosen]) == 1:
            self.chosen[chosen].append(len(units))
        # find armies with this unit
        bands = self.gt.getBandWithUnit(chosen)
        if bands != []:
            if type(bands[0]) is list:
                for group in bands:
                    use = group[4::2]
                    for unit in use:
                        if unit not in units and unit in self.allowed:
                            units.append(unit)
            else:
                use = bands[4::2]
                for unit in use:
                    if unit not in units and unit in self.allowed:
                        units.append(unit)
        # those that affect the unit
        items = self.gt.gather(chosen)
        for item in items[0]:
            if self.stopThreads:
                return
            if item[0] not in units:
                units.append(item[0])
        # if total to edit is greater than 50, shuffle it and select 50
        if len(units) > 90:
            random.shuffle(units)
            units = units[:90]
        if chosen not in units:
            units.append(chosen)
        t2 = threading.Thread(target = self.threadUpdateWorth, args=(units,0))
        t3 = threading.Thread(target = self.threadUpdateWorth, args=(units,1))
        t2.start()
        t3.start()
        t2.join()
        t3.join()
##        self.threadUpdateWorth(units, 0)
        self.sortWorth()
        return
    
    def removeTooExpensive(self):
        if self.unitWorth == []:
            return False
        sorting = lambda x : (x[2])
        self.unitWorth = sorted(self.unitWorth, key = sorting)
        stay = True
##        while stay:
##            stay = False
##            for unit in self.unitWorth:
##                if unit[2] > (self.pointTotal - self.currentPoints):
##                    stay = True
##    ##                print('removing: ')
##    ##                print(unit)
##    ##                print('because: ' + str(unit[2]) + ' > ' + str(self.pointTotal - self.currentPoints))
##                    self.unitWorth.remove(unit)
        while self.unitWorth != [] and self.unitWorth[-1][2] > (self.pointTotal - self.currentPoints):
            self.unitWorth.pop()
            if self.stopThreads:
                return
        return True

    """
    Selectors
    """
    def randSelect(self):
        if self.unitWorth == []:
            return False
        use = np.array(self.unitWorth)
        unit = np.random.choice(len(use), size = 1)
        unit = self.unitWorth[unit[0]]
        return unit

    """
    greedyKnapsack1: selects 1 item for the knapsack problem, follows a greedy algorithm

    made for quick testing, likely will not be all that great
    """
    def greedyKnapsack1(self, first = False):
        """
        self.chosen is a dictionary in the format of {unit name : [quantity, amount it affects]}
        """
        ## several breaks are added in case of exiting the program early
        if self.stopThreads:
            return
        if first:
            self.chosen[first[0]] = [1]
            use = self.db.display(first[0])
            use = use[14]
            if first[3] == 'u' or use == self.chosen[first[0]]:
                self.unitWorth.remove(first)
            self.currentPoints += first[2]
            self.removeTooExpensive()
            self.updateWorth(first[0])
            self.sortWorth() 
        if self.unitWorth == []:
            return
        ## choosing the unit
        weights = []
        if self.learning == 0 or len(self.unitWorth) == 1:
            weights.append(100)
        else:
            count = 0
            total = 0
            weights.append(100 - self.learning)
            while total < self.learning:
                """
                needs to set up an array of weights, based on self.learning
                for instance, if self.learning == 4, then the weights will look like
                3, 1
                if self.learning == 10, then the weights will look like
                4, 3, 2, 1
                if self.learning == 100, then the weights will look like
                14, 13, 12, 11, 10, 9, 8, 7, 6, 4, 3, 2, 1
                """
                for i in range(count):
                    weights[i + 1] += 1
                    total += 1
                    if total == self.learning:
                        break
                if total == self.learning:
                    break
                if count < len(self.unitWorth) - 1:
                    weights.append(1)
                    count += 1
                    total += 1
                    
        options = []
        if len(weights) < len(self.unitWorth):
            options = self.unitWorth[-1:-len(weights) - 1: -1]
        else:
            options = self.unitWorth[::-1]
        myWeights = tuple(weights)
        
        chosing = random.choices(options, weights = myWeights, k = 1)
        chosing = chosing[0]
        chose = chosing[0]
        if type(chose) == list:
            print('chose type is: ', end='')
            print(type(chose))
            chose = chose[0]
            print('chose type is now: ', end='')
            print(type(chose))
            print('chosing is: ', end='')
            print(chosing)
        
        if self.theory:
            use = float('inf')
        else:
            use = self.db.display(chose)
            use = use[14]
        self.estimate += chosing[1]

        if self.stopThreads:
            return
        
        if chose in self.chosen:
            self.chosen[chose][0] += 1
        else:
            self.chosen[chosing[0]] =  [1]
        self.currentPoints += chosing[2]
        index = self.unitWorth.index(chosing)
        if chosing[3] == 'u' or use == self.chosen[chosing[0]][0]:
            self.unitWorth.pop(index)
        else:
            use = self.db.displayRecord(chose)
            worth = self.pe.higherFormula(use[0], self.chosen)
            self.unitWorth[index][1] = worth
        if self.stopThreads:
            return
        self.removeTooExpensive()
        if self.stopThreads:
            return
        self.updateWorth(chose)
        if self.stopThreads:
            return
        self.sortWorth()
    
    """
    The functions needed:
    controller -
    set pointTotal - done
    set generals - done
    set allowed - done
    sort allowed - done
    set worth - done
    update worth - done
    remove too expensive units - done
    random selection of first item - done
    greedy knapsack problem - done
    better knapsack problem -
    
    self.connected = self.db.custSearchHelp(self.dicL)
    """

    """
    sets the display
    """
    def display(self, window):
        generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]
        starter = self.controller
        reset = self.reset
        knapsack = self.greedyKnapsack1
        title = "Heroscape Army Generator"
        firstRun = True
        bWidth = 14
        choice = 1
        learningVar = DoubleVar()
        """
        standard functions
        """        
        def destroy():
            self.stopThreads = True
            for key in myThreads.keys():
                myThreads[key].join()
            window.quit()
            return

        def save():
            # need to get a name
            name = setName.get('1.0', END)
            name = name.replace('\n', '')
            win = 0
            loss = 0
            ratio = 'N/A'
            # order all items from self.chosen
            keys = list(self.chosen.keys())
            keys = sorted(keys)
            # set up what to send
            send = []
            send.append(name)
            send.append(win)
            send.append(loss)
            send.append(ratio)
            for unit in keys:
                send.append(unit)
                send.append(self.chosen[unit][0])
            self.db.addBands(send)
            return
        
        def generateHelper():
            if 't1' in myThreads:                            
                myThreads['t1'].join()
                del myThreads['t1']
            bGenerate['state'] = DISABLED
            file.entryconfigure(0, state = DISABLED)
            myThreads['t1'] = threading.Thread(target = generate)
            myThreads['t1'].start()
            return
        
        def generate():
            #(self, points, firstChar, generals, theoretical, singleton)
            reset()
            loadingAdjust()
            sPoints = tPoints.get("1.0", END)
            sPoints = sPoints.strip('\n')
            if sPoints.isdigit():
                sPoints = int(sPoints)
            else:
                sPoints = 500
            sUnit = varUnit.get()
            sUnit = sUnit.replace('\n', '')
            sTheory = v.get()
            sSingleton = singleton.get()
            first = starter(sPoints, sUnit, generals, sTheory, sSingleton, learningVar.get())
            loadingAdjust()
            knapsack(first)
            loadingAdjust()
            if self.stopThreads:
                return
            while self.currentPoints < self.pointTotal and len(self.unitWorth):
                if self.stopThreads:
                    return
                knapsack()
                loadingAdjust()
            adjust()
            bGenerate['state'] = NORMAL
            items = file.winfo_children()
            file.entryconfigure(0, state = NORMAL)
##            self.greedyKnapsack1()
        def setup():
            generals = []
            if jandar.get():
                generals.append('JANDAR')
            if ullar.get():
                generals.append('ULLAR')
            if vydar.get():
                generals.append('VYDAR')
            if einar.get():
                generals.append('EINAR')
            if utgar.get():
                generals.append('UTGAR')
            if aquilla.get():
                generals.append('AQUILLA')
            if valkrill.get():
                generals.append('VALKRILL')
            if marvel.get():
                generals.append('MARVEL')
            if generals == []:
                generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]
            self.generals = generals
            unitMenu.delete(0, 'last')
            unitButtonOptions = [['RANDOM STARTER']]
            for gen in generals:
                unitButtonOptions.append([gen])
                everything = self.db.gatherGeneral([gen])
                for unit in everything:
                    unitButtonOptions[-1].append(unit)
            for item in unitButtonOptions:
                menu = Menu(unitMenu, tearoff = 0)
                if item == ['RANDOM STARTER']:
                    unitMenu.add_radiobutton(value = 'RANDOM STARTER', label = item[0], variable = varUnit)
                else:
                    unitMenu.add_cascade(label = item[0], menu = menu)
                    item.pop(0)
                    item.sort()
                    for value in item:
                        menu.add_radiobutton(value = value, label = value, variable = varUnit)
        def loadingAdjust():
            if self.stopThreads:
                return
            keys = list(self.chosen.keys())
            keys = sorted(keys)
            write = 'LOADING UNITS:\n'
            for key in keys:
                if self.stopThreads:
                    return
                write += key + ": " + str(self.chosen[key][0]) + '\n'
            write += 'Points: ' + str(self.currentPoints)
            view.config(state = NORMAL)
            view.delete("1.0", END)
            view.insert("1.0", write)
            view.config(state = DISABLED)
            return
        
        def adjust():
            # adjusts the units
            if self.stopThreads:
                return
            keys = list(self.chosen.keys())
            keys = sorted(keys)
            write = ''
            for key in keys:
                if self.stopThreads:
                    return
                write += key + ": " + str(self.chosen[key][0]) + '\n'
            write += 'Points: ' + str(self.currentPoints)
            view.config(state = NORMAL)
            view.delete("1.0", END)
            view.insert("1.0", write)
            view.config(state = DISABLED)
            return
        """
        start of tkinter window
        """
        # constants for window
        # window
        myThreads = {}
        firstTime = True
##        window = Tk()
        window.geometry("500x325")
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
        file.add_command(label='Generate Army', command = generateHelper)
        file.add_command(label='Save', command = save)
        file.add_command(label='Exit', command = destroy)
        # variables
        v = IntVar()
        jandar = BooleanVar()
        ullar = BooleanVar()
        vydar = BooleanVar()
        einar = BooleanVar()
        utgar = BooleanVar()
        aquilla = BooleanVar()
        valkrill = BooleanVar()
        marvel = BooleanVar()
        singleton = BooleanVar()
        # left side items
        lUnits = Label(
            leftSide,
            text = "UNIT:",
            width = 34,
            )
        lUnits.grid(row = 0, column = 0, columnspan = 5, sticky = N+E+W+S)
        
        varUnit = StringVar(value = 'RANDOM STARTER')
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

        menuButton.grid(row = 1, column = 0, columnspan = 5, sticky = N+W+S)
        bGenerate = Button(
            leftSide,
            text = 'GENERATE',
            width = bWidth,
            height = 1,
            command = generateHelper,
            )
        lPoints = Label(
            leftSide,
            text = 'POINTS',
            width = bWidth,
            )
        tPoints = Text(
            leftSide,
            height = 1,
            width = bWidth,
            wrap = 'none',
            )
        lLearning = Label(
            leftSide,
            text = 'LEARNING',
            width = bWidth,
            )
        sLearning = Scale(
            leftSide,
            from_ = 0,
            to = 100,
            orient = 'horizontal',
            variable = learningVar,
            )
        
        adding = [bGenerate, lPoints, tPoints, lLearning, sLearning]
        ro = 2
        for item in adding:
            co = 0
            item.grid(row = ro, column = co, sticky = N+W+S)
            ro += 1
        checkBoxes = Canvas(leftSide, width = 120, height = 150, relief = SUNKEN)
        checkBoxes.grid(row = 2, column = 1, rowspan = 7, sticky = N+W+S)
        # check boxes
        lGenerals = Label(checkBoxes, text = 'GENERALS', borderwidth = 0)
        cJandar = Checkbutton(
            checkBoxes,
            text = 'JANDAR',
            variable = jandar,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cUllar = Checkbutton(
            checkBoxes,
            text = 'ULLAR',
            variable = ullar,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cVydar = Checkbutton(
            checkBoxes,
            text = 'VYDAR',
            variable = vydar,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cEinar = Checkbutton(
            checkBoxes,
            text = 'EINAR',
            variable = einar,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cUtgar = Checkbutton(
            checkBoxes,
            text = 'UTGAR',
            variable = utgar,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cAquilla = Checkbutton(
            checkBoxes,
            text = 'AQUILLA',
            variable = aquilla,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cValkrill = Checkbutton(
            checkBoxes,
            text = 'VALKRILL',
            variable = valkrill,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cMarvel = Checkbutton(
            checkBoxes,
            text = 'MARVEL',
            variable = marvel,
            onvalue = True,
            offvalue = False,
            borderwidth = 0,
            command = setup,
            justify = 'left',
            anchor = 'w',
            )
        cSingleton = Checkbutton(
                checkBoxes,
                text = 'SINGLETON',
                variable = singleton,
                onvalue = True,
                offvalue = False,
                justify = 'left',
                anchor = 'w',
                )
        checkbox = [lGenerals, cJandar, cUllar, cVydar, cEinar, cUtgar, cAquilla, cValkrill, cMarvel]
        vals = [('THEORY',1),('POSSESS', 0)]
        for texts, val in vals:
            checkbox.append(Radiobutton(
                checkBoxes,
                text = texts,
                variable = v,
                value = val,
                justify = 'left',
                anchor = 'w',
                ))
        checkbox.append(cSingleton)
        
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
        bottomWidgits = [bSave, bExit]
        co = 0
        for item in bottomWidgits:
            item.grid(row = ro, column = co, sticky = W+N+S, pady = 10)
            ro += 1
        ro = 0

        for item in checkbox:
            item.grid(row = ro, column = co)
            ro += 1
            
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
        
        ro = 0
        for item in rightWidgits:
            item.grid(row = ro, column = 0, pady = 0, sticky = W+N+S)
            ro += 1
        if firstRun:
            setup()
        mainloop()
        self.stopThreads = True
        for key in myThreads.keys():
            myThreads[key].join()


    
