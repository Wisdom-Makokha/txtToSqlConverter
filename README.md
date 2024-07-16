#txttoSQLConverter

As an initial prototype it's okay
The converter can convert a txt file containing data arranged into the normal csv format

CSV format:
 column1, column2, .... , columnN (Header containing the column names is optional)
 column1, column2, .... , columnN
 ....

The output file will have this format for absent header rows:
    USE dictionary;

    INSERT INTO 'word_tb' ('column1', 'column2')
    VALUES
    (1, (null)),
    (2, ""),
    (3, "Ey""ries");

With the header row present the format for the output file is:
    USE dictionary;

    DROP IF EXISTS 'word_tb';

    CREATE TABLE 'word_tb' (
        word_ID, 
        word
    );

    INSERT INTO 'word_tb' ('word_ID', 'word')
    VALUES
    (1, (null)),
    (2, ""),
    (3, "Ey""ries"),

Present feautures:
    - terminal arguements to make running easier
    - an attempt at being thorough at getting everything that is needed for the program to run
    - brute force conversion with some small adjustments needed both at the end of the file and table creation statements

Missing features include:
    - multiline context to make it easier to no when the file ends
    - value data type identification to for both table creation statements and the proper handling of values
    - any more features I think of later