# Name: Benjamin Jones
# Program: popup.py
# Purpose: create popups

# import elements
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk


# class popup
#
# purpose: to manage popups
class PopUp:
    __slots__ = ['ret', 'normFont']
    def __init__(self):
        self.normFont = ("Helvetica", 10)
    # function: popup
    #
    # purpose: set up and run a popup message, with an OK and Cancel button
    def popup(self, mes):
        self.ret = False
        def ok():
            self.ret = True
            win.destroy()
        def cancel():
            win.destroy()
        win = Tk()
        lMes = Label(
            win,
            text = mes
            )
        bOK = Button(
            win,
            text = "OK",
            width = 15,
            command = ok,
            )
        bCancel = Button(
            win,
            text = "Cancel",
            width = 15,
            command = cancel,
            )
        lMes.grid(row = 0, column = 0, columnspan = 2, sticky = N+E+W+S)
        bOK.grid(row = 1, column = 0, sticky = N+E+W+S)
        bCancel.grid(row = 1, column = 1, sticky = N+E+W+S)
        win.mainloop()
        return self.ret
