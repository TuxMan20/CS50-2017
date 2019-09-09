/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Submited by Louis-Philippe Morier (/u/tuxman20)
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

#define BLOCK 512 // Constant for the chunk of data to be read

typedef uint8_t BYTE; // Abbreviation (BYTE) for an unsigned int of 8 bits

int main (int argc, char* argv[])
{
    if (argc != 2) // If the user did not specify a file, return an error
    {
        fprintf(stderr, "Usage: ./recover filename.extension. Error 1\n");
        return 1;
    }
    
    FILE *in_file = fopen(argv[1], "r"); // Opening the file and storing it's address into "in_file"
    
    if (in_file == NULL) // If the file cannot be found or opened, return an error
    {
        fprintf(stderr, "ERROR: Could not open raw file. Exiting Program. Error 2\n");
        return 2;
    }
    
    int filename = 0; // Used to create and track the file names of the jpg
    BYTE cur_read[BLOCK]; // Store the 512 bytes that are currently being read
    FILE *out_file = NULL; // Creating the out file
    
    //The big work starts now
    //Tried using nested for loops, Glenn Holloway suggested a single loop instead. 
    //Let me remove about 20 lines of codes and fixed my bugs!!
    while(fread(&cur_read, BLOCK, 1, in_file) > 0)
    {
         if(cur_read[0]== 0xff && cur_read[1] == 0xd8 && cur_read[2] == 0xff
         && (cur_read[3] == 0xe0 || cur_read[3] == 0xe1))
         {
            // Makes sure to close the last file before writing the next one
            // Found solution on reddit
            // http://www.reddit.com/r/cs50/comments/1vvlv0/check50_problem_in_pset5/
            if(out_file != NULL) fclose(out_file);
            
            // Create the empty jpg file, opens it for writing and prepare the next filename
            // Had issue with corrupted jpgs, found solution on reddit
            // http://www.reddit.com/r/cs50/comments/1zdhu6/pset5_recover_okay_i_get_50_corrupt_jpegs_now_what/
            char name[8];
            sprintf(name, "%03d.jpg", filename);
            out_file = fopen(name, "w");
            filename = filename + 1;
             
         }
         if(out_file != NULL) fwrite(cur_read, BLOCK, 1, out_file);
    }
    fclose(out_file);
    fclose(in_file);
    
    return 0; // Program quits normally    
}