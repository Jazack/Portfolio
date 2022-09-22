##Name: Benjamin Jones
##Program: new.py
##Purpose: gets a new name

import shutil
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial

class new:
    
    def __init__(self):
        pass
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
