#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include <sys/syscall.h>

#include "common.h"
#include "compiler.h"
#include "vm_translator.h"


static const char usage[] = 
                "     options:                                 \n"
                "         --input-file  : path to input file   \n"
                "         --format      : format of output file\n"
                "                         (vm, asm, bin)       \n"
                "         --help        : list options         \n";

void print_usage(){
    printf("%s\n", usage);
}
// uint8_t check_asm(std::string input_file){
//     strcmp(input_file+(input_file.size()-4), ".hack");
// }

uint8_t parse_arg(int argc, char* argv[]){  
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "--input-file")){
            if(argc < 3){
                printf("ERROR:Command line argument missing\n");
                return FAILURE;
            }
            input_file = argv[++i];
        }
        else if(!strcmp(argv[i], "--format")){
            formate = argv[++i];
        }
        else if(!strcmp(argv[i], "--help")){
            print_usage();
        }
        else{
            printf("ERROR:Invalid command line option \"%s\"\n", argv[i]);
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
    system("mkdir -p output_files");
    // compile();
    // vm_translate();
    assembler();
    return SUCCESS;
}