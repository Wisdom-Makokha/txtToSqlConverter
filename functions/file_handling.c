#include "../headers/definitions.h"

// function to open a file in a specific mode as specified in the structure new_file
// function has been modified to open the file placed at a specified file path
bool open_file(new_file *file_to_open, bool pick_input)
{
    // picking the file prefix
    char *picked_prefix = pick_input ? INPUT_PREFIX : OUPUT_PREFIX;

    char *file_path = combine_strings(picked_prefix, file_to_open->filename, FILE_LENGTH + 18);
    // printf("File path: %s\n", file_path);
    
    // check if opening the file was successful
    if ((file_to_open->fileptr = fopen(file_path, file_to_open->mode)) == NULL)
    {
        fprintf(stderr, "Unable to open file: \'%s\' in mode \'%s'\'!\n", file_to_open->filename, file_to_open->mode);
        free(file_path);
        return FAILURE;
    }

    // remember to always free memory
    free(file_path);
    return SUCCESS;
}

// function to combine two strings
char *combine_strings(char *string1, char *string2, unsigned return_string_limit)
{
     //format for the filename
    char *return_string_format = "%s%s";

    //getting the length of the string first for efficient memory allocation
    size_t length = 0;
    length = snprintf(NULL, length, return_string_format, string1, string2);

    // limiting the size of the memory allocated
    if(length > return_string_limit)
        length = return_string_limit;

    // dynamic memory allocation
    char *return_string = (char *) malloc(sizeof(char) * length + 1);

    // checking to ensure memory allocation was successful
    if(!return_string)
    {
        fprintf(stderr, "%s() error: virtual memory allocation failed.\n", __func__);
        free(return_string);
        return NULL;
    }

    // printing to the allocated memory the full file path
    if(((unsigned) snprintf(return_string, length + 1, return_string_format, string1, string2)) > length + 1)
    {
        fprintf(stderr, "%s() error: snprintf returned truncated result.\n", __func__);
        free(return_string);
        return NULL;
    }

    return return_string;
}