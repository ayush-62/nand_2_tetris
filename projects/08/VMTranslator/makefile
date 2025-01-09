VMTranslator: main.o Parser.o CodeWriter.o
	g++ main.o Parser.o CodeWriter.o -o VMTranslator;

main.o: main.cpp
	g++ -c main.cpp

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp

CodeWriter.o: CodeWriter.cpp CodeWriter.h
	g++ -c CodeWriter.cpp

clean:
	rm *.o

test_all: VMTranslator
	.\VMTranslator.exe ..\ProgramFlow\FibonacciSeries\FibonacciSeries.vm
	.\VMTranslator.exe ..\ProgramFlow\BasicLoop\BasicLoop.vm
	.\VMTranslator.exe ..\FunctionCalls\SimpleFunction\SimpleFunction.vm
	.\VMTranslator.exe ..\FunctionCalls\FibonacciElement
	.\VMTranslator.exe ..\FunctionCalls\StaticsTest\

test12: VMTranslator
	.\VMTranslator.exe ..\FunctionCalls\SimpleFunction\SimpleFunction.vm
	.\VMTranslator.exe ..\FunctionCalls\FibonacciElement

test1: VMTranslator
	.\VMTranslator.exe ..\FunctionCalls\SimpleFunction\SimpleFunction.vm

test2: VMTranslator
	.\VMTranslator.exe ..\FunctionCalls\FibonacciElement

test3: VMTranslator
	.\VMTranslator.exe ..\FunctionCalls\StaticsTest\