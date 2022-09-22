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
        CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS record(
                                name TEXT,
                                wins INTEGER,
                                losses INTEGER,
                                ratio TEXT,
                                worth REAL,
                                PRIMARY KEY (name))'''

        cursor.execute(CREATE_TABLE)
        CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS bands(
                                name TEXT,
                                wins INTEGER,
                                losses INTEGER,
                                ratio TEXT,
                                unit1 TEXT NULL,
                                quant1 TEXT NULL,
                                unit2 TEXT NULL,
                                quant2 TEXT NULL,
                                unit3 TEXT NULL,
                                quant3 TEXT NULL,
                                unit4 TEXT NULL,
                                quant4 TEXT NULL,
                                unit5 TEXT NULL,
                                quant5 TEXT NULL,
                                unit6 TEXT NULL,
                                quant6 TEXT NULL,
                                unit7 TEXT NULL,
                                quant7 TEXT NULL,
                                unit8 TEXT NULL,
                                quant8 TEXT NULL,
                                unit9 TEXT NULL,
                                quant9 TEXT NULL,
                                unit10 TEXT NULL,
                                quant10 TEXT NULL,
                                unit11 TEXT NULL,
                                quant11 TEXT NULL,
                                unit12 TEXT NULL,
                                quant12 TEXT NULL,
                                unit13 TEXT NULL,
                                quant13 TEXT NULL,
                                unit14 TEXT NULL,
                                quant14 TEXT NULL,
                                unit15 TEXT NULL,
                                quant15 TEXT NULL,
                                PRIMARY KEY (name))
                          '''
        cursor.execute(CREATE_TABLE)
        CREATE_TABLE = '''CREATE TABLE IF NOT EXISTS generals(
                                name TEXT,
                                color TEXT,
                                rank INTEGER,
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
        n = ""
        counter = 0 #keeps count of location in new
        new = [] # the new items
        # for loop to go through each tupple in items, and create a search based
        # on the tupples
        for tup in items:
            if len(tup[1]) > 1 and tup[1][-1] == "S":
                ntup = tup[1][:len(tup[1])-1]
            else:
                ntup = tup[1][:]
            if tup[2] == "OR" or tup[2] == "NOR":
                ors += 1
            if tup[0] == "GRAN":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND " + tup[0][1:].lower() + "<=" + ntup
                else:
                    parts.append(tup[0][1:].lower() + ">=" + ntup)
            elif tup[0] == "LRAN":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND " + tup[0][1:].lower() + ">=" + ntup
                else:
                    parts.append(tup[0][1:].lower() + "<=" + ntup)
            elif tup[0] == "RAN":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND " + tup[0].lower() + "!=" + ntup
                else:
                    parts.append(tup[0].lower() + "=" + ntup)
            elif tup[0] == "POW":
                if tup[2]=="N" or tup[2] == "NOR":
                    n += " AND abilities NOT LIKE \"%" + ntup + "%\""
                else:
                    parts.append(" abilities LIKE \"%" + ntup + "%\"")
            elif tup[0] == "LIFE":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND " + tup[0].lower() + "!=" + ntup
                else:
                    parts.append(tup[0].lower() + "=" + ntup)
            elif tup[0] == "ABIL":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND NOT instr (abilities,\"" + ntup + "\")"
                else:
                    parts.append(" AND instr (abilities,\"" + ntup + "\")")
            elif tup[0] == "CLA":
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND cla NOT LIKE \"" + ntup + "\" AND cla NOT LIKE \"" + ntup +"S\""
                    
                else:
                    parts.append(tup[0].lower() + " LIKE \"" + ntup + "\"")
                    ors += 1
                    parts.append(tup[0].lower() + " LIKE \"" + ntup + "S\"")
                    
            elif ntup == "":
                pass
            else:
                if tup[2] == "N" or tup[2] == "NOR":
                    n += " AND " + tup[0].lower() + " NOT LIKE \"" + ntup + "%\""
                elif tup[2] == "E":# E for Exactly
                    if tup[0] == "RACE":
                        ors += 1
                        parts.append(tup[0].lower() + " LIKE \"" + ntup + "\"")
                        parts.append(tup[0].lower() + " LIKE \"" + ntup + "S\"")
                    else:
                        parts.append(tup[0].lower() + " LIKE \"" + ntup + "\"")
                else:
                    parts.append(tup[0].lower() + " LIKE \"%" + ntup + "%\"")
                if tup[0] == "TY":
                    if ntup == "UNIQUE HERO":
                        if tup[2] == "N" or tup[2] == "NOR":
                            n += " AND ty NOT LIKE \"%UNCOMMON HERO%\""
                        else:
                            ors += 1
                            parts.append("ty LIKE \"%UNCOMMON HERO%\"")
                    elif ntup == "UNIQUE":
                        if tup[2] == "N" or tup[2] == "NOR":
                            n += " AND ty NOT LIKE \"%UNCOMMON%\""
                        else:
                            ors += 1
                            parts.append("ty LIKE \"%UNCOMMON%\"")
                    elif ntup == "COMMON":
                        if tup[2] == "N" or tup[2] == "NOR":
                            n += " AND ty NOT LIKE \"COMMON%\""
                        else:
                            parts.append("ty LIKE \"COMMON%\"")
            if tup[2] == "T":
                
                new.append(list(itertools.combinations(parts, len(parts)-ors)))
                parts.clear()
                counter = counter + 1
                ors = 0
                n = ""
        # end of for loop tup
        # create every combination of the search terms
        
        if ors < 0:
            ors = 0
        new.append(list(itertools.combinations(parts, len(parts)-ors)))
        send = "" # this will be the item to add to the command
        # for loop to create the send item
        for arr in new:
            for item in arr:
                for i in item:
                    send += i
                    if i != item[-1]:
                        send += " AND "
                send += n
                if item != arr[-1]:
                    send += " OR "
            if arr != new[-1]:
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
        cursor = myDB.cursor()
        cursor.execute(command)
        ret = []
        # for each item returned from the search, append that to
        # ret
        for row in cursor.fetchall():
            ret.append(row)
        # sort ret and return ret
        ret = sorted(ret)
        myDB.close()
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

    # function cleaner
    #
    # purpose: clean up the search to get rid of impossible types
    # self - don't need to worry about this
    # mes - the message that will be cleaned
    def cleaner(self, mes):
        pass

    
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
    def display(self, name, test = False):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM units WHERE name=?"""
        cursor.execute(command, (name,))
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        if (test):
            print("end of display, items are:\n")
            print(ret)
        return ret

    # function gatherGeneral
    #
    # purpose: to gather all the units that follow x general
    # self - don't need to worry about this
    # genTup - the general(s) whose army is being gathered
    def gatherGeneral(self, genTup):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        for general in genTup:
            command = """SELECT * FROM units WHERE general =?"""
            cursor.execute(command, (general,))
            for row in cursor.fetchall():
                ret.append(row[0])
        return ret

    def inside(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM units WHERE name=?"""
        cursor.execute(command, (name,))
        ret = cursor.fetchone()
        if ret:
            return True
        return False

#""" --------------- record table section --------------------- """
    # function displayRecord
    #
    # purpose: to gather all the information on a named unit
    # self - don't need to worry about this
    # name - the name of the character to gather info on
    def displayRecord(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM record WHERE name=?"""
        cursor.execute(command, (name,))
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        return ret
    
    # drops the table records
    def dropRecords(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """DROP TABLE IF EXISTS record"""
        cursor.execute(command)
        myDB.commit()
        myDB.close()
    
    # create table records
    def startRecords(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """CREATE TABLE IF NOT EXISTS record(
                                name TEXT,
                                wins INTEGER,
                                losses INTEGER,
                                ratio TEXT,
                                worth REAL,
                                PRIMARY KEY (name))"""
        cursor.execute(command)
        myDB.commit()
        myDB.close()
        
    # gets all of the records
    def getAllRecords(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM record"""
        cursor.execute(command)
        for row in cursor.fetchall():
            ret.append(row)
        myDB.commit()
        myDB.close()
        return ret
    # finds and returns the wins and losses of the character
    def dispWinsLosses(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM record WHERE name=?"""
        cursor.execute(command, (name,))
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        myDB.commit()
        myDB.close()
        return ret

    def addRecord(self, name, wins = 0, losses = 0, ratio = 'N\A', worth = 0.0):
        # set up the database to recieve a new entry
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        try:
            self.recordDelete(name)
        except:
            print(name, " does not exist")
        INSERT_PARAM = ("""INSERT INTO record
                    (name, wins, losses, ratio, worth)
                    VALUES (?, ?, ?, ?, ?)""")
        data_tuple = (name, wins, losses, ratio, worth)
        # execute the command, commit, and close
        cursor.execute(INSERT_PARAM, data_tuple)
        myDB.commit()
        myDB.close()

    # function delete
    #
    # purpose: delete a named entry
    # self - don't need to worry about this
    # name - the name of the character to delete
    def recordDelete(self, name):
        # set up the command and database
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """DELETE FROM record WHERE name=?"""
        # execute, commit, and close
        cursor.execute(command, (name,))
        myDB.commit()
        myDB.close()

    def updateRecord(self, name, wins, losses, worth):
        use = self.displayRecord(name)
        wins += use[1]
        losses += use[2]
        if use[1] != 0 or use[2] != 0:
            ratio = str(use[1]) + '/' + str(use[1] + use[2])
        else:
            ratio = 'N/A'
        self.addRecord(name, wins, losses, ratio, worth)

#""" --------------- bands table section --------------------- """
    def addBands(self, item):
        if item == [] or len(item) < 6 or len(item) % 2 == 1:
            return
        else:
            self.removeBands(item[0]) # remove the band if it already exists
        item[0] = str(item[0])
        item[1] = int(item[1])
        item[2] = int(item[2])
        while len(item) < 34:
            item.append(None)
        for i in range(4,len(item)):
            item[i] = str(item[i])
        INSERT_PARAM = ("""INSERT INTO bands
                        (name, wins, losses, ratio,
                         unit1, quant1, unit2, quant2, unit3, quant3, 
                         unit4, quant4, unit5, quant5, unit6, quant6, 
                         unit7, quant7, unit8, quant8, unit9, quant9, 
                         unit10, quant10, unit11, quant11, unit12, quant12, 
                         unit13, quant13, unit14, quant14, unit15, quant15)
                    VALUES (?, ?, ?, ?, ?,?, ?, ?, ?, ?,?, ?, ?, ?, ?,?, ?, ?, ?, ?,?, ?, ?, ?, ?,?, ?, ?, ?, ?,?, ?, ?, ?)""")
        data_tuple = (tuple(item))
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        cursor.execute(INSERT_PARAM, data_tuple)
        myDB.commit()
        myDB.close()
        return
    def removeBands(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """DELETE FROM bands WHERE name = ?"""
        # execute, commit, and close
        cursor.execute(command, (name,))
        myDB.commit()
        myDB.close()
        return
    def getBand(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT * FROM bands WHERE name = ?"""
        cursor.execute(command, (name,))
        ret = []       
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        myDB.close()
        return ret
    def getWithUnit(self, name):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT * FROM bands WHERE ? in (unit1,unit2,unit3,unit4,unit5,unit6,unit7,unit8,unit9,unit10,unit11,unit12,unit13,unit14,unit15)"""
        cursor.execute(command, (name,))
        ret = []       
        for row in cursor.fetchall():
            for item in row:
                ret.append(item)
        myDB.close()
        return ret
    def getAllBands(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM bands"""
        cursor.execute(command)
        for row in cursor.fetchall():
            ret.append(row)
        myDB.close()
        return ret
#""" --------------- generals table section --------------------- """
    def getAllGenerals(self):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        ret = []
        command = """SELECT * FROM generals"""
        cursor.execute(command)
        for row in cursor.fetchall():
            ret.append(row[0])
        myDB.close()
        return ret

    def getGeneralRank(self, general):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT rank FROM generals WHERE name = ?"""
        cursor.execute(command, (general,))
        ret = cursor.fetchall()
        if len(ret) > 0:
            ret = ret[0][0]
        myDB.close()
        return ret
    
    def getGeneralColor(self, general):
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        command = """SELECT color FROM generals WHERE name = ?"""
        cursor.execute(command, (general,))
        ret = cursor.fetchall()
        if len(ret) > 0:
            ret = ret[0][0]
        myDB.close()
        return ret

    def addGeneral(self, general, color, rank):
        INSERT_PARAM = """INSERT INTO generals
                        (name, color, rank)
                        VALUES (?, ?, ?)"""
        data_tuple = (general, color, rank)
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        cursor.execute(INSERT_PARAM, data_tuple)
        myDB.commit()
        myDB.close()
    def delGeneral(self, general):
        # delete all the units first and then the general
        toDelete = self.gatherGeneral(general)
        for unit in toDelete:
            self.delete(unit)
        UPDATE_PARAM = """DELETE FROM generals WHERE name = ?"""
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        cursor.execute(UPDATE_PARAM, (general,))
        myDB.commit()
        myDB.close()
        
    def updateColor(self, general, color):
        UPDATE_PARAM = """UPDATE generals SET color = ? WHERE name = ?"""
        data_tuple = (color, general)
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        cursor.execute(UPDATE_PARAM, data_tuple)
        myDB.commit()
        myDB.close()

    def updateColor(self, general, rank):
        UPDATE_PARAM = """UPDATE generals SET rank = ? WHERE name = ?"""
        data_tuple = (rank, general)
        myDB = sqlite3.connect(self.db)
        cursor = myDB.cursor()
        cursor.execute(UPDATE_PARAM, data_tuple)
        myDB.commit()
        myDB.close()
