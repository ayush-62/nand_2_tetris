#include <string>

using namespace std;

class Code {
	public: 
	
	static string dest(string destField); 
	
	static string comp(string compField);
	
	static string jump(string jumpField);
	
};
/*
dest mnemonic (string) 3 bits Returns the binary code of the dest mnemonic.
comp mnemonic (string) 7 bits Returns the binary code of the comp mnemonic.
jump mnemonic (string) 3 bits Returns the binary code of the jump mnemonic
*/
