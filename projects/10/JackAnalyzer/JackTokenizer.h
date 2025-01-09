#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <deque>

const int KEYWORD = 100;
const int SYMBOL = 101; 
const int IDENTIFIER = 102; 
const int INT_CONST = 103; 
const int STRING_CONST = 104;
const int ERROR = 105;

using namespace std;

const string keywords[] = {"class", "constructor", "function", "method", "field", "static", "var", "int", "char","boolean", "void", "true", "false", "null", "this", "let", "do", "if" , "else", "while", "return" };

const char symbols[] = {'{', '}', '(', ')', '[', ']', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~'};



class JackTokenizer {
	ifstream jackFile;
	string currentLine, currentToken;
	bool isBlockComment;
	deque<string> tokens;

	public:
		
		JackTokenizer(string filename);
		bool hasMoreTokens();
		void advance(); 
		int tokenType();
		string keyword();
		char symbol();
		string identifier();
		int intaVal();
		string stringVal();
		~JackTokenizer();

		// helper methods
		void generateTokens();
};

/*
Constructor input file /stream   -- Opens the input file/stream and gets ready to tokenize it

hasMoreTokens -- Boolean do we have more tokens in the input?

advance -- 	gets the next token from the input and makes it the current token. This method should only be
			called if hasMoreTokens() is true. Initially there is no current token..

tokenType -- KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST returns the type of the current token

keyWord -- 	CLASS, METHOD,
			FUNCTION,
			CONSTRUCTOR,
			INT, BOOLEAN, CHAR,
			VOID, VAR, STATIC,
			FIELD, LET, DO, IF,
			ELSE, WHILE,
			RETURN, TRUE,
			FALSE, NULL, THIS
			returns the keyword which is the current token. Should be called only when tokenType() is KEYWORD.

symbol  -- 	char -- returns the character which is the current token. Should be called only when tokenType() is SYMBOL.

identifier -- string -- returns the identifier which is the current token. Should be called only when tokenType
				() is IDENTIFIER

intVal --  int  -- returns the integer value of the current token. Should be called only when tokenType() is 
				INT_CONST

stringVal -- string -- returns the string value of the current token, without the double quotes. Should be 
			called only when tokenType() is STRING_CONST. 

*/

