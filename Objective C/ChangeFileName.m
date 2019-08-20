// Author:	Benjamin Jones
// Purpose:	This is a test program to change file names
// Language:	Objective-c
// Start Date:	July 9th, 2019
// Finish Date:	July 22th, 2019
/*
--------------------------------------------------------------------------------------------- NOTES ---------------------------------------------------------------------------------------------

A note about formatting (for easier reading):
Method names are first letter capitalized of each word (i.e. ChangeName), with the one exception being getLine
Variable names contain capitals for the first letter of each word after the first word (i.e. myString). This has no exceptions.
That should help with quick identification of what something is.

Every method, before it starts, has a method prologue, which contains the method name, return
	type, purpose, parameters, and notes (if any). This is there to explain the essen-
	tial information needed for understanding that method. Also, every method ends with
	a comment.
Example:
/ *
Function:	MyMethod
Type:		void
Purpose:	To be an example
Parameters:	N/A

Notes:		This is an example
* /
void MyMethod(){
... (code) ...
}// end of MyMethod

Comments, other than those appearing at the end of an item, are always atleast two tab
	indentations into the file, usually one more than the item that it is commenting
	on. Never one tab, and only no tabs when they are going to be taken out, or are
	part of the header information.

Sorry that is only a partly done class. Setting those up are confusing, and I think I only started understanding it a bit on the 22nd

The Table of Items contains every section of this program.

Also, thanks to the awesome community at StackOverflow.com, without whom, I would have
	been completely lost when attempting this project. Also, the Apple Developer
	Documentation, those helped me out so many times. And to the many other forums
	that I encountered that helped answer various questions (namely softpixel.com
	for guiding me through creating threads, which was awful, but the threads certainly
	help the program to run quicker).

---------------------------------------------------------------------------------------- TABLE OF ITEMS ----------------------------------------------------------------------------------------
Header information						
imports									 
global variables						
ChangeName							
StringCleaner							
-----  UTILITY FUNCTIONS -----
getLine								
SettextFile		-----  not used, for GUI -----		
SetdirPath		-----  not used, for GUI -----		
GetnumFailed;		-----  not used, for GUI -----		
GetnumSuccess;		-----  not used, for GUI -----		
GetfailedNames;		-----  not used, for GUI -----		
GettotalCounter;	-----  not used, for GUI -----		
----- END OF UTILITY FUNCTIONS -----
CombineTwo							
----- CLASS ThreadManager -----							
MyFileScanner
ReadFile							
----- END OF CLASS -----
main								
*/

//-------------------------------------------------------------------------------------- START OF THE PROGRAM --------------------------------------------------------------------------------------//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h> 
#include <stdlib.h>

//-------------------------------------------------------------------------------------------- GLOBALS ---------------------------------------------------------------------------------------------//

NSMutableArray *filePaths; // it will contain the file path of each item
NSMutableArray *oldNames; // The old names will be placed into this array
NSMutableArray *newNames; // The new names will be placed into this array
NSMutableArray *failedNames; // the failed transitions will be placed here
NSUInteger numFailed; // tracks number of failed name changes
NSUInteger numSuccess; // tracks number of succesful name changes
NSUInteger myKey; // identifier for every thread
NSUInteger aLock; //a(rray)Lock, for keeping the threads around until the array is fully finished
NSUInteger lock; // stops the program from continuing until all items are at the same place
NSUInteger increase = 50; // for the threads, controls how many there are, as well as the increase amount
NSUInteger totalCounter; // total amount in newNames (update order: oldNames, newNames, this)
NSString *textFile; // this will contain the text file address, passed from the GUI
NSString *dirPath; // this will contain the directory path, passed from the GUI
NSString *tFileName; // used for global communication
NSString *address; // it will contain the address for the file, as I don't know how to pass items with a threader yet, and I need to work around that.
//-------------------------------------------------------------------------------------------- METHODS ---------------------------------------------------------------------------------------------//

/*
Function:	ChangeName
Type:		Void
Purpose: Change the name of a give item
Parameters:	NSString* find		- the item whose name needs to change, complete path
		NSString* replace	- the new name, complete path
		NSFileManager* filemgr	- the file manager

Notes:		For some reason, it kept adding a question mark to most of the items (the very
	last item wouldnk't have it), and so I added the system to get rid of the last char-
	acter should it be found to be an illegal character
*/
void ChangeName(NSString* find, NSString* replace, NSFileManager* filemgr){
		// set up a list of legal characters
	NSCharacterSet * set =[[NSCharacterSet characterSetWithCharactersInString:@"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\\ .,\'"] invertedSet];
	NSString *last;
		// While loop to take off excess parts
	while(true){
			// create a substring of the last character
		last = [replace substringFromIndex: [replace length] -1];
			// Make sure that the file doesn't end with an illegal character
			// Delete the last character if it does
		if([last rangeOfCharacterFromSet:set].location != NSNotFound){
			replace = [replace substringToIndex:[replace length] -1];
		}
		else
			break;
	}
		// change the name of the object using moveItemAtPath:toPath:error:
	BOOL result = [filemgr moveItemAtPath:find toPath:replace error:nil];
	if (result)
		numSuccess++;
	else{
		numFailed++;
		[failedNames addObject:find];
	}
		// return nothing because this is a void member
}// end of ChangeName

