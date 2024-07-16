#include "../headers/definitions.h"

// function to get the file name
char *get_filename(void)
{
    char *filename = (char *)malloc(sizeof(char) * FILE_LENGTH);

    printf("Enter the name of the file to convert: ");

    // check if we are unable to read anything then return a NULL
    if ((fgets(filename, FILE_LENGTH, stdin)) == NULL)
    {
        perror("Unable to read filename\n");
        return NULL;
    }

    return filename;
}

// function to get the database name from the terminal
char *get_database(void)
{
    char *database = (char *)malloc(sizeof(sizeof(char) * DATABASE_LENGTH));

    printf("Enter the name of the database for the SQL statements: ");

    // check if we are unable to read anything then return a NULL
    if ((fgets(database, DATABASE_LENGTH, stdin)) == NULL)
    {
        perror("Unable to read database name\n");
        return NULL;
    }

    return database;
}

// function to check if there any header rows present
void check_for_header_row(bool *header_present)
{
    char response[6];

    printf("Does the file have a header row: (yes/no): ");

    // get the response as the entire line
    fgets(response, 6, stdin);

    if (response[0] == 'y')
        *header_present = true;
    else
        *header_present = false;
}

// functions to get arguements that were not given at the program call at the command line
void cover_terminal_processing(terminal_options *options_to_set)
{
    // database name check
    if (options_to_set->database_name.is_missing)
    {
        *(options_to_set->database_name.value.databasename) = get_database();
    }

    // filename check
    if (options_to_set->filename.is_missing)
    {
        *(options_to_set->filename.value.filename) = get_filename();
    }

    // header row check
    if (options_to_set->header.is_missing)
    {
        check_for_header_row(options_to_set->header.value.header_row_present);
    }
}

// function to confirm all of the set options
void confirm_options(terminal_options *set_options)
{
    bool stop = false;
    while (!stop)
    {
        char response[6];
        printf("These are your set options:- \n");
        printf("\tFilename: %s", *(set_options->filename.value.filename));
        printf("\tDatabase name: %s", *(set_options->database_name.value.databasename));
        printf("\tHeader row setting: %s\n", *(set_options->header.value.header_row_present) ? "present" : "absent");

        printf("Continue with these options? (yes/no): ");
        fgets(response, 6, stdin);

        if (response[0] == 'y')
            break;
        else if (response[0] == 'n')
        {
            printf("\nWhich option do you want to change: (Enter the number for your picked option)\n");
            printf("\tFilename: %d\n", FILENAME);
            printf("\tDatabase name: %d\n", DB_NAME);
            printf("\tHeader row setting: %d\n", HEADER);
            printf("\tAll of them: %d\n", ALL_OF_THEM);
            printf("\tNone of them: %d\n", NONE_OF_THEM);
            printf("Enter response: ");

            fgets(response, 2, stdin);
            int option_response = atoi(response);

            switch (option_response)
            {
            case FILENAME:
                set_options->filename.is_missing = true;
                break;
            case DB_NAME:
                set_options->database_name.is_missing = true;
                break;
            case HEADER:
                set_options->header.is_missing = true;
                break;
            case ALL_OF_THEM:
                set_options->filename.is_missing = true;
                set_options->database_name.is_missing = true;
                set_options->header.is_missing = true;
                break;
            case NONE_OF_THEM:
                stop = true;
                break;
            default:
                fprintf(stderr, "Unknown response: %d\n", option_response);
                break;
            }

            cover_terminal_processing(set_options);
        }
    }
}
