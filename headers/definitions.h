#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define EXPECTED_ARGS 1
#define MAX_TERMINAL_ARGS 7
#define SUCCESS true
#define FAILURE false
#define FILE_LENGTH 32
#define DATABASE_LENGTH 64
#define LINE_LENGTH 1024
#define INPUT_PREFIX "input/"
#define OUPUT_PREFIX "output/converted_"
#define PICK_INPUT true
#define PICK_OUTPUT false

// structure for file details
typedef struct file_struct
{
    char *filename;
    FILE *fileptr;
    char *mode;
} new_file;

// union for the possible values for an option
typedef union values
{
    char **databasename;
    char **filename;
    bool *header_row_present;
} option_values;

// structure for the options at the terminal
typedef struct
{
    bool is_missing;
    option_values value;
} option;

typedef struct 
{
    option filename;
    option database_name;
    option header;
} terminal_options;

// an enum for the options to pick any of the options to change
enum change_options{FILENAME = 1, DB_NAME, HEADER, ALL_OF_THEM, NONE_OF_THEM};


bool open_file(new_file *file_to_open, bool pick_input);
char *combine_strings(char *string1, char *string2, unsigned return_string_limit);

char *get_filename(void);
char *get_database(void);
void check_for_header_row(bool *header_present);

bool terminal_processing(int argc, char **argv, terminal_options *options_to_set);
terminal_options *create_option_struct(char **databasename, char **filename, bool *header);
void cover_terminal_processing(terminal_options *options_to_set);
void confirm_options(terminal_options *set_options);

void convert_to_sql_file(terminal_options *set_options, new_file *output, new_file *input, char *table_name);
int process_row(char *header, char **columns);