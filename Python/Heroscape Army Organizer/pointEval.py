"""
unit point evaluator
POS = want high
NEG = want low
gold value for a unit should be comprised of:
how many units of same type are already there (POS)
point cost (NEG)
life (POS)
move (POS)
range (POS)
attack (POS)
defense (POS)
wins (POS)
Wins with allied units (POS)
losses (NEG)
losses with allied units (NEG)
negative abilities that affect it (NEG)
positive abilities that affect it (POS)
abilities (POS)

Total = -(point cost)-(negative abilities that affect it) - (losses - losses with allied units) - (losses with allied units)
        + (quantity of units already there) + (life) + (move) + (range) + (attack) + (defense) + (wins - wins with allies)
        + (wins with allies) + (positibe abilities that affect it) + (abilities)
"""
"""
imports
"""
import threading
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
import random
import Gather

class worthEval:
    __slots__ = ['quantityVal', 'quantVal','pointVal', 'lifeVal', 'moveVal', 'rangeVal',
                 'attackVal', 'defenseVal', 'winsVal', 'winsAlliedVal', 'lossesVal',
                 'lossesAlliedVal', 'negAbilVal', 'posAbilVal', 'allyAbilVal', 'abilVal', 'dataBase', 'stanWorth', 'testAbilVal',
                 'gt', 'once', 'breaker']
    
    def __init__(self, dataBase):
        # set up global values
        self.stanWorth = 1
        self.quantityVal = 10
        self.quantVal = 3
        self.pointVal = 7
        self.lifeVal = 5
        self.moveVal = 2
        self.rangeVal = 2
        self.attackVal = 4
        self.defenseVal = 2
        self.winsVal = 4
        self.winsAlliedVal = 1
        self.lossesVal = 3
        self.lossesAlliedVal = 1
        self.negAbilVal = 1
        self.posAbilVal = 1
        self.allyAbilVal = 20
        self.abilVal = 2
        self.testAbilVal = 10
        self.dataBase = dataBase
        self.gt = Gather.GatherItems(dataBase)
        self.once = True

    """
    reset: resets the records table

    parameters:
    self ----- this can be ignored
    window --- the window to be used
    """
    def reset(self, window):
##        self.gt.dropRecords()
##        self.gt.startRecords()
##        units = self.gt.getAll()
##        count = 1
##        for unit in units:
##            print('setting up: ' + unit + ' and have done ' + str(count) + ' out of ' + str(len(units)))
##            worth = self.formula(unit)
##            self.gt.addWinLoss(unit, worth)
##            count += 1
        self.breaker = False
        text = StringVar()
        """
        startUpdate: updates each unit
        """
        def startUpdate():