/*
Function:	StringCleaner
Type:		NSString*
Purpose:	clean up any spaces in the user input so that they all have escape characters
Parameters:	NSString* myString	- The string to be cleaned
*/
NSString* StringCleaner(NSString* myString){
/*
NOTE:		Only one space is being removed at the end of the items information because a
	file can be pure spaces, and when an item is dragged into the field, a space is automatically
	added. So the remove one space is so that the user can drag and press enter. Without
	needing to do any extra work.
*/
		// create a substring of the last character
	NSString *last = [myString substringFromIndex: [myString length] -1];
		// If the last character is a space, remove it
	if([last isEqualToString:@" "]){
		myString = [myString substringToIndex:[myString length] -1];
	}
		// get rid of \,
	myString = [myString stringByReplacingOccurrencesOfString:@"\\," withString:@","];
		// get rid of extra slashes
	myString = [myString stringByReplacingOccurrencesOfString:@"\\ " withString:@" "];
		// remove quatation marks
	myString = [myString stringByReplacingOccurrencesOfString:@"\"" withString:@""];
		// get rid of extra \
	myString = [myString stringByReplacing OccurencesOfString:@"\\" withString:@""];
		// clean up &
		myString = [myString stringByReplacing OccurencesOfString:@"\&" withString:@"&"];

	return myString;
}// end of StringCleaner

/*
Function:	getLine
Type:		NSString*
Purpose:	get user input
Parameters:	N/A

Notes:		This method was created so as to allow me (the author) to have a bit more of
	the feeling that I have with C++, and to have a function that I am familiar with and un-
	derstand with getting user input.
*/
NSString* getLine(){
		// initialize variables
	NSFileHandle *handle = [NSFileHandle fileHandleWithStandardInput];
	NSData *data = handle.availableData;
		// set input to recieve UTF8 items
	NSString *input = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
		// take the user input
	if (input == (id)[NSNull null]){
		NSLog(@"INSIDE OF THE FIRST INPUT IS NULL");
		input = [[NSString alloc]initWithData:data encoding:NSJapaneseEUCStringEncoding];
	}
	NSCharacterSet *set = [NSCharacterSet newlineCharacterSet];
		// trim the user input
	NSString *userInput = [input stringByTrimmingCharactersInSet:set];
		// return the string
	return userInput;
}// end of getLine
//---------------------------------------------------------------- This Section are methods made for better interaction with a GUI -----------------------------------------------------------------//

/*
Function:	SettextFile
Type:		Void
Purpose:	To set the textFile string
Parameters:	NSString* myString	- the new textFile string
*/
void SettextFile(NSString* myString){
	textFile = myString;
}// end of SettextFile

/*
Function:	SetdirPath
Type:		Void
Purpose:	To set the dirPath string
Parameters:	NSString* myString	- the new dirPath string
*/
void	SetdirPath(NSString* myString){
	dirPath = myString;
}// end of SetdirPath

/*
Function:	GetnumFailed
Type:		NSUInteger
Purpose:	To get the numFailed variable
Parameters:	N/A
*/
NSUInteger GetnumFailed(){
	return numFailed;
}// end of GetnumFailed

/*
Function:	GetnumSuccess
Type:		NSUInteger
Purpose:	To get the numSuccess variable
Parameters:	N/A
*/
NSUInteger GetnumSuccess(){
	return numSuccess;
}// end of GetnumSuccess

/*
Function:	GetfailedNames
Type:		NSMutableArray*
Purpose:	To get the failedNames array
Parameters:	N/A
*/
NSMutableArray* GetfailedNames(){
	return failedNames;
}// end of GetfailedNames

/*
Function:	GettotalCounter
Type:		NSUInteger
Purpose:	To get the totalCounter variable
Parameters:	N/A
*/
NSUInteger GettotalCounter(){
	return totalCounter;
}// end of GettotalCounter
//----------------------------------------------------------------------------------------- End of Section -----------------------------------------------------------------------------------------//

/*
Function:	CombineTwo
type:		NSString*
Purpose:	To combine two strings with '/'
Parameters:	NSString* str1		- the first string to combine
		NSString* str2		- the second string to combine
*/
NSString* CombineTwo(NSString* str1, NSString* str2){
	return [NSString stringWithFormat:@"%@%@%@", str1, @"/", str2];
}// end of CombineTwo

