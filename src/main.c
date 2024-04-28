/*
 * Bitcmp - a program for comparing two files
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

const char* program_name;

unsigned long get_file_size (FILE* file)
{
    unsigned long size = 0;

    fseek (file, 0L, SEEK_END);
    size = ftell (file);
    fseek (file, 0L, SEEK_SET);

    return size;
}

void print_usage (FILE* stream, int exit_code)
{
        fprintf (stream, "Usage: %s -f [first_hash_file] -s [second_hash_file]\n", program_name);       
        fprintf (stream,
                        " -h --help \t Display this usage information.\n"
                        " -f --first [filename] \t First input hash file.\n"
                        " -s --second [filename] \t Second input hash file.\n");
        exit (exit_code);
}

int main (int argc, char* argv[])
{
    int next_option;

    const char* const short_options = "hf:s:";

    const struct option long_options[] = {
            { "help",       0, NULL, 'h' },
            { "first",      1, NULL, 'f' },
            { "second",     1, NULL, 's' },
            { NULL,         0, NULL,  0  }
    };

    program_name = argv[0];

    const char* first_filename  = NULL;
    const char* second_filename = NULL;

    /* Process arguments */
    do {
            next_option = getopt_long (argc, argv, short_options, long_options, NULL);

            switch (next_option)
            {
            case 'h':
                    print_usage (stdout, 0);

            case 'f':
                    first_filename = optarg;
                    break;

            case 's':
                    second_filename = optarg;
                    break;

            case -1: /* No more arguments */
                    break;

            default: /* Something went horribly wrong... */
                    abort();
            }
    }
    while (next_option != -1);


    /* Check if both of the files were provided */
    if (NULL == first_filename)
    {
            fprintf (stderr, "No first hash file found!\n");
            print_usage (stderr, 1);
    }

    if (NULL == second_filename)
    {
            fprintf (stderr, "No second hash file found!\n");
            print_usage (stderr, 1);
    }

    /* Open the files */
    FILE* first_file    = fopen (first_filename, "rb");
    FILE* second_file   = fopen (second_filename, "rb");

    if (NULL == first_file) 
    {
            fprintf (stderr, "Failed to open first file!\n");
            print_usage (stderr, 1);
    }

    if (NULL == second_file)
    {
            fprintf (stderr, "Failed to open second file!\n");
            print_usage (stderr, 1);
    }

    unsigned int first_size = get_file_size (first_file);
    unsigned int second_size = get_file_size (second_file);

    unsigned int diff_count = abs (first_size - second_size);

    for (int i = 0; i < min (first_size, second_size); ++i)
    {
            char a = 0;
            char b = 0;

            fread (&a, 1, 1, first_file);
            fread (&b, 1, 1, second_file);

            /* See how many bits are different between the two bytes */              
            char c = a ^ b;

            for (int j = 0; j < 8; ++j)
            {
                diff_count += (c >> j) & 1;
            }
    }

    /* Print the result */
    fprintf (stdout, "The difference between the two hashes is %d bits\n", diff_count);

    fclose (first_file);
    fclose (second_file);

    return 0;
}

