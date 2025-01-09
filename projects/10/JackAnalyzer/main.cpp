#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "CompilationEngine.h"

using namespace std;

namespace fs = std::filesystem;

void generateTokenFile(fs::path jackfile);

bool debug = true;


int main(int argc, char** argv) {

	string jackfile = "../ArrayTest";
	
	if(argc > 1) jackfile = argv[1];
	if(argc > 2) debug = (argv[2][0] == '1'); 

	fs::path jack_path(jackfile);
	fs::path d_path;
	fs::path xml_path;

	jack_path.make_preferred();
	d_path.make_preferred();
	xml_path.make_preferred();

	if(fs::is_directory(jack_path)) {
		if(jack_path.has_stem()) {
			d_path = jack_path;
		}
		else {
			d_path = jack_path.parent_path();
		}
		xml_path = d_path; 
		xml_path /= xml_path.stem().string()+".xml";
	}
	else {
		d_path = jack_path.parent_path();
		xml_path = jack_path;
		xml_path.replace_extension("xml");
	}

	cout << "jack_path: " << jack_path.string() << endl;
	cout << "d_path: " << d_path.string() << endl;
	cout << "xml_path: " << xml_path.string() << endl << endl;

	// JackTokenizer and code writer 
	
	// CodeWriter codeWriter(fs::absolute(xml_path).string());
	
	if(fs::is_directory(jack_path)) {
		for(auto file : fs::directory_iterator(d_path)) {
			if(debug) cout << "----------------------------------------------------------------------------" << endl;
			if(debug) cout << "File: " << file.path().string() << endl;
			if(file.path().extension() != ".jack") continue;
			generateTokenFile(file.path());
		}
	}
	else {
		generateTokenFile(jack_path);
	}

	// codeWriter.close();
	if(debug) cout << "Jack Token Generation for all Files Ended!" << endl;
	return 0;
}

void generateTokenFile(fs::path jackfile) {

	// JackTokenizer jack_tokenizer(jackfile.string());
	// codeWriter.setFileName(jackfile.stem().string());

	// ofstream xmlFile(jackfile.replace_extension(".xml").string());
	cout << "=======================================================================================" << endl;
	string ipfile = jackfile.string();
	string opfile = jackfile.replace_extension(".xml").string();
	cout << ipfile << endl;
	cout << opfile << endl;

	CompilationEngine compiler(ipfile, opfile);

	// xmlFile << "<tokens>" << endl;

	// while(jack_tokenizer.hasMoreTokens()) {
	// 	jack_tokenizer.advance();
		
	// 	switch (jack_tokenizer.tokenType())
	// 	{
	// 		case KEYWORD: {
	// 				xmlFile << "<keyword>" << jack_tokenizer.keyword() << "</keyword>" << endl;
	// 				}
	// 			break;

	// 		case SYMBOL: {
	// 				char c = jack_tokenizer.symbol();
	// 				string str = "";
	// 				if(c == '<') str = "&lt;";
	// 				else if(c == '>') str = "&gt;";
	// 				else if(c == '&') str = "&amp;";
	// 				else str += c;
	// 				xmlFile << "<symbol>" << str << "</symbol>" << endl;
	// 				}
	// 			break;

	// 		case IDENTIFIER: {
	// 				xmlFile << "<identifier>" << jack_tokenizer.identifier() << "</identifier>" << endl;
	// 				}
	// 			break;
			
	// 		case INT_CONST: {
	// 				xmlFile << "<integerConstant>" << jack_tokenizer.intaVal() << "</integerConstant>" << endl;
	// 				}
	// 			break;
			
	// 		case STRING_CONST: {
	// 				xmlFile << "<stringConstant>" << jack_tokenizer.stringVal() << "</stringConstant>" << endl;
	// 				}
	// 			break;
		
	// 		default:
	// 			break;
	// 	}
	// }
	// xmlFile << "</tokens>" << endl;
	// xmlFile.close();
	cout << jackfile.filename() << " -> done!" << endl << endl;
}








