Parser: main.o JackTokenizer.o CompilationEngine.o
	g++ main.o JackTokenizer.o CompilationEngine.o -o Parser;

main.o: main.cpp
	g++ -c main.cpp

JackTokenizer.o: JackTokenizer.cpp JackTokenizer.h
	g++ -c JackTokenizer.cpp

CompilationEngine.o: CompilationEngine.cpp CompilationEngine.h
	g++ -c CompilationEngine.cpp

# CodeWriter.o: CodeWriter.cpp CodeWriter.h
# 	g++ -c CodeWriter.cpp

clean:
	rm *.o

test_all: Parser
	.\Parser.exe ..\ArrayTest
	.\Parser.exe ..\ExpressionLessSquare
	.\Parser.exe ..\Square

test1: Parser
	.\Parser.exe ..\ArrayTest

test2: Parser
	.\Parser.exe ..\ExpressionLessSquare

test3: Parser
	.\Parser.exe ..\Square