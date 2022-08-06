# Name: Benjamin Jones
# Program: RUNME.py
# Purpose: used for deciding which element to load

import sys
import shutil
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial

# my programs
import Display
import MMenu
import allDisp
import setUp
import getSecond
import merge
import pointEval
import UnitBattleReport
import armyBuilder
import ArmyDisplay

class Control:
    __slots__ = ['men', "dis", "sw", "ret", "disA", "SetUp", "mergeHelp", "merger"]
    def __init__(self):
        self.men = MMenu.Menu()
        self.sw = ["", True]
        self.SetUp = setUp.setUP()

    def new(self, win, change = ""):
        self.ret = ""
        firstPass = True
        def stop():
            self.ret = False
            win.quit()
            
        def choose(event = None):
            self.ret = tGet.get("1.0",END).strip("\n")
            if self.ret != "":
                win.quit()
##        win = Tk()
        win.geometry('')
        win.title("New Army Creator")
        lGet = Label(win, text="PLEASE ENTER TITLE OF NEW DATABASE")
        tGet = Text(
            win,
            width = 30,
            height = 1,
            )
        tGet.bind("<Return>", choose)
        bGet = Button(
            win,
            text = "CHOOSE",
            command = choose,
            )
        bCancel = Button(
            win,
            text = 'CANCEL',
            command = stop,
            )
        if firstPass:
            tGet.insert('1.0', change)
            firstPass = False
        lGet.grid(row=0, column = 0)
        tGet.grid(row=1,column=0)
        bGet.grid(row=2,column=0)
        bCancel.grid(row=3,column=0)
        mainloop()
        return self.ret
    
    def copy(self, file, window):
        try:
            newFile = self.new(window, "PLEASE ENTER NEW FILE NAME")
            if newFile == "":
                raise Exception("NO NAME GIVEN")
            elif newFile == False:
                return
            if len(newFile) > 3:
                temp = newFile[len(newFile)-3:]
            else:
                temp = "new"
            if temp != ".db":
                newFile = newFile + ".db"
            shutil.copyfile(file, newFile)
        except:
            print("Unexpected error: ", sys.exc_info()[0])
            print("Message: ", sys.exc_info()[1])
            
    
    def setUp(self, window):
        # constants
        NEW = "NEW"
        DISPLAY = 1
        COPY_DATABASE = 2
        DISPLAY_STAT = 3
        SET_DEFAULT = 4
        MERGER = 5
        RESETWL = 6
        UBR = 7
        AG = 8
        UP = 9
        AD = 10
##        window = Tk()
        
        #main loop
        while self.sw[1] != False:
            tracker = 1
            if not self.sw[0] or self.sw[0] == '':
                self.sw = self.men.mme(self.SetUp.getDefault(), window) #this will return a tuple of which item to open, and the database to use
            elif self.sw[0] == NEW:
                self.sw[0] = self.new()
                tracker = 0
##            if self.sw[0] == "":
##                pass
            elif self.sw[1] == DISPLAY:
                if len(self.sw) < 3:
                    self.sw.append(False)
                self.dis = Display.Display(self.sw[0], self.sw[2])
                self.sw = self.dis.cardview(window, self.sw[2])
            elif self.sw[1] == COPY_DATABASE and tracker != 0:
                self.sw = self.copy(self.sw[0], window)
                self.sw = [False, True]
            elif self.sw[1] == MERGER:
                self.dis = getSecond.getSecond(self.sw[0])
                self.mergeHelp = self.dis.select(window)
                if self.mergeHelp != False:
                    self.dis = merge.merge(self.sw[0],self.mergeHelp)
                    self.dis.combine()
                self.sw = [False, True]
####                HERE
            elif self.sw[1] == RESETWL:
                pe = pointEval.worthEval(self.sw[0])
                pe.reset(window)
                self.sw = [False, True]
            elif self.sw[1] == DISPLAY_STAT:
                if len(self.sw) < 3:
                    self.sw.append(0)
                self.disA = allDisp.allDisp(self.sw[0], self.sw[2])
                self.sw = self.disA.disp(window)
            elif self.sw[1] == SET_DEFAULT: # change default database
                self.SetUp.setDefault(self.sw[0])
                self.sw = [False, True]
            elif self.sw[1] == UBR:
                ubr = UnitBattleReport.battleReport(self.sw[0])
                ubr.display(window)
                self.sw = [False, True]
            elif self.sw[1] == AG:
                ag = armyBuilder.buildArmy(self.sw[0])
                ag.display(window)
                self.sw = [False, True]
            elif self.sw[1] == UP:
                pe = pointEval.worthEval(self.sw[0])
                pe.update(window)
                self.sw = [False, True]
            elif self.sw[1] == AD:
                ad = ArmyDisplay.ArmyDisplay(self.sw[0])
                ad.armyView(window)
                self.sw = [False, True]
            for widget in window.winfo_children():
                widget.destroy()
            window.configure(background = 'gray95')
        return
    
    def tKinterSetup(self):
        window = Tk()
        window.configure(background = 'gray95')
        self.setUp(window)
        return
            

#I may allow for console control over this, but not right now
me = Control()

##me.setUp()
me.tKinterSetup()
