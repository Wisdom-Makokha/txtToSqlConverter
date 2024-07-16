#include "../headers/definitions.h"

// format for terminal commands to enter details
// accepted flags
// -f filename
// -d database name
// -h header row present

// second version of the function to process terminal aruguements
bool terminal_processing(int argc, char **argv, terminal_options *options_to_set)
{
    int dash = 0;
    int option = 1;
    bool result = SUCCESS;

    for (int index = 1; index < argc && index < MAX_TERMINAL_ARGS; index++)
    {
        // ensure the flag starts with a -
        if ((strlen(argv[index]) == 2) && argv[index][dash] == '-')
        {
            switch (tolower(argv[index][option]))
            {
            // filename option
            case 'f':
                // set option to no longer missing
                options_to_set->filename.is_missing = false;

                index++;
                // give the value for the option
                *(options_to_set->filename.value.filename) = argv[index];

                break;
            case 'd':
                // set option to no longer missing
                options_to_set->database_name.is_missing = false;

                index++;
                // give the value for the option
                *(options_to_set->database_name.value.databasename) = argv[index];
                break;
            case 'h':
                // set option to no longer missing
                options_to_set->header.is_missing = false;

                // give the value for the option
                *(options_to_set->header.value.header_row_present) = true;
                break;
            default:
                result = FAILURE;
            }
        }

        // if any of them return an error stop the loop
        if (!result)
            break;
    }

    return result;
}

// function to create the structure for the options it dynamically allocates memory for the structure
terminal_options *create_option_struct(char **databasename, char **filename, bool *header)
{
    terminal_options *options_to_set = (terminal_options *)malloc(sizeof(terminal_options));

    // check for memory allocation issues
    if (options_to_set != NULL)
    {
        // initialise the values
        options_to_set->database_name.is_missing = true;
        options_to_set->database_name.value.databasename = databasename;

        options_to_set->filename.is_missing = true;
        options_to_set->filename.value.filename = filename;

        options_to_set->header.is_missing = true;
        options_to_set->header.value.header_row_present = header;
    }
    else
        fprintf(stderr, "Memory allocation to structure options_to_set failed in functions: %s\n", __func__);

    return options_to_set;
}