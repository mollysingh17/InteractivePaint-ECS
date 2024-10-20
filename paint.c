#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include <ctype.h>

#include "print_statements.h"

#define MAX_LIMIT 50

static char canvas[10][10];

static int rows, columns;

Canvas *create_print_canvas(Canvas *paint_canvas);
Canvas *canvas_new(const int rows, const int cols);

// Function to display the canvas

void show_canvas(Canvas *paint_canvas)

{

    int i, j;

   /* printf("\nOld Canvas:\n");

    for (i = 0; i < rows; i++)

    {

        for (j = 0; j < columns; j++)

            printf(" %c", canvas[i][j]);

        printf("\n");
    }  */

    Canvas *print_canvas = create_print_canvas(paint_canvas);

    // printf("\nCanvas:\n");

    for (i = 0; i < print_canvas->rows; i++)

    {

        for (j = 0; j < print_canvas->cols; j++)

            printf(" %c", print_canvas->filldata[i][j]);

        printf("\n");
    }
}

Canvas *create_print_canvas(Canvas *paint_canvas)
{
    Canvas *print_canvas = canvas_new(rows + 1, columns + 1);
    int i, j;

    for (int i = 0; i < print_canvas->rows; i++)
    {
        print_canvas->filldata[i] = (char *)malloc(sizeof(char) * print_canvas->cols);
    }

    for (i = 0; i < print_canvas->rows; i++)
    {

        for (j = 0; j < print_canvas->cols; j++)
        {

            if (i == 0)
            {
                if (j > 0)
                {
                    print_canvas->filldata[i][j] = j - 1 + '0';
                }
                else
                {
                    print_canvas->filldata[i][j] = ' ';
                }
            }
            else if (j == 0)
            {
                if (i > 0)
                {
                    print_canvas->filldata[i][j] = i - 1 + '0';
                }
                else
                {
                    print_canvas->filldata[i][j] = ' ';
                }
            }
            else
            {
                print_canvas->filldata[i][j] = paint_canvas->filldata[i - 1][j - 1];
            }
        }
    }

    // reversing rows

    for (i = 0; i < print_canvas->rows / 2; i++)
    {

        for (j = 0; j < print_canvas->cols; j++)
        {

            char temp = print_canvas->filldata[i][j];
            print_canvas->filldata[i][j] = print_canvas->filldata[print_canvas->rows - i - 1][j];
            print_canvas->filldata[print_canvas->rows - i - 1][j] = temp;
        }
    }

    return print_canvas;
}

// Function to initialize the canvas to all blanks.

// Since blank cannot be visualized, the canvas is initialized to all *s.

void initialize_canvas(Canvas *paint_canvas)

{

    int i, j;

    for (i = 0; i < rows; i++)
    {

        for (j = 0; j < columns; j++)
        {

            canvas[i][j] = '*'; // initialze canvas
        }
    }

    for (int i = 0; i < paint_canvas->rows; i++)
    {
        paint_canvas->filldata[i] = (char *)malloc(sizeof(char) * paint_canvas->cols);
    }

    for (i = 0; i < paint_canvas->rows; i++)
    {

        for (j = 0; j < paint_canvas->cols; j++)
        {

            paint_canvas->filldata[i][j] = '*';
        }
    }

    show_canvas(paint_canvas);
}

Canvas *canvas_new(const int rows, const int cols)
{ /*
    Dynamically create rows cols  matrix
    A matrix here is an array of array of doubles
    @rows: the number of rows the matrix should have
    @cols: the number of columns the matrix should have
    @returns: matrix_t structure containing matrix memry allocations
    @modifies: nothing
    */
    Canvas *canvas = malloc(sizeof(Canvas));
    canvas->rows = rows;
    canvas->cols = cols;

    canvas->filldata = (char **)malloc(sizeof(char *) * (canvas->rows));
    return canvas;
}

/* Function that writes to the canvas according to the following rules

    Horizontal lines are drawn using -

    Vertical lines are drawn using |

    Right diagonal lines are drawn using \

    Left diagonal lines are drawn using /

    If the line you are drawing intersects another line a + should be displayed at the intersection  */

void write(Canvas *paint_canvas, char *response)