##            self.gt.dropRecords()
##            self.gt.startRecords()
            units = self.gt.getAll()
            count = 1
            for unit in units:
                if self.breaker == True:
                    return
                text.set('updating ' + unit + ' and have done ' + str(count) + ' out of ' + str(len(units)))
                worth = self.formula(unit)
                worth = round(worth, 2)
                self.gt.addWinLoss(unit, worth)
                count += 1
        """
        stop: stops the reset function
        """
        def stop():
            self.breaker = True
            window.quit()
        window.geometry('')
        lLocation = Label(
            window,
            textvariable = text,
            width = 60
            )
        bStop = Button(
            window,
            text = 'EXIT',
            command = stop
            )
        lLocation.grid(row = 0, column = 0)
        bStop.grid(row=1, column = 0)
        t1 = threading.Thread(target = startUpdate)
        t1.start()
        mainloop()
        t1.join()

    """
    update: updates the records table

    parameters:
    self ----- this can be ignored
    window --- the window to be used
    """
    def update(self, window):
        self.breaker = False
        text = StringVar()
        def startUpdate():
            units = self.gt.getAllRecords()
            count = 1
            for unit in units:
                if self.breaker == True:
                    return
                text.set('updating ' + unit[0] + ' and have done ' + str(count) + ' out of ' + str(len(units)))
                worth = self.formula(unit[0])#, unit[1], unit[2])
                worth = round(worth, 2)
                if unit[1] != 0 or unit[2] != 0:
                    ratio = str(unit[1]) + '/' + str(unit[1] + unit[2])
                else:
                    ratio = 'N/A'
                self.gt.addWinLoss(unit[0], worth, unit[1], unit[2], ratio)
                count += 1
        def stop():
            self.breaker = True
            window.quit()
        window.geometry('')
        lLocation = Label(
            window,
            textvariable = text,
            width = 60
            )
        bStop = Button(
            window,
            text = 'EXIT',
            command = stop
            )
        lLocation.grid(row = 0, column = 0)
        bStop.grid(row=1, column = 0)
        t1 = threading.Thread(target = startUpdate)
        t1.start()
        mainloop()
        t1.join()
            
        
    """
    formula: this is to find the worth of each card

    parameters:
    self ----- this can be ignored
    name ----- the name of the unit to evaluate
    """
    def formula(self, name):
        winLoss = self.gt.winLoss(name)
        add = False
        if not winLoss:
            add = True
            winLoss = [name, 0,0]
        if winLoss[1] == 0 and winLoss[2] == 0:
            Total = self.stanWorth
        else:
            Total = (winLoss[1]/(winLoss[1] + winLoss[2]) - 0.5) * (1 + (winLoss[1] + winLoss[2] - 1)/100)
        Total = round(Total, 2)
        return Total

    """
    abilHelp: helps get the units that a figure affects

    parameters:
    self ----- this can be ignored
    name ----- the name of the figure being looked up
    """
    def abilHelp(self, name):
        items = self.gt.abilGet(name)
        units = []
        for group in items:
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
        return units
    """
    higherFormula: this is to find the worth of each card in an army, adjusted for the current units in the army

    parameters:
    self ----- this can be ignored
    name ----- the name of the unit being evaluated
    chosen --- the units that have already been chosen
    """
    def higherFormula(self, name, chosen = {}):
        """
        standard worth from formula

        allies that possitively affect it

        total units used (parabola, should peak at 4):
            -(1/4*x-1)**2 + 1
            
        potential for more units (common),
            y = -(1/10*x)^1.5 + 0.7529 for 0 < x < 5
            0.7529
            y = 0.3535 for x >= 5
        value for unique
            y = 0.2529 ((1/10*x)^1.5 where x = 4)
        
        allied wins

        allied loss

        ignoring abilities

        allied abilities that affect them

        if their abilities affect allies
        
        """
        
        winLoss = self.gt.winLoss(name)
        if not winLoss:
            winLoss = [name, 0,0,0, self.stanWorth]
        unit = self.gt.display(name)
        life = unit[7]
        try:
            points = int(unit[12])
        except:
            points = 0
        ty = unit[3]
        move = unit[8]
        ran = unit[9]
        att = unit[10]
        defe = unit[11]
        points = unit[12]

        # quantity section
        quantity = 0
        if name in chosen:
            quantity = -(1/10* chosen[name][0] )**1.5 + 0.8529
##            quantity = -(1/4 * chosen[name][0] - 1) ** 2 + 2
        # potential quantity for items
        if 'UNIQUE' not in ty:
            quant = (unit[14] - quantity)
            if quant < 5: # at 5 or more units, the advantage that they bring becomes about the same
                quant = -(1/4 * quant - 1) ** 2 + 1
##                quant = (1/10* quant )**1.5
            else:
                quant = 1
        else:
            quant = 0.2529

        # not currently able to get the win loss ratio of being with allies
##        winsAllied = 0
##        lossesAllied = 0
##
        bands = self.gt.getBandWithUnit(name)
        alliedRatio = 0
        if bands != []:
            use = 0.5
            # formula is:
            # (wins - losses + 0.5) ^ 3
            # this is because the more wins or losses, the greater recommendation or warning it should receive.
            # it should be cubed because:
            # 1: it's an exponential increase in reccommendation/warning
            # 2: it will keep the sign, either negative or positive
            for band in bands:
                if type(band) == list:
                    for unit in band:
                        if unit in chosen:
                            if band[1] != 0 or band[2] != 0:
##                                alliedRatio += ((use + (band[1] / (band[1] + band[2]))) * 2)
                                alliedRatio += (band[1] - band[2] + use) ** 3
                            
                else:
                    if band in chosen:
                        if bands[1] != 0 or bands[2] != 0:
                            alliedRatio += (bands[1] - bands[2] + use) ** 3
##                            alliedRatio += ((use + (bands[1] / (bands[1] + bands[2]))) * 2)
                        
                
            
        # end of if statement
        
        eff = self.gt.gather(name)
        effective = 0
        for ef in eff[0]:
            if ef[0] in chosen:
                # the thought is that the more units it affects, the less powerful it's affect is
                effective += (self.allyAbilVal + chosen[ef[0]][0] ** 2) / chosen[ef[0]][1]

        abil = 0             
        affects = self.abilHelp(name)
        temp = len(affects)
        if len(affects) > 25:
            random.shuffle(affects)
            affects = affects[:25]
        for unit in affects:
            if unit in chosen:
              abil += (self.testAbilVal + chosen[unit][0] ** 2)/temp  
              
                
        Total = (
                 + alliedRatio
                 + winLoss[4]
                 + quantity
                 + effective
                 + abil
                 + quant
                 )
        if type(Total) == complex: # in some testing, I was hving this become a complex data type, so if it does that, take the real part
            Total = Total.real
        return Total
