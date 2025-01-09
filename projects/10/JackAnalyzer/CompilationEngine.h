#include <iostream>
#include <fstream>
#include <string>
#include "JackTokenizer.h"

using namespace std;

class CompilationEngine {
    ofstream xmlfile;
    JackTokenizer tokenizer;
    string string_constant, identifier, keyword, symbol, int_constant;
    int tokenType;
    bool error;
    string identation;

    public:
        
        CompilationEngine(string ipfile, string opfile);
        void compileClass();
        void compileClassVarDec();
        void compileSubroutine();
        void compileParameterList();
        void compileVarDec();
        void compileStatements();
        void compileDo();
        void compileLet();
        void compileWhile();
        void compileReturn();
        void compileIf();
        void compileExpression();
        void compileTerm();
        void compileExpressionList();
        ~CompilationEngine();
        
        // helper methods
        void getNextTokenType();
        string getXml(string tag, string val);

};

/*

Constructor -- Inputstream/file Outputstream/file -- creates a new compilation engine with the given input and output. 
                The next method called must be compileClass().

CompileClass -- -- compiles a complete class.

CompileClassVarDec -- -- compiles a static declaration or a field declaration.

CompileSubroutine -- -- compiles a complete method, function, or constructor.

compileParameterList -- -- compiles a (possibly empty) parameter list, not including the enclosing “()”.

compileVarDec -- -- compiles a var declaration.

compileStatements -- -- compiles a sequence of statements, not including the enclosing “{}”.

compileDo -- -- Compiles a do statement

compileLet -- -- Compiles a let statement

compileWhile -- -- Compiles a while statement

compileReturn -- -- compiles a return statement.

compileIf -- -- compiles an if statement, possibly with a trailing else clause. 

CompileExpression -- -- compiles an expression. 

CompileTerm -- -- compiles a term. This method is faced with a slight difficulty when trying to decide between some of 
                the alternative rules. Specifically, if the current token is an identifier, it must still distinguish 
                between a variable, an array entry, and a subroutine call. The distinction can be made by looking ahead 
                one extra token. A single look-ahead token, which may be one of “[“, “(“, “.”, suffices to distinguish 
                between the three possibilities. Any other token is not part of this term and should not be advanced 
                over.

CompileExpressionList -- -- compiles a (possibly empty) commaseparated list of expressions. 
*/