// creating a class with a single function, because I need that to create a thread it seems
@interface ThreadManager : NSObject
+(void)MyFileScanner:(id)param;
+(void)ReadFile:(id)param;
@end

@implementation ThreadManager
/*
Function:	MyFileScanner
Type:		Void
Purpose:	To scan the file, prepare the items, and call ChangeName to change the names
Parameters:	N/A

Notes:		This could probably be improved quite a bit, I just kind of figured this out in one day
	and attempted to get it working. I'm sure I made mistakes, but this is my first time doing
	threading in Objective-C, and it's bloody annoying
*/
+(void)MyFileScanner:(id)param{
		// initiate variables
	NSString *find, *replace;
		// set the key to the current myKey value, and decrement it one (there's a wait of usleep(2) between every thread, so that they can each have their own value)
	NSUInteger key = myKey--;
		// initiate a NSFileManager object. It would be nice to just have one of these. But I can't pass it around, and I don't feel secure making this a global
	NSFileManager* filemgr = [[[NSFileManager alloc] init] autorelease];
		// initiate counting to be equal to the key
	NSUInteger counting = key;
		// while loop to change the item names, stay in the loop until aLock is finished and counting is greater than the total counter (just to be sure about what is being done.
	while (counting < totalCounter || aLock == 0){
			// set find and replace to be equal to their respective items
		find = [oldNames objectAtIndex:counting];
		replace = [newNames objectAtIndex:counting];
			// clean find and replace
		find = StringCleaner(find);
		replace = StringCleaner(replace);
			// combine the directory, folder paths, and find/replace
		find = CombineTwo(tFileName, CombineTwo([filePaths objectAtIndex:counting], find));
		replace = CombineTwo(tFileName, CombineTwo([filePaths objectAtIndex:counting], replace));
			// call the scanFile function to scan and replace
		ChangeName(find, replace, filemgr);
			// increment counting by increase
		counting = counting + increase;
	}// end of while loop
		// increment lock by 1
	lock++;
}// end of FileScanner
/*
Function:       ReadFile
Type:           NSData*
Purpose:        Read a file and place the items into the newName array and oldName array
Parameters:     N/A

Notes:		This originally was a pure global function, however I needed to run a thread
	through this. And so I made it into this. It should need a parameter of NSString* address,
	however, I couldn't figure out how to send that through. So I made it into a global variable
	as that is the only way I currently know of to get this working. And I need it to work.
*/
+(void)ReadFile:(id)param{//(NSString* address, NSFileManager* filemgr){
		// initiate a NSFileManager object
	NSFileManager* filemgr = [[NSFileManager alloc] init];
		// Create the array
	NSArray *ary = [[[NSArray alloc] init] autorelease];
		// verify that the file exists
	if (![filemgr fileExistsAtPath:address]){
			// if it doesn't, throw an error
		NSException* myException = [[[NSException alloc] initWithName:@"NO FILE AT DESIGNATED PATH" reason:@"ファイルが存在しません" userInfo:nil] autorelease];
		[myException raise];
	}// end of if statement
		// Create a file item, opened to address
	FILE *file = fopen([address UTF8String], "r");
		// Create a very large char buffer (it'll hold more than it will ever need)
	char buffer[250];
		// create the string to hold each line
	NSString* line;
		// create a counter
	NSUInteger counter = 0;
		// do a while loop until you reach the end of the file
	while (fgets(buffer, sizeof(char)*250, file) != NULL){
			// set line to hold a line from the buffer
		line = [NSString stringWithFormat:@"%s", buffer];
			// separate the items by tabbed spaces into an array
	        ary = [line componentsSeparatedByString:@"\t"];
				// make sure that the array has more than 2 items in it
        	        if ([ary count] > 2)
              		        {
					// make sure the counter is greater than 0 (the first line in the files are items stating what is in each column
		                if (counter > 0){
						// add the first (0th) item to filePaths
					[filePaths addObject:[ary objectAtIndex:0]];
						// add the second (1st) item to oldNames
                		        [oldNames addObject:[ary objectAtIndex:1]];
						// add the third (2nd) item to newNames
                			[newNames addObject:[ary objectAtIndex:2]];
						// increment the total counter
			        	totalCounter++;
        		        }// end of if statement
			}// end of first if statement
				// if there are 2 or less items in the array, tell the user that it could not read a file at the line number
			else
				NSLog(@"Could Not read a file at line %lu", (counter + 1));
			// increment the counter
                counter++;
	}// end of while statement
		//signify that the document has now fully been read
	aLock = 1;
}// end of ReadFile
@end