{

    /* char symbol = '*';
    if (inc->total_read > 5 || inc->total_read < 5){
        printf("Improper draw command.\n");
    }  */
    int i, j;

    int start_row = response[2] - 48;

    int start_col = response[4] - 48;

    int end_row = response[6] - 48;

    int end_col = response[8] - 48; 

   /*int start_row = inc->arg1;

    int start_col = inc->arg2;

    int end_row = inc->arg3;

    int end_col = inc->arg4; */
   
    

    if (start_row < 0 || start_row >= 10 ||

        start_col < 0 || start_col >= 10 ||

        end_row < 0 || end_row >= 10 ||

        end_col < 0 || end_col >= 10

    )

    {

        printf("Invalid entry");

        return;
    }

    // horizontal line drawn using -

    if (start_row == end_row)

    {

        if (start_col <= end_col) // line drawn from left to right

        {

            for (j = start_col; j <= end_col; j++)

            {

                if (canvas[start_row][j] == '*' || canvas[start_row][j] == '-')
                {

                    canvas[start_row][j] = '-';
                }
                else
                {

                    canvas[start_row][j] = '+'; // when there is intersection of lines
                }
                // write to struct
                if (paint_canvas->filldata[start_row][j] == '*' || paint_canvas->filldata[start_row][j] == '-')
                {

                    paint_canvas->filldata[start_row][j] = '-';
                }
                else
                {

                    paint_canvas->filldata[start_row][j] = '+'; // when there is intersection of lines
                }
            }
        }

        else // line drawn from right to left

        {

            for (j = start_col; j <= end_col; j--)

            {

                if (canvas[start_row][j] == '*' || canvas[start_row][j] == '-')

                    canvas[start_row][j] = '-';

                else

                    canvas[start_row][j] = '+'; // when there is intersection of lines

                // write to struct
                if (paint_canvas->filldata[start_row][j] == '*' || paint_canvas->filldata[start_row][j] == '-')

                    paint_canvas->filldata[start_row][j] = '-';

                else

                    paint_canvas->filldata[start_row][j] = '+'; // when there is intersection of lines
            }
        }
    }

    // vertical line drawn using |

    else if (start_col == end_col)

    {

        if (start_row < end_row) // line drawn from top to bottom

        {

            for (i = start_row; i <= end_row; i++)

            {

                if (canvas[i][start_col] == '*' || canvas[i][start_col] == '|')

                    canvas[i][start_col] = '|';

                else

                    canvas[i][start_col] = '+'; // when there is intersection of lines

                // write to struct
                if (paint_canvas->filldata[i][start_col] == '*' || paint_canvas->filldata[i][start_col] == '|')

                    paint_canvas->filldata[i][start_col] = '|';

                else

                    paint_canvas->filldata[i][start_col] = '+'; // when there is intersection of lines
            }
        }

        else // line drawn from bottom to top

        {

            for (i = start_row; i <= end_row; i--)

            {

                if (canvas[i][start_col] == '*' || canvas[i][start_col] == '|')

                    canvas[i][start_col] = '|';

                else

                    canvas[i][start_col] = '+'; // when there is intersection of lines

                // write to truct

                if (paint_canvas->filldata[i][start_col] == '*' || paint_canvas->filldata[i][start_col] == '|')

                    paint_canvas->filldata[i][start_col] = '|';

                else

                    paint_canvas->filldata[i][start_col] = '+'; // when there is intersection of lines
            }
        }
    }

    // Left diagonal line from top left to bottom right

    else if ((start_row < end_row) && (start_col > end_col))

    {

        for (i = start_row, j = start_col; i <= end_row || j >= end_col; i++, j--)

        {

            if (canvas[i][j] == '*' || canvas[i][j] == '/')

                canvas[i][j] = '/';

            else

                canvas[i][j] = '+'; // when there is intersection of lines

            // write to struct
            if (paint_canvas->filldata[i][j] == '*' || paint_canvas->filldata[i][j] == '\\')

                paint_canvas->filldata[i][j] = '\\';

            else

                paint_canvas->filldata[i][j] = '+'; // when there is intersection of lines
        }
    }

    // Left diagonal line from bottom left to top right

    else if ((start_row > end_row) && (start_col < end_col))

    {

        for (i = start_row, j = start_col; i >= end_row || j <= end_col; i--, j++)

        {

            if (canvas[i][j] == '*' || canvas[i][j] == '/')

                canvas[i][j] = '/';

            else

                canvas[i][j] = '+'; // when there is intersection of lines

            if (paint_canvas->filldata[i][j] == '*' || paint_canvas->filldata[i][j] == '\\')

                paint_canvas->filldata[i][j] = '\\';

            else

                paint_canvas->filldata[i][j] = '+'; // when there is intersection of lines
        }
    }

    // Right diagonal line from top left to bottom right

    else if ((start_row < end_row) && (start_col < end_col))

    {

        for (i = start_row, j = start_col; i <= end_row || j <= end_col; i++, j++)

        {

            if (canvas[i][j] == '*' || canvas[i][j] == '\\')

                canvas[i][j] = '\\';

            else

                canvas[i][j] = '+'; // when there is intersection of lines

            // write to struct

            if (paint_canvas->filldata[i][j] == '*' || paint_canvas->filldata[i][j] == '/')

                paint_canvas->filldata[i][j] = '/';

            else

                paint_canvas->filldata[i][j] = '+'; // when there is intersection of lines
        }
    }

    // Right diagonal line from bottom right to top left

    else

    {

        for (i = start_row, j = start_col; i >= end_row || j >= end_col; i--, j--)

        {

            if (canvas[i][j] == '*' || canvas[i][j] == '\\')

                canvas[i][j] = '\\';

            else

                canvas[i][j] = '+'; // when there is intersection of lines

            // write to struct
            if (paint_canvas->filldata[i][j] == '*' || canvas[i][j] == '/')

                paint_canvas->filldata[i][j] = '/';

            else

                paint_canvas->filldata[i][j] = '+'; // when there is intersection of lines
        }
    }

    show_canvas(paint_canvas);
}

