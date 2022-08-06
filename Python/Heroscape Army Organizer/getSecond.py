# Name: Benjamin Jones
# Program: getSecond
# purpose: get a second database

# import

import itertools
import os
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk

class getSecond:
    __slots__ = ["db", "opt"]
    def __init__(self, db="units.db"):
        self.db = db
        self.opt = False
        
    def select(self, window):
#--------------------------------------------START OF TKINTER FUNCTIONS--------------------------------------------
        self.opt = False
        # functions for tkinter window
        def destroy():
            self.opt = False
            window.quit()
        def loadHelp(event = None):
            self.opt = DBfirst.get()
            if self.db == self.opt:
                self.opt = False
            window.quit()
    #--------------------------------------------START OF TKINTER WINDOW--------------------------------------------
##        window = Tk()
        window.geometry("100x100")
        window.title("Second Selector")
        # menu
##        window.bind_class("Text", "<Tab>",focus_next_window)

        # images
##        canvas = Canvas(window, width = 680, height = 130)
##        img = ImageTk.PhotoImage(Image.open(file="images\HImage.jpeg"))
##
        # options from local databases
        fileExt = ".db"
        filePath = os.getcwd()
        files = [_ for _ in os.listdir(filePath) if _.endswith(fileExt) and _ != self.db]
        DBfirst = StringVar(window)
        DBfirst.set(files[0]);

        
        # Labels
        lDOptions = Label(window, text="DATABASE:")

        widgets = [lDOptions]
        
        # Menus
        tDOptions = OptionMenu(
            window,
            DBfirst,
            *files,
        )
        # buttons
        load = Button(
            window,
            text = "Load",
            width = 15,
            height = 1,
            command = loadHelp
            )
        ex = Button(
            window,
            text = "Exit",
            width = 15,
            height = 1,
            command = destroy
            )
        co = 1
##        canvas.grid(row=0,column=co,columnspan = 2,sticky = N+W+E+S)
##        canvas.create_image(680,130, anchor = N+W+E+S, image = img)
        lDOptions.grid(row=1, column=co, sticky =N+W+E+S)
        tDOptions.grid(row=2, column=co, sticky =N+W+E+S)
        load.grid(row=3, column = co, sticky = N+W+E+S)
        ex.grid(row=4, column = co, sticky = N+W+E+S)
#--------------------------------------------END OF TKINTER WINDOW--------------------------------------------
        mainloop()
        return self.opt