/*
Function:	main
Type:		int
Purpose:	start the program
Parameters:	N/A
*/
int main (int argc, const char * argv[]){
		// create the pool
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		// initialize try block
@try{
		// set the over all counter to zero
	NSUInteger tCounter = 0;
		// create the file manager
	NSFileManager *filemgr = [[NSFileManager defaultManager] autorelease];
	filePaths = [[[NSMutableArray alloc] init] autorelease];
	oldNames = [[[NSMutableArray alloc] init] autorelease];
	newNames = [[[NSMutableArray alloc] init] autorelease];
	failedNames = [[[NSMutableArray alloc] init] autorelease];
		// start a while loop, on first line because this is essentially where the method starts
while (tCounter < 1){
	myKey = increase;
	myKey--;
	aLock = 0;
	lock = 0;
		// clear the screan
	system("clear");
		// initialize globals
	numFailed = 0;
	numSuccess = 0;
	totalCounter = 0;
		// ask for the file address
	printf("ファイル名のリストファイル（タブ区切りテキスト）をドラッグします\n");
		// get the file address
	tFileName = getLine();
		// clean it
	address = StringCleaner(tFileName);
		// detach a thread to start reading the file	
	[NSThread detachNewThreadSelector:@selector(ReadFile:) toTarget:[ThreadManager class] withObject:nil];
		// create find and replace
	NSString * find;
	NSString * replace;
		// ask for the address of the items
	printf("親フォルダをドラッグします\n");
	tFileName = getLine();
NSLog(@"%@", tFileName);
		// start timeing
	NSDate *start = [NSDate date];
		// clean it
	tFileName = StringCleaner(tFileName);
		// verify that the file exists
	if (![filemgr fileExistsAtPath:tFileName]){
			// if it doesn't, throw an error
		NSException* myException = [[[NSException alloc] initWithName:@"NO DIRECTORY AT DESIGNATED PATH" reason:@"ディレクトリが存在しません" userInfo:nil] autorelease];
		[myException raise];
	}// end of if statement
		// set the counter to 0
	NSUInteger counter = 0;
		// create as many threads as increase says to
	while (counter < increase){
		[NSThread detachNewThreadSelector:@selector(MyFileScanner:) toTarget:[ThreadManager class] withObject:nil];
			// wait 2 between every thread (to be safe that the key has changed
		usleep(2);
			// increment the counter by one
		counter++;
	}// end of while loop
		// wait until all the threads are finished
	while(lock < increase){
	}
		// display num success and failures
	printf("合計：%lu\n成功：%lu\n失敗：%lu\n", totalCounter, numSuccess, numFailed);
		// stop timing
	NSTimeInterval timeInterval = [start timeIntervalSinceNow];
		// if some items failed, ask the user if they desire to have the failed items printed out
	if (numFailed > 0){
		printf("文書を文書に書き込むには\"Y\"を押してください\n");
		tFileName = getLine();
		tFileName = [tFileName uppercaseString];
			// if the answer is yess, print out the items
		if ([tFileName isEqualToString:@"Y"]){
			[filemgr createFileAtPath:@"./COULD_NOT_CHANGE.txt" contents:nil attributes:nil];
			NSFileHandle *fileHandle = [NSFileHandle fileHandleForWritingAtPath:@"./COULD_NOT_CHANGE.txt"];
			[fileHandle seekToEndOfFile];
			NSUInteger counting = 0;
			for (NSString* key in failedNames){
				[fileHandle writeData:[key dataUsingEncoding:NSUTF8StringEncoding]];
				if (counting < numFailed)
					[fileHandle writeData:[@"\n" dataUsingEncoding:NSUTF8StringEncoding]];
			}// end of for statement
				// close the file
			[fileHandle closeFile];
		}// end of if statement
	}// end of if statement
		// format the timeInterval
	if (timeInterval < 0)
		timeInterval *= (-1);
	printf("終了まで%f秒\n", timeInterval);
	tCounter++;
	printf("再度実行するには”Y”を入力、終了するにはそのままエンター\n");
	tFileName = getLine();
	tFileName = [tFileName uppercaseString];
	if ([tFileName isEqualToString:@"Y"])
		tCounter--;
		// empty the arrays, make sure to do it right
	[filePaths removeAllObjects];
	[oldNames removeAllObjects];
	[newNames removeAllObjects];
	[failedNames removeAllObjects];
}
}// end of try block
@catch (NSException *exception){
	NSLog(@"%@", exception.reason);
}
@finally{
	NSLog(@"End condition");
}
		// drain the pool
	[pool drain];
	return 0;
}// end of main
//--------------------------------------------------------------------------------------- END OF PROGRAM ---------------------------------------------------------------------------------------//