// Function that erases character at a particular row col to *

void erase(Canvas *paint_canvas, char *response)

{

    int row = response[2] - 48;

    int col = response[4] - 48;

    canvas[row][col] = '*';
}

// Function that adds a row or column at a specified position

void add(Canvas *paint_canvas, input_command *inc)

{

  //  char choice = response[2];

  //  int position = response[4] - 48;

    char choice = inc->command2[0];

    int position = inc->arg2;

    int i, j;

    if (choice == 'r')

    {

        // add rows

        rows = rows + 1;

        for (i = rows - 1; i > position; i--)

        {

            for (j = 0; j < columns; j++)

                canvas[i][j] = canvas[i - 1][j]; // Shifts the required rows
        }

        for (j = 0; j < columns; j++)

            canvas[position][j] = '*';
    }

    else if (choice == 'c')

    {

        // add columns

        columns = columns + 1;

        for (j = columns - 1; j > position; j--)

        {

            for (i = 0; i < rows; i++)

                canvas[i][j] = canvas[i][j - 1]; // Shifts the required columns
        }

        for (i = 0; i < rows; i++)

            canvas[i][position] = '*';
    }

    else

        printf("\nInvalid Command");

    show_canvas(paint_canvas);
}

// Function that deletes a particular row or column

void del(Canvas *paint_canvas, char *response)

{

    char choice = response[2];

    int position = response[4] - 48;

    int i, j;

    if (choice == 'r')

    {

        // delete rows

        for (i = position; i < rows - 1; i++)

        {

            for (j = 0; j < columns; j++)

                canvas[i][j] = canvas[i + 1][j];
        }

        rows--;
    }

    else if (choice == 'c')

    {

        // add columns

        for (j = position; j < columns - 1; j++)

        {

            for (i = 0; i < rows; i++)

                canvas[i][j] = canvas[i][j + 1];
        }

        columns--;
    }

    else

        printf("\nInvalid Command");

    show_canvas(paint_canvas);
}

void resize(Canvas *paint_canvas, char *response)

{

    printf("Routine will be available in later versions.");

    // Please note that more than the minimum number of sub-parts(3) already solved
}

void save()

