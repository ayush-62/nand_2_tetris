#include <string>
#include <unordered_map>

#include <math.h>
#include <stdint.h>

#define SUCCESS 0
#define FAILURE 1


int line_num = 0;

std::unordered_map<std::string, std::string> dest_map = {
        {"null", "000"},
        {"M", "001"},   
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"AMD", "111"}
};
std::unordered_map<std::string, std::string> comp_map = {
    // a=1
        {"0", "0101010"},
        {"1", "0111111"},
        {"-1", "0111010"},
        {"D", "0001100"},
        {"A", "0110000"},
        {"!D", "0001101"},
        {"!A", "0110001"},
        {"-D", "0001111"},
        {"-A", "0110011"},
        {"D+1", "0011111"},
        {"A+1", "0110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"D+A", "0000010"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},
    // a=0
        {"M", "1110000"},
        {"!M", "1110001"},
        {"-M", "1110011"},
        {"M+1", "1110111"},
        {"M-1", "1110010"},
        {"D+M", "1000010"},
        {"D-M", "1010011"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
};
std::unordered_map<std::string, std::string> jump_map = {
        {"null", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}

};

std::unordered_map<std::string, int> variable_sym_map = {

};

std::unordered_map<std::string, int> lable_sym_map = {
    
};

std::unordered_map<std::string, int> predef_sym_map = {
    {"R0",0},
    {"R1",1},
    {"R2",2},
    {"R3",3},
    {"R4",4},
    {"R5",5},
    {"R6",6},
    {"R7",7},
    {"R8",8},
    {"R9",9},
    {"R10",10},
    {"R11",11},
    {"R12",12},
    {"R13",13},
    {"R14",14},
    {"R15",15},

    {"SP",0},
    {"LCL",1},
    {"ARG",2},
    {"THIS",3},
    {"THAT",4},
    {"SCREEN",16384},
    {"KBD",24576}
};
uint8_t print_error(std::string inst, std::string msg){
    char erro_msg[] = "[ASM]  ERROR: %s                        \n" 
                      "       In \"%s\" at line %d\n";
    printf(erro_msg, msg.c_str(), inst.c_str(), line_num);
    return SUCCESS;
}

uint8_t create_output_file(std::string input_file, std::string &asm_out){
    int i;
    size_t last_slash_pos;
    size_t dot_pos;

    asm_out = "output_files/";
    i = input_file.size()-1;
    last_slash_pos = input_file.find_last_of("/\\");
    input_file = (last_slash_pos == std::string::npos)? input_file: input_file.substr(last_slash_pos+1);
    dot_pos = input_file.find_last_of(".");
    input_file = input_file.substr(0, dot_pos);   
    asm_out += input_file+".hack";
    return SUCCESS;
}

uint8_t int_to_binary(int num, std::string &binary){
    int iter = 14;
    if(num < 0 || num > pow(2, 15)-1){
        print_error(std::to_string(num), "invalid value");
        return FAILURE;
    }
    while(iter > -1){
        binary += ((num & 1<<(iter--))? '1':'0');
    }
    return SUCCESS;
}
