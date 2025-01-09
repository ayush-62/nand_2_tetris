#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(string filename) : jackFile(filename) { 
	isBlockComment = false;	
	currentLine = "";
	currentToken = "";
	 cout << "Jacktokrnier constructor: " << filename << endl;
}
	
bool JackTokenizer::hasMoreTokens() {
	while(jackFile.peek() != EOF && tokens.empty()) {
		generateTokens();
	}
	return (!tokens.empty() || jackFile.peek() != EOF);
	// (jackFile.peek() != EOF)
}
	
void JackTokenizer::advance() {
	// generateTokens();
	
	// if(tokens.empty()) {
	// 	cout << "Empty queue" << endl; return;
	// }
	currentToken = tokens.front();
	// cout << "ct : " << currentToken << endl;
	tokens.pop_front();
}

// keyword: 'class' | 'constructor' | 'function' | 'method' | 'field' | 'static' |
// 			'var' | 'int' | 'char' | 'boolean' | 'void' | 'true' | 'false' | 'null' | 'this' |
// 			'let' | 'do' | 'if' | 'else' | 'while' | 'return'
// symbol: '{' | '}' | '(' | ')' | '[' | ']' | '. ' | ', ' | '; ' | '+' | '-' | '*' | '/' | '&' | '|' | '<' |
//			'>' | '=' | '~'
// integerConstant: a decimal number in the range 0 .. 32767
// stringConstant '"' sequence of ASCII characters not including double quote or newline '"'
// identifier: sequence of letters, digits, and underscore ( '_' ) not starting with a digit 
int JackTokenizer::tokenType() {
	if(currentToken.length() > 1) {
		for(string s : keywords) {
			if(currentToken == s) {
				return KEYWORD;
			}
		}
	}
	for(char c : symbols) {
		if(currentToken[0] == c) {
			return SYMBOL;
		}
	}
	if(isdigit(currentToken[0]))  {
		bool error = false;
		for(char c : currentToken) {
			if(!isdigit(c)) error = true;
		}
		if(error) {
			cout << "Invalid integer constant! token : " << currentToken << endl;
			return ERROR;
		}
		return INT_CONST;
	}    
	if(currentToken[0] == '"') {
		return STRING_CONST;
	}
	return IDENTIFIER;
}
	
string JackTokenizer::keyword() {
	return currentToken;
}

char JackTokenizer::symbol() {
	return currentToken[0];
}

string JackTokenizer::identifier() {
	return currentToken;
}

int JackTokenizer::intaVal() {
	int int_const = stoi(currentToken);
	if(int_const > 32767) return -1;
	return int_const;
}

string JackTokenizer::stringVal() {
	return currentToken.substr(1, currentToken.length()-2);
}


JackTokenizer::~JackTokenizer() {
	jackFile.close();
}


// helper methods

void JackTokenizer::generateTokens() {
	getline(jackFile, currentLine);
	cout << "advance ------------------------------------" << endl;

	string tok = "";
	
	for(int i = 0; i < currentLine.length(); i++) {
		bool isdelim = false;
		
		// if block comment = true checks for "*/", if not found continue for next char iteration  
		if(isBlockComment) {
			if(currentLine[i] == '*' && i+1 < currentLine.length() && currentLine[i+1] == '/') {
				// cout << "tok_blcm : \t" << tok << endl;
				// cout << "tok_blcm : \t*/" << endl;
				tok = "";
				i++;
				isBlockComment = false;
			}
			else {
				tok += currentLine[i];
			}
			continue;
		}
		
		// compare if current char is delimiter
		for(char c : symbols) {
			if(currentLine[i] == c) {
				isdelim = true;
				break;
			}
		}
		
		// check for comment start either "//" or "/*"
		if(currentLine[i] == '/') {
			if(i+1 < currentLine.length()) {
				if(currentLine[i+1] == '/') {
					cout << "comment " << currentLine.substr(i) << endl;
					break; 
				}
				if(currentLine[i+1] == '*') {
					// cout << "tok_blcm : \t/*" << endl;
					isBlockComment = true;
					i++;
					continue;
				}
			}
		}

		// if not comment then generates token and delimiter 
		if(isdelim || currentLine[i] == ' ' || currentLine[i] == '\t') {
			if(tok.length() != 0) {
				// cout << "tok : \t\t" << tok << endl;
				tokens.push_back(tok);
			}
			if(currentLine[i] != ' ' && currentLine[i] != '\t') {
				// cout << "tok_delim : \t" << currentLine[i] << endl;
				tokens.push_back(currentLine.substr(i, 1));
			}
			// currentToken = tok;
			tok = "";
		}

		// generates token for string constant 
		else if(currentLine[i] == '"') {
			if(tok.length() != 0) {
				// cout << "tok : \t\t" << tok << endl;
				tokens.push_back(tok);
			}
			// cout << "tok_quote : \t" << currentLine[i] << endl;
			// currentToken = tok;
			tok = "";
			i++;
			while(currentLine[i] != '"'){
				tok += currentLine[i];
				i++;
				if(i >= currentLine.length()) {
					cout << "string constant is not closed" << endl;
					break;
				}

			}
			// cout << "tok : \t\t\"" << tok  << "\"" << endl;
			tokens.push_back("\"" + tok + "\"");
			// cout << "tok_quote : \t" << currentLine[i] << endl;
			tok = "";
		}

		//else append char to current token
		else {
			tok += currentLine[i];
		}
	}
	if(tok.length() > 0) {
		if(isBlockComment) 
			cout << "tok_blcmt : \t\t " << tok << endl;
		else {
			// cout << "tok_last : \t\t " << tok << endl;
			tokens.push_back(tok);
		}
	}
	
	cout << "tokens : [ ";
	for(string t : tokens) {
		cout << t << " ";
	}
	cout << "]" << endl << endl;
}

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

