#include <stdio.h>
#include <string.h>
#include "crc.h"

//----------------------------------------------------------------------
// Usage: bindumper filename-to-read-and-dump
//
// This program reads the file passed in the arguments and outputs the 
// binary reprsentation in an array of decimals. The output is written to 
// a file named "output" in the same folder. The output is in the form of
// a variable "unsigned char bin[] = { ... }" so it can be reused in
// C/C++ code
// --------------------------------------------------------------------
int main(int argc, const char *argv[]) 
{
    if (argc != 2) {
        printf("Usage: bindumper filename-to-read-and-dump");
        return 1;
    }

    FILE* fsource;
    FILE* fdest;

    fsource = fopen(argv[1], "rb");
    fdest = fopen("output", "w");

    fprintf(fdest, "%s", "unsigned char bin[] = {");
    
    unsigned char buffer[1000];
    int i = 0;
    int read = 0;
    int read_total = 0;
    while( (read = fread(buffer, 1, 1000, fsource)) ) {
        for (i = 0; i < read; i++) {
            fprintf(fdest, "%d,", buffer[i]);
        }
        read_total += read;
    }

    //Remove the extra comma added when the last byte was written
    fseek(fdest, -1, SEEK_CUR);
    fprintf(fdest, "%s", "};");

    fclose(fsource);
    fclose(fdest);

    printf("Total bytes read = %d\n", read_total);

    return 0;
}
