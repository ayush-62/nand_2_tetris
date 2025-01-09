#include "CompilationEngine.h"

using namespace std;

CompilationEngine::CompilationEngine(string ipfile, string opfile) : tokenizer(ipfile), xmlfile(opfile) {
    cout << "Constructor CE " << ipfile << endl;
    cout << "Constructor CE " << opfile << endl;
    identation = "";
    getNextTokenType();
    /*
    class: 'class' className '{' cvd subroutineDec* '}'
    cvd = classVarDec cvd\ E
    
    */
    compileClass();
}

CompilationEngine::~CompilationEngine() {
    xmlfile.close();
}

// class: 'class' className '{' classVarDec* subroutineDec* '}'
void CompilationEngine::compileClass() {
    xmlfile << identation << "<class>" << endl;
    identation += "\t";
    
    // 'class'
    cout << "class - " << keyword << " - " << endl;
    if(tokenType == KEYWORD && keyword == "class") { xmlfile << identation << getXml("keyword", keyword) << endl; }
    else { xmlfile << "expecting class keyword!" << endl; return; }
    getNextTokenType(); 
    
    // className
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid class name (identifier)" << endl;  return;}
    getNextTokenType();

    // '{'
    if(tokenType == SYMBOL && symbol == "{") xmlfile << identation << getXml("symbol", symbol) << endl;
    else { xmlfile << "Expecting '{' ." << endl;  return;}
    getNextTokenType();
        
    // classVarDec*
    compileClassVarDec();
    // while(tokenType == KEYWORD && (keyword == "static" || keyword == "field")) { 
    //     compileClassVarDec();
    //     getNextTokenType(); 
    // }
        
    // subroutineDec*
    compileSubroutine();
    // while(tokenType == KEYWORD && (keyword == "constructor" || keyword == "function" || keyword == "method")) {
    //     compileSubroutine();
    //     getNextTokenType();
    // }
    
    // '}'
    // getNextTokenType(); 
    if(tokenType == SYMBOL && symbol == "}") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting '}' ." << endl;  return;}
    getNextTokenType();
    
    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</class>" << endl;
}

