#ifndef PRINT_HELP_H
	#define PRINT_HELP_H
	typedef struct canvas_struct
    {
        int rows;
        int cols;
        char **filldata;
    } Canvas;

	typedef struct command_struct
    {
		char command[20];
		char command2[20];
		int arg1;
        int arg2;
		int arg3;
		int arg4;
		int total_read;
    } input_command;

	void print_help();
	
#endif