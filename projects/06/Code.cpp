#include "Code.h"

using namespace std;

string Code::dest(string destField) {
	if(destField.length() == 0) return "000"; // null
	if(destField == "M") return "001";		  // M
	if(destField == "D") return "010";		  // D
	if(destField == "MD") return "011";		  // MD
	if(destField == "A") return "100";		  // A
	if(destField == "AM") return "101";		  // AM
	if(destField == "AD") return "110";		  // AD
	if(destField == "AMD") return "111";	  // AMD
	
	return "Invalid Dest Code!";							  
}
	
string Code::comp(string compField) {
	// a = 0
	if(compField == "0")   return "0101010"; // 0
	if(compField == "1")   return "0111111"; // 1
	if(compField == "-1")  return "0111010"; // -1
	if(compField == "D")   return "0001100"; // D
	if(compField == "A")   return "0110000"; // A
	if(compField == "!D")  return "0001101"; // !D
	if(compField == "!A")  return "0110001"; // !A
	if(compField == "-D")  return "0001111"; // -D
	if(compField == "-A")  return "0110011"; // -A
	if(compField == "D+1") return "0011111"; // D + 1
	if(compField == "A+1") return "0110111"; // A + 1
	if(compField == "D-1") return "0001110"; // D - 1
	if(compField == "A-1") return "0110010"; // A - 1
	if(compField == "D+A") return "0000010"; // D + A
	if(compField == "D-A") return "0010011"; // D - A
	if(compField == "A-D") return "0000111"; // A - D
	if(compField == "D&A") return "0000000"; // D & A
	if(compField == "D|A") return "0010101"; // D | A
	
	// a = 1
//	if(compField == "0")   return "0101010"; // 0
//	if(compField == "1")   return "0111111"; // 1
//	if(compField == "-1")  return "0111010"; // -1
//	if(compField == "D")   return "0001100"; // D
	if(compField == "M")   return "1110000"; // M
//	if(compField == "!D")  return "0001101"; // !D
	if(compField == "!M")  return "1110001"; // !M
//	if(compField == "-D")  return "0001111"; // -D
	if(compField == "-M")  return "1110011"; // -M
//	if(compField == "D+1") return "0011111"; // D + 1
	if(compField == "M+1") return "1110111"; // M + 1
//	if(compField == "D-1") return "0001110"; // D - 1
	if(compField == "M-1") return "1110010"; // M - 1
	if(compField == "D+M") return "1000010"; // D + M
	if(compField == "D-M") return "1010011"; // D - M
	if(compField == "M-D") return "1000111"; // M - D
	if(compField == "D&M") return "1000000"; // D & M
	if(compField == "D|M") return "1010101"; // D | M
	
	return "Invalid Comp Code!";
}
	
string Code::jump(string jumpField) {
	if(jumpField.length() == 0) return "000"; // null
	if(jumpField == "JGT") return "001";	  // JGT
	if(jumpField == "JEQ") return "010";	  // JEQ
	if(jumpField == "JGE") return "011";	  // JGE
	if(jumpField == "JLT") return "100";	  // JLT
	if(jumpField == "JNE") return "101";	  // JNE
	if(jumpField == "JLE") return "110";	  // JLE
	if(jumpField == "JMP") return "111";	  // JMP
	
	return "Invalid Jump code!";							  
}
