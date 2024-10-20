# InteractivePaint-ECS

Overview  
The Interactive Paint Application is a text-based drawing tool developed in C, featuring a dynamic, resizable canvas for creating and manipulating custom graphics. It allows users to draw, edit, and display artwork within a terminal-based interface. The application utilizes dynamic memory management and modular code to handle real-time updates and user interactions efficiently.

Features   
Dynamic Canvas Resizing: Supports custom canvas dimensions that can be adjusted as needed.
Text-Based Drawing Tools: Allows drawing on the canvas, erasing, and modifying specific sections.
Real-Time Updates: Provides immediate visual feedback as the user interacts with the canvas.
Modular Design: Organized in a modular code structure, making it easy to extend functionalities.

Commands:   
The application accepts various commands to interact with the canvas:
draw <x> <y>: Draws a character at the specified coordinates.
erase <x> <y>: Erases a character at the specified coordinates.
resize <new_width> <new_height>: Resizes the canvas to the given dimensions.
display: Shows the current state of the canvas.
help: Lists all available commands.
quit: Exits the application.

Code Structure:  
paint.c: The main program file containing the core logic for canvas management and user interactions.
print_statements.h: Header file with utility functions for displaying messages and handling output.
Modular Functions: The code is divided into functions for creating, displaying, and modifying the canvas to maintain a clean structure.

Future Improvements
- Adding support for additional drawing tools (lines, shapes, etc.).
- Implementing undo and redo functionalities.
- Enhancing the user interface for better visualization.

Lessons Learned  
This project provided valuable experience in:
- Managing memory dynamically in C.
- Structuring code in a modular way for better maintainability.
- Designing simple algorithms for real-time applications.
