# Name: Benjamin Jones
# Program: Card Database Maker
# purpose: make and manage a database using sqlite

# imports
import sqlite3
import itertools
import os

## class Read Files
#
# purpose: read and manage the databse
class ReadFiles:
    # function __init__
    #
    # self - self, you don't need to worry about this
    # db - the database location
    def __init__(self, db):
        # verify that db is a proper database
        if len(db) > 3:
            temp = db[len(db)-3:]
        else:
            temp = "new"
        if temp != ".db":
            self.db = db + ".db"
        else:
            self.db = db
        # set up the database, if the database doesn't exist
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS units(
                                name TEXT,
                                general TEXT,
                                race TEXT,
                                ty TEXT,
                                cla TEXT,
                                personality TEXT,
                                size TEXT,
                                life INTEGER,
                                move INTEGER,
                                ran INTEGER,
                                attack INTEGER,
                                defense INTEGER,
                                points INTEGER,
                                abilities TEXT,
                                quantity INTEGER,
                                PRIMARY KEY (name))'''

        cursor.execute(CREATE_TABLE)
        myDB.commit()
        myDB.close()

    # function custSearch
    #
    # self - don't need to worry about this
    # items - tupple, contains the items used for the search
    def custSearch(self, items):
        # set up variables
        command = "SELECT * FROM units WHERE "
        parts = []
        ors = 0
        added = False
        n = ""
        # for loop to go through each tupple in items, and create a search based
        # on the tupples
        for tup in items:
            if len(tup[1]) > 1 and tup[1][-1] == "S":
                ntup = tup[1][:len(tup[1])-1]
            else:
                ntup = tup[1][:]
            if tup[2] == "OR":
                ors += 1
            if tup[0] == "GRAN":
                if tup[2] == "N":
                    n += " AND " + tup[0][1:].lower() + "<=" + ntup
                else:
                    parts.append(tup[0][1:].lower() + ">=" + ntup)
            elif tup[0] == "LRAN":
                if tup[2] == "N":
                    n += " AND " + tup[0][1:].lower() + ">=" + ntup
                else:
                    parts.append(tup[0][1:].lower() + "<=" + ntup)
            elif tup[0] == "RAN":
                if tup[2] == "N":
                    n += " AND " + tup[0][1:].lower() + "!=" + ntup
                else:
                    parts.append(tup[0].lower() + "=" + ntup)
            elif tup[0] == "POW":
                if tup[2]=="N":
                    n += " AND abilities NOT LIKE \"%<POWER>" + ntup + "<%\""
                else:
                    parts.append(" abilities LIKE \"%<POWER>" + ntup + "<%\"")
            else:
                if tup[2] == "N":
                    n += " AND " + tup[0].lower() + " NOT LIKE \"%" + ntup + "%\""
                else:
                    parts.append(tup[0].lower() + " LIKE \"%" + ntup + "%\"")
                if tup[0] == "TY":
                    if ntup == "UNIQUE HERO":
                        if tup[2] == "N":
                            n += " AND ty NOT LIKE \"%UNCOMMON HERO%\""
                        else:
                            ors += 1
                            parts.append("ty LIKE \"%UNCOMMON HERO%\"")
                    if ntup == "UNIQUE":
                        if tup[2] == "N":
                            n += " AND ty NOT LIKE \"%UNCOMMON%\""
                        else:
                            ors += 1
                            parts.append("ty LIKE \"%UNCOMMON%\"")
        # end of for loop tup
        # create every combination of the search terms
        new = list(itertools.combinations(parts, len(parts)-ors))
        send = "" # this will be the item to add to the command
        # for loop to create the send item
        for item in new:
            for i in item:
                send += i
                if i != item[-1]:
                    send += " AND "
            send += n
            if item != new[-1]:
                send += " OR "
        # end of for loop item
        #finish formatting send
        if send[:5] == " AND ":
            send = send[5:-1]
        if send[-1] == "%":
            send += "\""
        # append send to command and run it through the database
        command += send
        myDB = sqlite3.connect(self.db)
        cursor=myDB.cursor()
        cursor.execute(command)
        ret = []
        # for each item returned from the search, append that to
        # ret
        for row in cursor.fetchall():
            ret.append(row)
        # sort ret and return ret
        ret = sorted(ret)
        return ret

    # function cust search help
    #
    # purpose: to help with the custom search\
    # items - items to be searched through
    def custSearchHelp(self, items):
        # set variables
        ret = []
        temp = []
        custQ = []
        searchStart = False
        # verify that items has enough information to be used
        if len(items) < 2:
            return None
        # for loop to format and run custSearch for the various items
        for tup in items:
            if searchStart and tup[0] == "POWER":
                if len(temp) > 0:
                    ret.append(tuple(self.custSearch(temp)))
                else:
                    ret.append(None)
                temp = []
            elif tup[0] == "POWER":
                searchStart = True
            else:
                temp.append(tup)
        #end of for loop tup
        #check for last one
        if len(temp) > 0:
            ret.append(tuple(self.custSearch(temp)))
        else: ret.append(None)
        # return ret, does it really need a comment?
        return ret

    # function add
    #
    # purpose: adds to the database
    # variables: each variable is one of the characteristics on the army card
    def add(self, name, general, race, ty, cla, personality, size, life, move, ran, attack, defense, points, abilities, quantity):
        # set up the database to recieve a new entry
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        try:
            self.delete(name)
        except:
            print(name, " does not exist")
        INSERT_PARAM = ("""INSERT INTO units
                    (name , general, race, ty, cla, personality , size, life, move, ran, attack, defense, points, abilities, quantity)
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""")
        data_tuple = (name, general, race, ty, cla, personality, size, life, move, ran, attack, defense, points, abilities, quantity)
        # execute the command, commit, and close
        cursor.execute(INSERT_PARAM, data_tuple)
        myDB.commit()
        myDB.close()

    # function delete
    #
    # purpose: delete a named entry
    # self - don't need to worry about this
    # name - the name of the character to delete
    def delete(self, name):
        # set up the command and database
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """DELETE FROM units WHERE name=?"""
        # execute, commit, and close
        cursor.execute(command, (name,))
        myDB.commit()
        myDB.close()

    # function getAll
    #
    # purpose: get all the units
    def getAll(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT * FROM units"""
        ret = []
        cursor.execute(command)
        for row in cursor.fetchall():
            ret.append(row[0])
        return ret

    # function getAllBut
    #
    # purpose: to retrieve all the units excepting the named unit
    # self - don't need to worry about this
    # name - the name of the character to exclude
    def getAllBut(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT * FROM units WHERE name != ?"""
        ret = []
        cursor.execute(command, (name,))
        for row in cursor.fetchall():
            ret.append(row[0])
        return ret

    # function display
    #
    # purpose: to gather all the information on a named unit
    # self - don't need to worry about this
    # name - the name of the character to gather info on
    def display(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM units WHERE name=?"""
        cursor.execute(command, (name,))
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        return ret

    # function gatherGeneral
    #
    # purpose: to gather all the units that follow x general
    # self - don't need to worry about this
    # general - the general whose army is being gathered
    def gatherGeneral(self, general):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT * FROM units WHERE general=?"""
        ret = []
        cursor.execute(command, (general,))
        for row in cursor.fetchall():
            ret.append(row[0])
        return ret