// classVarDec: ('static' | 'field' ) type varName (',' varName)* ';' classVarDec 
//            : epsilon
void CompilationEngine::compileClassVarDec() {
    // 'static' or 'field'
    if(tokenType == KEYWORD && (keyword == "static" || keyword == "field")) {
        xmlfile << identation << "<classVarDec>" << endl;
        identation += "\t";
        xmlfile << identation << getXml("keyword", keyword) << endl; 
    }
    else {return;}
    getNextTokenType();
    
    // type -----  {'int' | 'char' | 'boolean' | className}
    if(tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean")) { xmlfile << identation << getXml("keyword", keyword) << endl; }
    else if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid type!" << endl;  return; }
    getNextTokenType();

    // varName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid variable!" << endl;  return;}
    getNextTokenType();

    // (, varName)* 
    while(tokenType == SYMBOL && symbol == ",") {
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();
        if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
        else { xmlfile << "not valid varibale!" << endl;  return;}
        getNextTokenType();
    }

    // ';'
    // getNextTokenType(); 
    if(tokenType == SYMBOL && symbol == ";") xmlfile << identation << getXml("symbol", symbol) << endl;
    else { xmlfile << "Expecting ';' ." << endl;  return;}
    getNextTokenType();
    
    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</classVarDec>" << endl;

    // classVardec*
    compileClassVarDec();
}

// subroutineDec: ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
void CompilationEngine::compileSubroutine() {

    if(tokenType == KEYWORD && (keyword == "constructor" || keyword == "function" || keyword == "method")) {
        xmlfile << identation << "<subroutineDec>" << endl;
        identation += "\t";
        // 'constructor' | 'function' | 'method'
        xmlfile << identation << getXml("keyword", keyword) << endl;
    }
    else { return; }
    getNextTokenType();
    
    // 'void' | type -----  {'int' | 'char' | 'boolean' | className}
    if(tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean" || keyword == "void")) { xmlfile << identation << getXml("keyword", keyword) << endl; }
    else if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid type!" << endl;  return; }
    getNextTokenType();

    // subroutineName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid variable!" << endl;  return;}
    getNextTokenType();

    // '('
    if(tokenType == SYMBOL && symbol == "(") {xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting '(' " << endl; return; }
    getNextTokenType();

    // parameterList ----- type varName (, varName)*    
    // type varName (, varName)*
    compileParameterList();
    // if(tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean")) { compileParameterList(); }
    // else if(tokenType == IDENTIFIER) { compileParameterList(); }
    
    // ')'
    // getNextTokenType(); 
    if(tokenType == SYMBOL && symbol == ")") xmlfile << identation << getXml("symbol", symbol) << endl;
    else { xmlfile << "Expecting ')' after parameters." << endl;  return;}
    getNextTokenType();

    // subroutineBody: '{' varDec* statements '}'
    xmlfile << identation << "<subroutineBody>" << endl;
    identation += "\t";
    // '{'
    if(tokenType == SYMBOL && symbol == "{") {xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting '{' " << endl; return; }
    getNextTokenType();

    // varDec*
    compileVarDec();
    // while(tokenType == KEYWORD && keyword == "var") { 
    //     compileVarDec(); 
    //     getNextTokenType();
    // }

    // statements
    compileStatements();
    // if(tokenType == KEYWORD && (keyword == "let" || keyword == "do" || keyword == "while" || keyword == "if" || keyword == "return")) { compileStatements(); }
    
    // '}'
    // getNextTokenType();
    if(tokenType == SYMBOL && symbol == "}") {xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting '}' " << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</subroutineBody>" << endl;

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</subroutineDec>" << endl;

    compileSubroutine();
}

// parameterList: ( (type varName) (',' type varName)*)?
void CompilationEngine::compileParameterList() {
    xmlfile << identation << "<parameterList>" << endl;
    identation += "\t";
    if(tokenType == IDENTIFIER | tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean")) {
        // type
        xmlfile << identation << getXml("keyword", keyword) << endl;
    }
    else {
        if(identation.length() > 0) identation.pop_back();
        xmlfile << identation << "</parameterList>" << endl;
        return;}
    getNextTokenType();

    // varName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid variable!" << endl;  return;}
    getNextTokenType();

    // (, type varName)*
    while(tokenType == SYMBOL && symbol == ",") {
        // ','
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        // type -----  {'int' | 'char' | 'boolean' | className}
        if(tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean")) { xmlfile << identation << getXml("keyword", keyword) << endl; }
        else if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
        else { xmlfile << "not valid type!" << endl;  return; }
        getNextTokenType();

        // varName ---- Identifier
        if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
        else { xmlfile << "not valid variable!" << endl;  return;}
        getNextTokenType();
    }

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</parameterList>" << endl;
}

// varDec: 'var' type varName (',' varName)* ';'
void CompilationEngine::compileVarDec() {
    if(tokenType == KEYWORD && keyword == "var") {
        xmlfile << identation << "<varDec>" << endl;
        identation += "\t";
        // 'var'
        xmlfile << identation << getXml("keyword", keyword) << endl;
    }
    else return;
    getNextTokenType();
    
    // type -----  {'int' | 'char' | 'boolean' | className}
    if(tokenType == KEYWORD && (keyword == "int" || keyword == "char" || keyword == "boolean")) { xmlfile << identation << getXml("keyword", keyword) << endl; }
    else if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid type!" << endl;  return; }
    getNextTokenType();

    // varName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid variable!" << endl;  return;}
    getNextTokenType();

    // (, varName)*
    while(tokenType == SYMBOL && symbol == ",") {
        // ','
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        // varName ---- Identifier
        if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
        else { xmlfile << "not valid variable!" << endl;  return;}
        getNextTokenType();
    }

    // ';'
    if(tokenType == SYMBOL && symbol == ";") {xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting ';' " << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</varDec>" << endl;

    compileVarDec();
}

// Statements: statement*
// statemtent : letStatement | doStatement | whileStatement | ifStatement | returnStatement
void CompilationEngine::compileStatements() {
    xmlfile << identation << "<statements>" << endl;
    identation += "\t";

    while(tokenType == KEYWORD) {
        if(keyword == "let") { compileLet(); }
        else if(keyword == "do") { compileDo(); }
        else if(keyword == "while") { compileWhile(); }
        else if(keyword == "if") { compileIf(); }
        else if(keyword == "return") { compileReturn(); }
        else break;
        // getNextTokenType();
    }

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</statements>" << endl;
}

// 'do' subroutineCall ';'
// subroutineCall: subroutineName '(' expressionList ')' | ( className | varName) '.' subroutineName '(' expressionList ')'
void CompilationEngine::compileDo() {
    xmlfile << identation << "<doStatement>" << endl;
    identation += "\t";

     // 'let', 'do', 'while', 'if', 'return'
    xmlfile << identation << getXml("keyword", keyword) << endl;
    getNextTokenType();

    // subroutineName | className | varName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid variable!" << endl;  return;}
    getNextTokenType();

    // '.' | '('
    if(tokenType == SYMBOL && symbol == ".") { 
        // '.'
        xmlfile << identation << getXml("symbol", symbol) << endl; 
        getNextTokenType();
        
        // subroutineName ---- Identifier
        if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
        else { xmlfile << "not valid variable!" << endl;  return;}
        getNextTokenType();

        // '('
    }

    // '('
    if(tokenType == SYMBOL && symbol == "(") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '('" << endl; return; }
    getNextTokenType();

    // expressionList
    compileExpressionList();

    // ')'
    if(tokenType == SYMBOL && symbol == ")") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected ')'" << endl; return; }
    getNextTokenType();
    
    // ';'
    if(tokenType == SYMBOL && symbol == ";") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected ';'" << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</doStatement>" << endl;

    // compileStatements();
}

// letStatement: 'let' varName ('[' expression ']')? '=' expression ';'
void CompilationEngine::compileLet() {
    xmlfile << identation << "<letStatement>" << endl;
    identation += "\t";

     // 'let', 'do', 'while', 'if', 'return'
    xmlfile << identation << getXml("keyword", keyword) << endl;
    getNextTokenType();

    // varName ---- Identifier
    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
    else { xmlfile << "not valid identifier!" << endl;  return;}
    getNextTokenType();

    // '[' | '='
    if(tokenType == SYMBOL && symbol == "[") { 
        // '['
        xmlfile << identation << getXml("symbol", symbol) << endl; 
        getNextTokenType();
        
        // expression
        compileExpression();

        // ']'
        if(tokenType == SYMBOL && symbol == "]") { xmlfile << identation << getXml("symbol", symbol) << endl; }
        else { xmlfile << "Expecting ']' !" << endl;  return;}
        getNextTokenType();
    }

    // '='
    if(tokenType == SYMBOL && symbol == "=") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '='" << endl; return; }
    getNextTokenType();
    
    // expression
    compileExpression();

    // ';'
    if(tokenType == SYMBOL && symbol == ";") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected ';'" << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</letStatement>" << endl;

    // compileStatements();
}

// whileStatement: 'while' '(' expression ')' '{' statements '}' 
void CompilationEngine::compileWhile() {
    xmlfile << identation << "<whileStatement>" << endl;
    identation += "\t";

     // 'let', 'do', 'while', 'if', 'return'
    xmlfile << identation << getXml("keyword", keyword) << endl;
    getNextTokenType();

    // '('
    if(tokenType == SYMBOL && symbol == "(") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting '(' !" << endl;  return;}
    getNextTokenType();

    // expression
    compileExpression();
    
    // ')'
    if(tokenType == SYMBOL && symbol == ")") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expecting ')' !" << endl;  return;}
    getNextTokenType();

    // '{'
    if(tokenType == SYMBOL && symbol == "{") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '{'" << endl; return; }
    getNextTokenType();

    // statements
    compileStatements();

    // '}'
    if(tokenType == SYMBOL && symbol == "}") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '}'" << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</whileStatement>" << endl;

    // compileStatements();
}

// returnStatement: 'return' expression? ';'
void CompilationEngine::compileReturn() {
    xmlfile << identation << "<returnStatement>" << endl;
    identation += "\t";

     // 'let', 'do', 'while', 'if', 'return'
    xmlfile << identation << getXml("keyword", keyword) << endl;
    getNextTokenType();

    if(!(tokenType == SYMBOL && symbol == ";")) {
        // expression
        compileExpression();
    }
    
    // ';'
    if(tokenType == SYMBOL && symbol == ";") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected ';'" << endl; return; }
    getNextTokenType();

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</returnStatement>" << endl;

    // compileStatements();
}

// ifStatement: 'if' '(' expression ')' '{' statements '}' ( 'else' '{' statements '}' )?
void CompilationEngine::compileIf() {
    xmlfile << identation << "<ifStatement>" << endl;
    identation += "\t";

     // 'let', 'do', 'while', 'if', 'return'
    xmlfile << identation << getXml("keyword", keyword) << endl;
    getNextTokenType();

    // '('
    if(tokenType == SYMBOL && symbol == "(") {
        xmlfile << identation << getXml("symbol", symbol) << endl;
    }
    else { xmlfile << "Expected '('" << endl; return; }
    getNextTokenType();

    // expression
    compileExpression();
    
    // ')'
    if(tokenType == SYMBOL && symbol == ")") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected ')'" << endl; return; }
    getNextTokenType();

    // '{'
    if(tokenType == SYMBOL && symbol == "{") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '{'" << endl; return; }
    getNextTokenType();

    // statements
    compileStatements();

    // '}'
    if(tokenType == SYMBOL && symbol == "}") { xmlfile << identation << getXml("symbol", symbol) << endl; }
    else { xmlfile << "Expected '}'" << endl; return; }
    getNextTokenType();

    // else 
    if(tokenType == KEYWORD && keyword == "else") { 
        //else 
        xmlfile << identation << getXml("keyword", keyword) << endl;
        getNextTokenType();

        // '{'
        if(tokenType == SYMBOL && symbol == "{") { xmlfile << identation << getXml("symbol", symbol) << endl; }
        else { xmlfile << "Expected '{'" << endl; return; }
        getNextTokenType();

        // statements
        compileStatements();

        // '}'
        if(tokenType == SYMBOL && symbol == "}") { xmlfile << identation << getXml("symbol", symbol) << endl; }
        else { xmlfile << "Expected '}'" << endl; return; }
        getNextTokenType();
 
    }
    
    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</ifStatement>" << endl;

    // compileStatements();
}

// Expression: term (op term)*
// op: '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
void CompilationEngine::compileExpression() {
    xmlfile << identation << "<expression>" << endl;
    identation += "\t";
    
    // term
    compileTerm();
    
    // (op term)*
    while(tokenType == SYMBOL && (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "&" || symbol == "|" || symbol == "<" || symbol == ">" || symbol == "=")) {
        // op
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        //term
        compileTerm();
    }
     
    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</expression>" << endl;
}

// term: integerConstant | stringConstant | keywordConstant | varName | varName '[' expression']' | subroutineCall | 
//       '(' expression ')' | unaryOp term
// unaryOp: '-' | '~'
// keywordConstant: 'true' | 'false' | 'null' | 'this' 
void CompilationEngine::compileTerm() {
    xmlfile << identation << "<term>" << endl;
    identation += "\t";
    
    // integerConstant
    if(tokenType == INT_CONST) { xmlfile << identation << getXml("integerConstant", int_constant) << endl; getNextTokenType(); }
    // stringConstant
    else if(tokenType == STRING_CONST) { xmlfile << identation << getXml("stringConstant", string_constant) << endl; getNextTokenType(); }
    // keywordConstant : 'true' | 'false' | 'null' | 'this' 
    else if(tokenType == KEYWORD && (keyword == "true" || keyword == "false" || keyword == "null" || keyword == "this")) {  xmlfile << identation << getXml("keyword", keyword) << endl; getNextTokenType(); }
    // '(' expression ')'
    else if(tokenType == SYMBOL && symbol == "(") {
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        compileExpression();

        if(tokenType == SYMBOL && symbol == ")") { xmlfile << identation << getXml("symbol", symbol) << endl; }
        else { xmlfile << identation << "Expecting ')'" << endl; }
        getNextTokenType();
    }
    // unaryOp term
    // unaryOp: '-' | '~'
    else if(tokenType == SYMBOL && (symbol == "~" || symbol == "-")) {
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        compileTerm();
    }
    // VarName | VarName '[' expression ']' | subroutineCall
    else if(tokenType == IDENTIFIER) {
        // varName
        xmlfile << identation << getXml("identifier", identifier) << endl;
        getNextTokenType();

        // '.' | '[' | '('
        if(tokenType == SYMBOL) {
            // '[' - Array 
            if(symbol == "[") {
                xmlfile << identation << getXml("symbol", symbol) << endl;
                getNextTokenType();

                compileExpression();

                if(tokenType == SYMBOL && symbol == "]") { 
                    xmlfile << identation << getXml("symbol", symbol) << endl;
                    getNextTokenType(); 
                }
                else { xmlfile << identation << "expecting ']'" << endl; return;}
            }
            // subroutine call
            else if(symbol == "." || symbol == "("){
                // '.' | '('
                if(symbol == ".") { 
                    // '.'
                    xmlfile << identation << getXml("symbol", symbol) << endl; 
                    getNextTokenType();
                    
                    // subroutineName ---- Identifier
                    if(tokenType == IDENTIFIER) { xmlfile << identation << getXml("identifier", identifier) << endl; }
                    else { xmlfile << "not valid variable!" << endl;  return;}
                    getNextTokenType();
                }

                // '('
                if(symbol == "(") { xmlfile << identation << getXml("symbol", symbol) << endl; }
                else { xmlfile << "Expected '('" << endl; return; }
                getNextTokenType();

                // expressionList
                compileExpressionList();

                // ')'
                if(tokenType == SYMBOL && symbol == ")") { xmlfile << identation << getXml("symbol", symbol) << endl; }
                else { xmlfile << "Expected ')'" << endl; return; }
                getNextTokenType();
            }
        }
    }

    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</term>" << endl;
}

// expressionList: (expression (',' expression)* )?
void CompilationEngine::compileExpressionList() {
    xmlfile << identation << "<expressionList>" << endl;
    identation += "\t";
    
    if(tokenType == SYMBOL && symbol == ")") { 
        if(identation.length() > 0) identation.pop_back();
        xmlfile << identation << "</expressionList>" << endl;
        return; 
    }
    // expression
    compileExpression();
    
    // (, expression)*
    while(tokenType == SYMBOL && symbol == ",") {
        // ','
        xmlfile << identation << getXml("symbol", symbol) << endl;
        getNextTokenType();

        //expression
        compileExpression();
    }
     
    if(identation.length() > 0) identation.pop_back();
    xmlfile << identation << "</expressionList>" << endl;
}


// helper method

void CompilationEngine::getNextTokenType() {
    bool error = false;
    if(tokenizer.hasMoreTokens()) {
        tokenizer.advance();
        tokenType = tokenizer.tokenType();
        // cout << "Token Type: " << tokenType << endl;
        if(tokenType == KEYWORD) {
            keyword = tokenizer.keyword();
            cout << "keyword  - " << keyword << endl;
        }
        else if(tokenType == IDENTIFIER) {
            identifier = tokenizer.identifier();
            cout << "identifier  - " << identifier << endl;
        }
        else if(tokenType == STRING_CONST) {
            string_constant = tokenizer.stringVal();
            cout << "string_constant  - " << string_constant << endl;
        }
        else if(tokenType == INT_CONST) {
            int_constant = to_string(tokenizer.intaVal());
            cout << "int_constant  - " << int_constant << endl;
        }
        else if(tokenType == SYMBOL) {
            symbol = tokenizer.symbol();
            
            cout << "symbol  - " << symbol << endl;
        }
        else {
            error = true;
            cout << "error: " << endl;
        }
    }
    else {
        cout << "no token left!" << endl;
    }
    error = true;
}

string CompilationEngine::getXml(string tag, string val) {
    if(val == "<") val = "&lt;";
    else if(val == ">") val = "&gt;";
    else if(val == "&") val = "&amp;";
    return "<" + tag + "> " + val + " </" + tag + ">";
}