{

    printf("Routine will be available in later versions");

    // Please note that more than the minimum number of sub-parts(3) already solved
}

void load_canvas()

{

    printf("Routine will be available in later versions");

    // Please note that more than the minimum number of sub-parts(3) already solved
}

int main(int argc, char *argv[])

{

    char user_input[MAX_LIMIT];

    if (argc != 3)

    {

        rows = 10;
        columns = 10;

        if (argc > 0)
        {

            printf("Wrong number of command line arguments entered.\n");
            printf("\nUsage: ./paint.out [num_rows num_cols]\n");
            printf("\nMaking default board of 10 X 10.\n");
        }
    }

    else

    {

        rows = atoi(argv[1]);

        columns = atoi(argv[2]);

        if (rows > 10 || rows < 1 || columns > 10 || columns < 1)

        {

            if (rows > 10)
            {
                printf("The number of rows is more than 10.\n");
                printf("\nMaking default board of 10 X 10.\n");
            }
            else if (rows < 0)
            {
                printf("The number of rows is less than 1.\n");
                printf("\nMaking default board of 10 X 10.\n");
            }
            else if (columns > 10)
            {
                printf("The number of columns is more than 10.\n");
                printf("\nMaking default board of 10 X 10.\n");
            }
            else if (columns < 0)
            {
                printf("The number of columns is less than 1.\n");
                printf("\nMaking default board of 10 X 10.\n");
            }

            rows = 10;

            columns = 10;
        }
    }

    Canvas *paint_canvas = canvas_new(rows, columns);

    initialize_canvas(paint_canvas);
    paint_canvas->rows = rows;
    paint_canvas->cols = columns;

    // return 0;

    while (1)

    {
       /* input_command *inc = (input_command *)malloc(sizeof(inc));
        inc->arg1=0;
        inc->arg2=0;
        inc->arg3=0;
        inc->arg4=0;*/

        printf("\n Enter your command: ");

        fflush(stdin);

        // gets(user_input);

        int ch;
        int n=0;
        ch = getchar();
        bool onespace = true;
        //fgets(user_input, MAX_LIMIT, stdin);
       // scanf("%m[^\n]%*c", &input);

        while (ch !='\n') {           
            //printf(" char %c", ich);
            if (!isspace(ch)   && n < MAX_LIMIT - 1){
                user_input[n] = ch;
                onespace = true;
                n++;
            } else if (isspace(ch) && onespace   && n < MAX_LIMIT -1){
                 onespace = false;
                 user_input[n] = ch;
                 n++;
            }
            ch = getchar();
            
        }
        user_input[n] ='\0';
        printf(" input %s", user_input);
   

        //scanf("%[^\n]s", input);
       // int total_read = 0;
       // inc->total_read = sscanf(input, " %s %d %d %d %d", inc->command, &inc->arg1, &inc->arg2, &inc->arg3, &inc->arg4);
        


       // if (sscanf(input, " %s %d %d %d %d", inc->command, &inc->arg1, &inc->arg2, &inc->arg3, &inc->arg4);)
       // printf("%ld", strlen(inc->command));

       // printf("total read struct  %s, %d, %s, %d, %d, %d ", inc->command, inc->total_read, inc->command2, inc->arg2, inc->arg3, inc->arg4);
      
      //  free(input);
        fflush(stdin);
       // if (strlen(inc->command) > 1)
        //{
        //    printf("\n Unrecognized command. Type h for help.");
        //}
        return 0;
       // switch (user_input[0])

        
        switch (user_input[0])
        {

        case 'q':

            printf("Exiting canvas.");

            exit(0);

        case 'h':

            // printf("Refer to already implemented part in command description.");
            print_help();
            break;

        case 'w':
            
 
          //  write(paint_canvas, user_input);

            break;

        case 'e':

           // erase(paint_canvas, user_input);

            break;

        case 'a':

         //   add(paint_canvas, inc);

            break;

        case 'd':

         //   del(paint_canvas, user_input);

            break;

        case 'r':

          //  resize(paint_canvas, user_input);

            break;

        case 's':

            save();

            break;

        case 'l':

          //  load_canvas();

            break;

        default:

            printf("\nError! Command not found");
        }
    }
    return 0;
}