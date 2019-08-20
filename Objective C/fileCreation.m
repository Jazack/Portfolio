// Author:	Benjamin Jones
// Purpose:	This is a test program to change file names
// Language:	Objective-c
// Start Date:	July 9th, 2019
// Finish Date:

//----------------------------------START OF THE PROGRAM----------------------------------//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h> 
#include <stdlib.h>
// Global items
NSMutableArray *filePaths; // it will contain the file path of each item
NSMutableArray *oldNames; // The old names will be placed into this array
NSMutableArray *newNames; // The new names will be placed into this array
NSMutableArray *failedNames; // the failed transitions will be placed here
NSUInteger numFailed; // tracks number of failed name changes
NSUInteger numSuccess; // tracks number of succesful name changes
NSUInteger totalCounter; // total amount in newNames (update order: oldNames, newNames, this)
NSString *textFile; // this will contain the text file address, passed from the GUI
NSString *dirPath; // this will contain the directory path, passed from the GUI

/*
Function:	StringCleaner
Type:		NSString*
Purpose:	clean up any spaces in the user input so that they all have escape characters
Parameters:	NSString* myString	- The string to be cleaned
*/
NSString* StringCleaner(NSString* myString){
		// create a substring of the last character
	NSString *last = [myString substringFromIndex: [myString length] -1];
		// If the last character is a space, remove it
	if([last isEqualToString:@" "]){
		myString = [myString substringToIndex:[myString length] -1];
	}
		// get rid of extra slashes
	myString = [myString stringByReplacingOccurrencesOfString:@"\\ " withString:@" "];
		// remove quatation marks
	myString = [myString stringByReplacingOccurrencesOfString:@"\"" withString:@""];
		// I realized I could just do this, instead of separting via array first
	return myString;//[myString stringByReplacingOccurrencesOfString:@" " withString:@"\\ "];
}// end of StringCleaner

/*
Function:	getLine
Type:		const char*
Purpose:	get user input
Parameters:	N/A

Notes:		This method was created so as to allow me (Benjamin Jones) to have a bit more of
	the feeling that I have with C++, and to have a function that I am familiar with and un-
	derstand with getting user input.
		At the end, this will be used to get the file that contains the name information,
	currently it is being used to get the user input for what file to change the name from
	and to
*/
const char* getLine(){
		// initialize variables
	NSFileHandle *handle = [NSFileHandle fileHandleWithStandardInput];
	NSData *data = handle.availableData;
		// set input to recieve UTF8 items
	NSString *input = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
		// take the user input
	NSCharacterSet *set = [NSCharacterSet newlineCharacterSet];
		// trim the user input
	NSString *userInput = [input stringByTrimmingCharactersInSet:set];
		// place it into a const char*
	const char* destination = [userInput cStringUsingEncoding:[NSString defaultCStringEncoding]];
		// return destination
	return destination;
}// end of getLine
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

/*
Function:	ScanFile
Type:		void
Purpose:	prepare everything for the ScanHelper method
Parameters:	NSString* find		- the name of the item being looked for
		NSString* replace	- the new name of the item
		NSString* directory	- the directory to be searched

Notes:		This method is still going to change quite a bit, it'll have another parameter, so
	as to set up the helper function in searching in the proper file(s).
		Also, why doesn't MAC allow "==" in objective-c? That would have saved time.
*/
void ScanFile(NSString* find, NSString* replace){//, NSString* directory){
		// initialize variables
	NSFileManager *filemgr = [NSFileManager defaultManager];
if ([filemgr fileExistsAtPath:find]){
	NSLog(@"File exits at %@", find);
}
}

/*
Function:	FormatFolders
Type:		NSString*
Purpose:	To format an item properly into folders
Parameters:	NSString* toFormat	- the string that needs to be formatted
*/

/*
Function:	ReadFile
Type:		NSData*
Purpose:	read a file and place the items into the newName array and oldName array
Parameters:	NSString* address	- the address of the file being read
*/
void ReadFile(NSString* address){
NSArray *ary;
FILE *file = fopen([address UTF8String], "r");
char buffer[256];
NSString *line;
NSUInteger counter = 0;
while (fgets(buffer, sizeof(char)*256, file) != NULL){
	line = [NSString stringWithFormat:@"%s", buffer];
    	ary = [line componentsSeparatedByString:@"\t"];
		if ([ary count] > 0)
			{
		if (counter > 0){
			[filePaths addObject:[ary objectAtIndex:0]];
			[oldNames addObject:[ary objectAtIndex:1]];
			totalCounter++;
		}
		}
		counter++;
	}
}// end of ReadFile

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
		// start a while loop;
while (tCounter < 1){

	NSFileManager *filemgr = [NSFileManager defaultManager];
		// initialize globals
	system("clear");
	numFailed = 0;
	numSuccess = 0;
	totalCounter = 0;
	filePaths = [[NSMutableArray alloc] init];
	oldNames = [[NSMutableArray alloc] init];
	newNames = [[NSMutableArray alloc] init];
	failedNames = [[NSMutableArray alloc] init];
		// create the char* to hold addresses
	const char * fileName;
		// ask for the file address
	printf("Please enter (drag) the file address that you wish to read\n");
		// get the file address
	fileName = getLine();
		// format it
	NSString * tFileName = [NSString stringWithUTF8String:fileName];
		// clean it
	tFileName = StringCleaner(tFileName);
		// read the items into a new string
	ReadFile(tFileName);
		// create find and replace
	NSString * find;
	NSString * replace;
		// ask for the address of the items
	printf("Please list (drag) the folder that contains all the items\n");
	fileName = getLine();
		// format it properly
	tFileName = [NSString stringWithUTF8String:fileName];
	tFileName = StringCleaner(tFileName);
		// set the counter to 0
	NSUInteger counting = 0;
		// while loop to change the item names
	while (counting < totalCounter){
		find = [oldNames objectAtIndex:counting];
		find = StringCleaner(find);
		tFileName = CombineTwo(tFileName, [filePaths objectAtIndex:counting]);
		if (![filemgr fileExistsAtPath:tFileName])
			[filemgr createDirectoryAtPath:tFileName withIntermediateDirectories:0 attributes:nil error:nil];
			// combine the directory, folder paths, and find/replace
		find = CombineTwo(tFileName, find);
			// call the scanFile function to scan and replace
		[filemgr createFileAtPath:find contents:nil attributes:nil];
		counting++;
	}// end of while loop
/*		// display num success and failures
	printf("SUCCESSES: %lu\nFAILURES: %lu\n", numSuccess, numFailed);
	if (numFailed > 0){
		printf("TO SEE THE FAILED ITEMS, PRESS \"Y\"\n");
		fileName = getLine();
		tFileName = [NSString stringWithUTF8String:fileName];
		if ([tFileName isEqualToString:@"Y"])
			NSLog(@"%@", failedNames);
	}
*/
	tCounter++;
	printf("IF YOU WISH TO DO ANOTHER SET, SUBMIT \"Y\", ELSE, SUBMIT ANYTHING ELSE\n");
	fileName = getLine();
	tFileName = [NSString stringWithUTF8String:fileName];
	if ([tFileName isEqualToString:@"Y"])
		tCounter--;
}
}// end of try block
@catch (NSException *exception){
	NSLog(@"%@", exception.reason);
}
@finally{
	NSLog(@"Finally condition");
}

		// drain the pool
	[pool drain];
	return 0;
}// end of main
//--------------------------------------------------------------------------------------- END OF PROGRAM ---------------------------------------------------------------------------------------//
