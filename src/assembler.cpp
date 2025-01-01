#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "assembler.h"

uint8_t handle_A_instruction(std::string inst, std::ofstream &out_file){
    int num;
    int ram_offset;
    bool is_char = 0;
    bool is_int = 0;
    std::string binary = "";
    std::string value = inst.substr(1);
    if(value.size() < 1){
        print_error(inst, "invalid instruction");
    }
    for(auto it: value){
        if((it >= '0' && it <= '9')){
            is_int = 1;
        }
        else{
            is_char = 1;   
        }
    }
    if(predef_sym_map.find(value) != predef_sym_map.end()){
        num = predef_sym_map[value];
    }
    else if(lable_sym_map.find(value) != lable_sym_map.end()){
        num = lable_sym_map[value];
    }
    else if(variable_sym_map.find(value) != variable_sym_map.end()){
        num = variable_sym_map[value];
    }
    else if(value[0] >= '0' && value[0] <= '9' && !is_char){
        num = atoi(value.c_str());
    }
    else{
        ram_offset = 16+variable_sym_map.size();
        variable_sym_map[value] = ram_offset;
        num = ram_offset;
        // std::cout<<ram_offset<<std::endl;
    }
    if(int_to_binary(num, binary) == FAILURE){
        return FAILURE;
    }
    binary = "0"+binary;
    // std::cout << binary <<std::endl;
    out_file << binary <<std::endl;
    return SUCCESS;
}

uint8_t handle_C_instruction(std::string inst, std::ofstream &out_file){
    int eq_pos;
    int semi_pos;
    std::string dest = "";
    std::string comp = "";
    std::string jump = "";
    std::string binary = "";
    
    eq_pos = inst.find_last_of("=");
    semi_pos = inst.find_last_of(";");
    if(eq_pos == std::string::npos){
        dest = "null";
        if(semi_pos == std::string::npos){
            //null
            print_error(inst, "invalid instruction");
            return FAILURE;     
        }
        else{
            //c;j
            comp = inst.substr(0, semi_pos);
            jump = inst.substr(semi_pos+1);     
        }
    }
    else{
        dest = inst.substr(0,eq_pos);
        if(semi_pos == std::string::npos){
            //d=c
            comp = inst.substr(eq_pos+1);
            jump = "null";
        }
        else{
            //d=c;j
            comp = inst.substr(eq_pos+1, semi_pos);
            jump = inst.substr(semi_pos+1);
        }
    }
    // std::cout<<dest<<" "<<comp<<" "<<jump<<std::endl;
    if(comp_map.find(comp) == comp_map.end()||
        dest_map.find(dest) == dest_map.end()||
        jump_map.find(jump) == jump_map.end())
    {
        print_error(inst, "invalid instruction");
        return FAILURE;
    }
    binary = "111"+comp_map[comp]+dest_map[dest]+jump_map[jump];
    out_file << binary<<std::endl;
    return SUCCESS;
}


uint handle_symb(std::ifstream &in_file){
    int pos;
    int ref = 0;
    std::string line;
    std::string inst;
    std::string symb = ""; 
    std::string msg;
    while(std::getline(in_file, line)){
        line_num++;
        std::istringstream lineStream(line);
        while(lineStream >> inst){
            if(inst[0] == '/'){
               break;
            }
            if(inst[0] == '('){
                pos = inst.find_last_of(")");
                if((pos == std::string::npos)){
                    print_error(inst, "syntax error");
                    return FAILURE;
                }
                if(pos <= 1){
                    print_error(inst, "lable symbol can't be empty");
                    return FAILURE;
                }
                symb = inst.substr(1, pos-1);
                if(predef_sym_map.find(symb) != predef_sym_map.end()){
                    print_error(inst, "pre-define symbol can't be used as lable symbol");
                    return FAILURE;
                }
                if(lable_sym_map.find(symb) != lable_sym_map.end()){
                    msg = "multiple declaration of lable symbol at line ";
                    msg += std::to_string(line_num);
                    msg += ". previously declared at line ";
                    msg += std::to_string(lable_sym_map[symb]);
                    print_error(inst, msg);
                    return FAILURE;
                }
                lable_sym_map[symb] = ref;    
            }
            else{
                // std::cout<<inst << " "<<ref++<<std::endl;
                ref++;
            }
        }
    }
    // for(auto it : lable_sym_map){
    //     std::cout<<it.first<<" "<<it.second<<std::endl;
    // }
    in_file.clear();
    in_file.seekg(0,std::ios::beg);
    return SUCCESS;
}

uint8_t assembler(){
    std::string line;
    std::string inst;
    std::string asm_out;

    std::ifstream in_file(input_file); // Open file for reading
    if (!in_file.is_open()) {
        printf("Error: Could not open file.\n");
        return FAILURE;
    }
    create_output_file(input_file , asm_out);
    std::ofstream out_file(asm_out); 
    if(handle_symb(in_file) == FAILURE){
        return FAILURE;
    }
    line_num = 0;
    while(std::getline(in_file, line)){
        std::istringstream lineStream(line);
        line_num++;
        while(lineStream >> inst){
            if(inst[0] == '/'){
                if(inst.size() < 1 ||  inst[1] != '/'){
                    print_error(inst,"Invalid instruction");
                    return FAILURE;
                }
                else break;
            }
            else if(inst[0] == '@'){
                if(handle_A_instruction(inst, out_file) == FAILURE){
                    return FAILURE;
                }
            }
            else if(inst[0] == '('){
                // if(check_symb_lable(inst, out_file) == FAILURE){
                //     return FAILURE;
                // }
                continue;
                
            }
            else{
               if(handle_C_instruction(inst, out_file) == FAILURE){
                    return FAILURE;
                }
            }
        }
    }
    return SUCCESS;
}
