#include "../headers/definitions.h"

#define COLUMN_LIMIT 15

// function to convert the input file to an output file
void convert_to_sql_file(terminal_options *set_options, new_file *output, new_file *input, char *table_name)
{
    fprintf(output->fileptr, "USE %s;\n\n", *(set_options->database_name.value.databasename));

    char line[LINE_LENGTH];

    // get the first line
    fgets(line, LINE_LENGTH, input->fileptr);
    line[strlen(line) - 1] = '\0';

    char *columns[COLUMN_LIMIT];
    int index = 0;

    // get the number of columns
    int column_number = process_row(line, columns);

    if (*(set_options->header.value.header_row_present))
    {
        // drop the table if it already exists
        fprintf(output->fileptr, "DROP IF EXISTS '%s';\n\n", table_name);

        // create the table
        fprintf(output->fileptr, "CREATE TABLE '%s' (\n", table_name);
        
        // columns to create
        index = 0;
        for(; index < column_number - 1; index++)
        {
            fprintf(output->fileptr, "\t%s, \n", columns[index]);
        }

        fprintf(output->fileptr, "\t%s\n);\n\n", columns[index]);
    }

    // print the insert beginning statement
    fprintf(output->fileptr, "INSERT INTO '%s' (", table_name);
    
    index = 0;
    for (; index < column_number - 1; index++)
    {
        if (*(set_options->header.value.header_row_present))
            fprintf(output->fileptr, "'%s', ", columns[index]);
        else
            fprintf(output->fileptr, "'table_name_%d', ", index);
    }

    // separate the last column to not print the comma
    if (*(set_options->header.value.header_row_present))
        fprintf(output->fileptr, "'%s')\n", columns[index]);
    else
        fprintf(output->fileptr, "'column_%d')\n", index);

    //values
    fprintf(output->fileptr, "VALUES\n");

    // print the values
    while((fgets(line, LINE_LENGTH, input->fileptr)) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        char *values[COLUMN_LIMIT];
        process_row(line, values);

        // values for each row
        index = 0;
        fprintf(output->fileptr, "(");
        for(; index < column_number - 1; index++)
        {
            fprintf(output->fileptr, "%s, ", values[index]);
        }

        fprintf(output->fileptr, "%s),\n", values[index]);
    }

    fprintf(output->fileptr, ";");
}

// function to process the header row and get the number of columns
int process_row(char *header, char **columns)
{
    char *delimiter = ",";
    int index = 0;
    columns[index] = strtok(header, delimiter);
    // printf(columns[index]);
    index++;

    while ((columns[index] = strtok(NULL, delimiter)) != NULL)
    {
        // printf(columns[index]);
        index++;
    }

    return index;
}