/**
 * @file main.c
 * @author Wisdom Makokha
 * @brief As a brute force converter, this works bu it requires some more tweaking to make it work as an actual converter 
 * missing features that may make this better: multiple line context, value data type identification
 * @version 0.1
 * @date 2024-07-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../headers/definitions.h"

int main(int argc, char **argv)
{
    new_file convert_struct;
    convert_struct.mode = "r";
    char *databasename;
    bool header_present = false;

    terminal_options *options_to_set = create_option_struct(&databasename, &convert_struct.filename, &header_present);

    // initial set up
    terminal_processing(argc, argv, options_to_set);
    cover_terminal_processing(options_to_set);
    confirm_options(options_to_set);

    // initialise output struct
    new_file output_struct;
    output_struct.mode = "w";

    char *table_name = strdup(convert_struct.filename);
    table_name = strtok(table_name, ".");

    output_struct.filename = combine_strings(table_name, ".sql", FILE_LENGTH + 18);

    // printf("%s\n", output_struct.filename);

    // open input file
    if (!open_file(&convert_struct, PICK_INPUT))
        exit(EXIT_FAILURE);

    // open output file
    if(!open_file(&output_struct, PICK_OUTPUT))
        exit(EXIT_FAILURE);

    convert_to_sql_file(options_to_set, &output_struct, &convert_struct, table_name);

    fclose(convert_struct.fileptr);
    fclose(output_struct.fileptr);
    free(options_to_set);
    exit(EXIT_SUCCESS);
}
