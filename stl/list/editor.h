//designing a text editor like vi.
#ifndef EDITOR
#define EDITOR
#include <list>
#include <string>
using namespace std;
const string COMMAND_START = "$";
const string BLANK = " ";
const string INPUT_ERROR = "WRONG INPUT, PLEASE TRY AGAIN. ";
const string INSERT_COMMAND = "$insert";
const string DELETE_COMMAND = "$delete";
const string LINE_COMMAND = "$line";
const string DONE_COMMAND = "$done";
const string COMMAND_ERROR = "WRONG COMMAND, PLEASE TRY AGAIN.";

//insert part
const string SUCCESSFUL_INPUT = "successful input.";
const int MAX_LINE_LENGTH = 40;
const string LINE_TOO_LONG_ERROR 
            = "the length of line is more than 40.";

//delete part
const string FIRST_TOO_SMALL_ERROR 
            = "the first argument is lower than 0";
const string SECOND_TOO_LARGE_ERROR 
            = "the second argument is larger than the line number";
const string FIRST_LARGER_THAN_SECOND_ERROR 
        = " the first argument is larger than the second argument";
const string OTHER_ERROR 
        = "there are some errors in the command's arguments";

//line part
const string TOO_SMALL_ERROR = "the argument is lower than 0";
const string TOO_LARGR_ERROR 
            = "the argument is larger than the line number";

//done part
const string FINAL_MESSAGE = "Here is the text: \n";

class Editor
{
    protected:
        list<string> text;
        list<string>::iterator currentLine;
        int currentLineNumber;
        bool inserting; // checking whether the state is inserting.
    
    public:
        Editor();

        //FOR THE FUNCTIONS BELOW( except done_command() ), 
        //IF THEY WORK WELL, THEY WILL RETURN BLANKSPACE.
        //IF THERE IS AN ERROR, THE RETURN WILL START WITH COMMAND_START.

        //judging whether the line is a command or an inserting content.
        string parse(const string &line);
        
        //if the line is a command, checking whether it is valid.
        string command_check(const string &line);

        //inserting the line into the current cursor of the text;
        string insert_command(const string &line);

        //deleting the lines between the m th and n th line.(both boundaries are included)
        //prerequisite: 0 <= m <= n < size
        string delete_command(int m, int n);

        //transmitting the cursor to the m th line.
        //prerequisite: 0 <= m <size
        string line_command(int m);

        //finish editting and return the text.
        //put '>' as a cursor at the front of the current line.
        string done_command();

        ~Editor()
        {}
};

#endif