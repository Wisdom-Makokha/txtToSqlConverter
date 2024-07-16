#include "../headers/definitions.h"

// the list of possible states for the initial program call
enum Missing{FILENAME, DB_NAME, FILE_N_DBNAME, HEADER_PR, NONE, ERROR};

// function to process arguements from the terminal
int process_terminal_commands(int argc, char **argv, char **databasename, char **filename, bool *header_present)
{
    int dash = 0;
    int option = 1;
    enum Missing Missing_status = FILE_N_DBNAME;
    *header_present = false;

    for (int index = 1; index < argc && index < MAX_TERMINAL_ARGS; index += 2)
    {
        // ensure the flag starts with a -
        if ((strlen(argv[index]) == 2) && argv[index][dash] == '-')
        {
            switch (tolower(argv[index][option]))
            {
            // filename option
            case 'f':
                *filename = argv[index + 1];

                // check if we already have the DB name, then change the status to nothing missing
                if (Missing_status == FILENAME)
                    Missing_status = NONE;

                // change the status to show we now have the filename
                else
                    Missing_status = DB_NAME;

                break;
            // database name option
            case 'd':
                *databasename = argv[index + 1];

                // check if we already have the filename, then change the status to nothing missing
                if (Missing_status == DB_NAME)
                    Missing_status = NONE;

                // change the status to show we now have the db name
                else
                    Missing_status = FILENAME;

                break;
            // header option
            case 'h':
                *header_present = true;
                break;
            // for errors
            default:
                Missing_status = ERROR;
                break;
            }
        }
        else
            Missing_status = ERROR;

        // If any of them return an error just retake both values
        if (Missing_status == ERROR)
            break;
    }

    return Missing_status;
}


// function to cover any issues that
void get_missing_arguements(enum Missing terminal_results, char **databasename, char **filename, bool *header_present)
{
    // check if the values for filename and dataabase have been set
    switch (terminal_results)
    {
    case FILENAME:
        // printf("Filename\n");
        *filename = get_filename();
        break;
    case DB_NAME:
        // printf("Database name\n");
        *databasename = get_database();
        break;
    case FILE_N_DBNAME:
        // printf("Filename n database name\n");
        *databasename = get_database();
        *filename = get_filename();
        break;
    case ERROR:
        printf("Error with terminal arguement\n");
        *databasename = get_database();
        *filename = get_filename();
        break;
    case HEADER_PR:
        check_for_header_row(header_present);
        break;
    case NONE:
        printf("Nothing missing\n");
        break;
    default:
        fprintf(stderr, "Unexpected arguement to function: %s\n", __func__);
        break;
    }

    // check if the header row should be set to present
    if (!*header_present)
        check_for_header_row(header_present);
}

// function to confirm picked options
void confirm_arguemnts(char **databasename, char **filename, bool *header_present)
{
    while (true)
    {
        char response[6];
        printf("These are your set options:- \n");
        printf("\tFilename: %s", *filename);
        printf("\tDatabase name: %s", *databasename);
        printf("\tHeader row setting: %s\n", *header_present ? "present" : "absent");

        printf("Continue with these options? (yes/no): ");
        fgets(response, 6, stdin);

        if (response[0] == 'y')
            break;
        else if (response[0] == 'n')
        {
            printf("Which option do you want to change: \n");
            printf("\tFilename: %d\n", FILENAME);
            printf("\tDatabase name: %d\n", DB_NAME);
            printf("\tHeader row setting: %d\n", HEADER);
            printf("\tAll of them: %d\n", ALL_OF_THEM);
            printf("\tNone of them: %d\n", NONE_OF_THEM);

            int option_response;
            fgets(response, 2, stdin);
            option_response = atoi(response);

            // get_missing_arguements(option_response, databasename, filename, header_present);
        }
    }
}