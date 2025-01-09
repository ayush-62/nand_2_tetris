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