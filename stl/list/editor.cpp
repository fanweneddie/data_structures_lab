#include "editor.h"

//initializing constructor
Editor::Editor()
{
    currentLine = text.begin();
    currentLineNumber = -1;
    inserting = false;
}

//Line parsing
//judging whether the line is a command or an inserting content.
//if successful, return BLANKSPACE.
string Editor::parse(const string &line)
{
    if( line.substr(0,1) != COMMAND_START)
    {
        if( inserting )
            return insert_command(line);
        else
        {
            return COMMAND_START + INPUT_ERROR;
        }
    }

    else
    {
        return command_check(line);
    }
}

//if the line is a command, checking whether it is valid.
//if successful, return BLANKSPACE.
string Editor::command_check(const string& line)
{
    int blank_pos1 = line.find(BLANK);
    string command;

    // having the blank,such as $delete 2 3 or $line 4
    if( blank_pos1 >=0 )  
        command = line.substr(0, blank_pos1);
    //no blank, such as $insert or $done
    else
        command = line;

    if( command == INSERT_COMMAND )
    {
        inserting = true;
        return BLANK;
    }
    
    if( command == DELETE_COMMAND )
    {
        int blank_pos2 = line.find( BLANK,blank_pos1 + 1 );
        string m1 = line.substr(blank_pos1 + 1 , 
                            blank_pos2 - blank_pos1 -1);
        string n1 = line.substr(blank_pos2 + 1);
        int m = atoi( m1.c_str() );
        int n = atoi( n1.c_str() );
        return delete_command(m, n);
    }

    if( command == LINE_COMMAND )
    {
        string m1 = line.substr(blank_pos1 + 1);
        int m = atoi( m1.c_str() );
        return line_command(m);
    }

    if( command == DONE_COMMAND )
    {
        return done_command();
    }

    return COMMAND_START + COMMAND_ERROR;
}

//inserting the line into the current cursor of the text;
//if successful, return BLANKSPACE.
string Editor::insert_command(const string&line)
{
    if( line.size() > MAX_LINE_LENGTH )
    {
        return COMMAND_START + LINE_TOO_LONG_ERROR;
    }

    currentLine = text.insert(++currentLine, line);
    currentLineNumber++;
    return BLANK;
}

//deleting the lines between the m th and n th line.(both boundaries are included)
//prerequisite: 0 <= m <= n < size
//if successful, return BLANKSPACE.
string Editor::delete_command(int m , int n)
{
    if( m <= 0 )
        return COMMAND_START + FIRST_TOO_SMALL_ERROR;
    if( n >= text.size() )
        return COMMAND_START + SECOND_TOO_LARGE_ERROR;
    if( m > n )
        return COMMAND_START + FIRST_LARGER_THAN_SECOND_ERROR;

    list<string>::iterator it = text.begin();
    for (int i = 0; i <= m;i++)
        
        it++;

    for (int i = m; i <= n;i++)
    {
        text.erase(it++);
    }
    //dealing with the change of the cursor
    if( currentLineNumber >= m && currentLineNumber <= n )
    {
        currentLineNumber = m - 1;
        currentLine--;
    }
    else if(currentLineNumber > n)
    {
        currentLineNumber -= (n - m + 1);
    }

    return BLANK;
}

//transmitting the cursor to the m th line.
//prerequisite: 0 <= m <size
//if successful, return BLANKSPACE.
string Editor::line_command(int m)
{
    if( m < 0 )
        return COMMAND_START + TOO_SMALL_ERROR;
    if( m >= text.size() )
        return COMMAND_START + TOO_LARGR_ERROR;

    
    if( currentLineNumber < m )
    {
        for (int i = currentLineNumber; i < m;i++)
        {
            currentLine++;
        }
    }

    else if( currentLineNumber > m )
    {
        for (int i = currentLineNumber; i > m;i--)
        {
            currentLine--;
        }
    }

    currentLineNumber = m;
    return BLANK;
}

//finish editting and return the text.
//put '>' as a cursor at the front of the current line.
//if successful, return the text with a cursor.
string Editor::done_command()
{
    string textStirng = FINAL_MESSAGE;
    
    if( currentLineNumber == -1 )
        textStirng += ">\n";
    
    else
    {
        for(list<string>::iterator itr = text.begin();
            itr != text.end();itr++)
        {
            if(itr == currentLine )
                textStirng += (">" + *itr + "\n");
            else
                textStirng += (" " + *itr + "\n");
        }
    }

    return textStirng;
}
