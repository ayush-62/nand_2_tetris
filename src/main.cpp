#include <iostream>
#include <stdint.h>
#include <fstream>

#include "common.h"
#include "compiler.h"
#include "assembler.h"
#include "vm_translator.h"


static const char usage[] = 
                "     options:                                 \n"
                "         --input-file  : path to input file   \n"
                "         --format      : format of output file\n"
                "                         (vm, asm, bin)       \n"
                "         --help        : list options         \n";
void print_usage(){
    std::cout<<usage<<std::endl;
}
uint8_t parse_arg(int argc, char* argv[]){  
    for(int i = 1; i < argc; i++){
        if(argv[i] == "--input-file"){
            input_file =  argv[++i];
        }
        else if(argv[i] == "--format"){
            formate = argv[++i];
        }
        else if(argv[i] == "--help"){
            print_usage();
            
        }
        else{
            std::cout<<"ERROR:Invalid command line option "<<argv[i]<<std::endl;
            print_usage();
            return FAILURE;
        }
    }
    return SUCCESS;
}

int main(int argc, char *argv[]){
    if(parse_arg(argc, argv) == FAILURE){
        return EXIT_FAILURE;
    }
    // compile();
    // vm_translate();
    // assemble();
    return SUCCESS;
}