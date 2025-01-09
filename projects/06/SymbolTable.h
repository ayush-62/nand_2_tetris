#include <string>
#include <unordered_map>

using namespace std;

class SymbolTable {
	public:
		
	unordered_map<string, int> symtbl;
	
	SymbolTable();
	
	void addEntry(string, int);
	
	bool contains(string);
	
	int getAddress(string);
};
