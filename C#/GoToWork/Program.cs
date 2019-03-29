// Project Prolog
// Name: Benjamin Jones
// CS 1400 Section 002
// Project: GoToWork
// Date: 3/2/2016 10:09:47 AM
// Purpose: Demonstrate the concepts of writing class UML Diagrams, class Fields, Properties & Methods
//          class static Methods. Also to show how to change the Console's appearance.
//
// I declare that the following code was written by me or provided 
// by the instructor for this project. I understand that copying source
// code from any other source constitutes cheating, and that I will receive
// a zero on this project if I am found in violation of this policy.
// ----------------------------------------------------------------------------------------------------

using System;
using static System.Console;

namespace GoToWork
{
    static public class Program
    {
        /// Method Prolog
        /// <summary>
        /// Purpose: Entry point this C# Program
        /// </summary>
        static public void Main()
        {
            Work.StartProgram(new Work());      //Calls the static method and passes a reference to Work Instance object
        }//End Main()
    }//End class Program
    /// <summary>
    /// Hybrid class, has both instance and static members
    /// </summary>
    public class Work
    {
        //------------------------- instance fields (variables) and static feilds (const is also static)
        private const double FREEZE = 32.0;
        private const string SAT = "SAT";
        private const string SUN = "SUN";
        private const string MON = "MON";
        private const string TUE = "TUE";
        private const string WED = "WED";
        private const string THU = "THU";
        private const string FRI = "FRI";
        private const string HEAD = "------------ Super-Duper Console Application ---------------\n\n";
        private const string MNU = "\t------ Select one of the tests below: ------\n\t1) If-Else Test:\n\t2) Switch Test:\n\t3) Conditional Test:\n\t4) Exit Program:\n\n\t\tEnter your selection:  ";
        private const string WK_END = "Stay home and have fun";
        private const string WRK_DAY = "Nice day; however, you have to go to work";
        private const string TEM_DAY = "Go to work and wear a warm coat"; 
        private const string TODAY = "\n\tWhat is the day-of-the-week?  ";
        private const string CURRENT_TEMP = "Enter the current temperature in degees F: ";
        private const string EXIT = "\t\t\tExiting the program\n\t\tGoodbye... ";
        private const string ERROR_MSG_1 = "Incorrect menu item selected: ";
        private const string ERROR_MSG_2 = "Temperature value is invalid: ";
        private string today;
        /// <summary>
        /// Instance Constructor
        /// </summary>
        public Work()
        {
            today = string.Empty;
        }
        /// <summary>
        /// static class to call the Menu()
        /// </summary>
        /// <param name="wrk"></param>
        static public void StartProgram(Work wrk)
        {
            wrk.Menu();
        }
        /// <summary>
        /// Gets user input to determine what method to run or Exit the program
        /// </summary>
        public void Menu()
        {
            string orgInput = "";
            string input = "";
            int menuItem = -1;
            string localToday = "";
            Work.ConsoleSetUp();
            do
            {
                Clear();
                WriteLine(HEAD);
                Write(MNU);
                input = ((orgInput = ReadLine())=="") ? "5" : orgInput;
                if(int.TryParse(input, out menuItem)==false)
                {
                    WriteLine($"{ERROR_MSG_1} -> {input}");
                    ReadKey(true);
                    continue;
                }
                else
                {
                    // switch statement to find if one should go for work
                    switch(menuItem)
                    {
                        case 1:
                            localToday = DayOfWeek;
                            If_ElseTest();
                            break;
                        case 2:
                            localToday = DayOfWeek;
                            SwitchTest();
                            break;
                        case 3:
                            localToday = DayOfWeek;
                            ConditionalTest();
                            break;
                        case 4:
                            WriteLine($"{EXIT}");
                            ReadKey(true);
                            return;
                        default:
                            WriteLine($"{ERROR_MSG_1} -> {menuItem}");
                            ReadKey(true);
                            continue;
                    }
                }

            } while (true);
        }
        /// <summary>
        /// Tests the if-else conditional
        /// </summary>
        public void If_ElseTest()
        {
            if (today==SUN || today==SAT)
            {
                WriteLine(WK_END);
            }
            else
            {
                WriteLine(TemperatureTest());
            }
            ReadKey(true);
        }
        /// <summary>
        /// Tests the use of the switch() conditional
        /// </summary>
        public void SwitchTest()
        {
            switch (today)
            {
                case SAT:
                case SUN:
                    WriteLine(WK_END);
                    break;
                case MON:
                case TUE:
                case WED:
                case THU:
                case FRI:
                    WriteLine(TemperatureTest());
                    break;
                default:

                    break;
            }
            ReadKey(true);
        }
        /// <summary>
        /// Tests the use of a ?: operator
        /// </summary>
        public void ConditionalTest()
        {
            WriteLine((today==SAT || today==SUN) ? WK_END : TemperatureTest());
            ReadKey(true);
        }
        /// <summary>
        /// Gets the day-of-week from the user, determines if it is valid and returns a (3) char string for the dofw
        /// sets the "today" class level variable with this value
        /// </summary>
        public string DayOfWeek
        {
            get
            {
                string input = string.Empty;
                string origionalInput = string.Empty;
                bool state = false;
                do
                {
                    Clear();
                    Write(TODAY);
                    origionalInput = input = ((input = ReadLine().ToUpper()) == "" || input.Length <3) ? "unknown" : input;
                    input = $"{input[0]}{input[1]}{input[2]}";
                    state = (input == SAT || input == SUN || input == MON || input == TUE || input == WED || input == THU || input == FRI);
                } while (input=="unk");
                today = input;
                return input;
            }
        }
        /// <summary>
        /// Gets a valid current temperature in degrees farenheight and returns a string message
        /// </summary>
        /// <returns>returns the proper message for temperature during the work week</returns>
        public string TemperatureTest()
        { 
            //Store the temperature in double in temp
            string input = string.Empty;
            double temp = -1.0;
            //put this code in a loop
            do
            {
                Clear(); 
                //Ask the user what is the temperature in degrees Farenhiet
                Write($"{CURRENT_TEMP}");
                if(double.TryParse(input=ReadLine(), out temp)==false)
                {
                    WriteLine($"{ERROR_MSG_2} {input}");
                    ReadKey(true);
                    continue;
                }//if temp > 32o return "Go to work else return "Go to work an wear a coat"
                return (temp > FREEZE) ? WRK_DAY : TEM_DAY;
            } while (true);
        }
        static public void ConsoleSetUp()
        {
            Console.BackgroundColor = ConsoleColor.White;
            ForegroundColor = ConsoleColor.DarkBlue;
            int height = Console.WindowHeight;
            int width = WindowWidth;
            int max_height = Console.LargestWindowHeight;
            int max_width = LargestWindowWidth;
            WindowWidth = max_width / 4;
            WindowHeight = max_height / 2;
            Console.Beep();
            Clear();
        }
    }//End class Work
}//End namespace GoToWork

