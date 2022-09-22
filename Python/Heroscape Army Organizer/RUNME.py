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
import CardDatabaseMaker
import new

"""
The control class, this will be in charge of setting up each sub program
"""
class Control:
    __slots__ = ['men', "dis", "sw", "ret", "disA", "SetUp", "mergeHelp", "merger"]

    """
    __init__: this function will set up the bassics for everything

    parameters:
    self ----- this can be ignored
    """
    def __init__(self):
        self.men = MMenu.Menu()
        self.sw = ["", True]
        self.SetUp = setUp.setUP()

    """
    new: this function takes care of when a new database is needed

    parameters:
    self ----- this can be ignored
    win ------ the window that will be made
    change --- used to insert a name if needed
    """
    def new(self, win, change = ""):
        self.ret = ""
        firstPass = True
        """
        stop: stops this function and gets out of the window
        """
        def stop():
            self.ret = False
            win.quit()

        """
        choose: gets the name chosen
        """
        def choose(event = None):
            self.ret = tGet.get("1.0",END).strip("\n")
            if self.ret != "":
                win.quit()
##        win = Tk()
        # set up the window
        win.geometry('')
        win.title("New Army Creator")
        lGet = Label(win, text="PLEASE ENTER TITLE OF NEW DATABASE")
        # set up the widgits
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
        # set up the name to be changed
        if firstPass:
            tGet.insert('1.0', change)
            firstPass = False
        # initialize everything
        lGet.grid(row=0, column = 0)
        tGet.grid(row=1,column=0)
        bGet.grid(row=2,column=0)
        bCancel.grid(row=3,column=0)
        mainloop() # end of main section
        return self.ret
    """
    updateDB: updates the database, it is not available for every version of the system

    parameters:
    self ----- this can be ignored
    database - the database to use
    """
    def updateDB(self, database):
        generals = {"JANDAR":("deep sky blue", 0), "ULLAR":("green", 1),
                    "VYDAR": ("slate grey", 2), "EINAR":("orange",3),
                    "UTGAR" : ("red", 4), "VALKRILL" : ("gold4", 5),
                    "AQUILLA" : ("dark goldenrod", 6), "MARVEL": ("yellow2", 7)}
        keys = generals.keys()
        db = CardDatabaseMaker.ReadFiles(database)
        for key in keys:
            db.addGeneral(key, generals[key][0], generals[key][1])
        return
    """
    copy: copies a database

    parameters:
    self ----- this can be ignored
    file ----- the file to be copied
    window --- the window to be changed
    """
    def copy(self, file, window):
        try:
            """
            get the name for the new file
            make sure it works
            if needed add .db to the end
            create the file
            """
            myNew = new.new()
            newFile = myNew.new(window, "PLEASE ENTER NEW FILE NAME")
            if newFile == "":
                raise Exception("NO NAME GIVEN")
            elif newFile == False:
                return file
            if len(newFile) > 3:
                temp = newFile[len(newFile)-3:]
            else:
                temp = "new"
            if temp != ".db":
                newFile = newFile + ".db"
            shutil.copyfile(file, newFile)
            return newFile
        except:
            # if there's an error, report it
            print("Unexpected error: ", sys.exc_info()[0])
            print("Message: ", sys.exc_info()[1])
            
    """
    setUp: this is the main section that will decode what to do next

    parameters:
    self ----- this can be ignored
    window --- the window that will be used
    """
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
        UPDATE = 20
        START = 21
##        window = Tk()
        
        #main loop
        # self.sw[1] == False means quit
        while self.sw[1] != False:
            # figure out what program to do, through a switch system
            if self.sw[1] == START or not self.sw[0] or self.sw[0] == '':
                self.sw = self.men.mme(self.SetUp.getDefault(), window, self.sw[0]) #this will return a tuple of which item to open, and the database to use
            elif self.sw[0] == NEW:
                self.sw[0] = self.new(window)
##            if self.sw[0] == "":
##                pass
            elif self.sw[1] == DISPLAY:
                if len(self.sw) < 3:
                    self.sw.append(False)
                self.dis = Display.Display(self.sw[0], self.sw[2])
                self.sw = self.dis.cardview(window, self.sw[2])
            elif self.sw[1] == COPY_DATABASE:
                self.sw[0] = self.copy(self.sw[0], window)
                self.sw[1] = START
            elif self.sw[1] == MERGER:
                self.dis = getSecond.getSecond(self.sw[0])
                self.mergeHelp = self.dis.select(window)
                if self.mergeHelp != False:
                    self.dis = merge.merge(self.sw[0],self.mergeHelp)
                    self.dis.combine()
                self.sw[1] = START
            elif self.sw[1] == RESETWL:
                pe = pointEval.worthEval(self.sw[0])
                pe.reset(window)
                self.sw[1] = START
            elif self.sw[1] == DISPLAY_STAT:
                if len(self.sw) < 3:
                    self.sw.append(0)
                self.disA = allDisp.allDisp(self.sw[0], self.sw[2])
                self.sw = self.disA.disp(window)
            elif self.sw[1] == SET_DEFAULT: # change default database
                self.SetUp.setDefault(self.sw[0])
                self.sw[1] = START
            elif self.sw[1] == UBR:
                ubr = UnitBattleReport.battleReport(self.sw[0])
                ubr.display(window)
                self.sw[1] = START
            elif self.sw[1] == AG:
                ag = armyBuilder.buildArmy(self.sw[0])
                self.sw = ag.display(window)
            elif self.sw[1] == UP:
                pe = pointEval.worthEval(self.sw[0])
                pe.update(window)
                self.sw[1] = START
            elif self.sw[1] == AD:
                ad = ArmyDisplay.ArmyDisplay(self.sw[0])
                if len(self.sw) > 2:
                    self.sw = ad.armyView(window, self.sw[2])
                else:
                    self.sw = ad.armyView(window)
##                self.sw = [False, True]
            # clean out the window between each item
            elif self.sw[1] == UPDATE:
                self.updateDB(self.sw[0])
                self.sw[1] = START
            for widget in window.winfo_children():
                widget.destroy()
            # set the default color
            window.configure(background = 'gray95')
        return

    """
    tKinterSetup: creates the window

    parameters:
    self ----- this can be ignored
    """
    def tKinterSetup(self):
        # create the window and then call the setup
        window = Tk()
        window.configure(background = 'gray95')
        self.setUp(window)
        return

# this starts the program
me = Control()
me.tKinterSetup()
