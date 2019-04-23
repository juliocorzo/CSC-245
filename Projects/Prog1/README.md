# CSC 245 - Program 1
# Julio R. Corzo

1. The goal of this program was to manage a text file and add, delete or move
through the lines of it. The client program handled all the operations related
to the text file, such as insert, delete, next, previous, move to top, etc.

2. The input file was passed as a parameter from the time that the editor was
run in the terminal. The output file has the same name as the input file, with
the changes made after the user selects the `E` option, which exits the program
and saves the changes.

3. Outline of the OOP Design.
  1. LineList is a class that implements doubly-linked lists for the program.
  it consists of methods and the structures necessary to navigate a linked lists
  of strings. Input and Output streams are used by the program but are built
  into the standard library.
  2. For the class LineList being implemented, its attributes are as follows:
    1. A pointer variable called `currLine` that stores the node that the
    program is currently at.
    2. An int called `currLineNum` that indicates on which line the editor is
    currently in.
    3. An int `length`, which represents the total lines that the file curren-
    tly has.
    4. As for public methods, there are many included, for example, methods to
    navigate the list whose names are pretty self-explanatory: `goToTop()`,
    which takes the `currLine` pointer and moves it to the top of the list.
    Similar methods include `goToBottom()`, `moveNextLine()`, `movePrevLine()`.
    All of these methods move the pointer and change the value of `currLineNum`.
    5. Other methods dealt with the deletion and insertion of lines into the
    text file. These methods are also self explanatory, but harder to implement.
    6. We also have getter methods to allow users to access private variables.
    These methods are `getCurrLine()`, `getCurrLineNum()`, and `getLength()`.
    7. Helper method `printList()`, which prints the entire list from the top.

## Outline
1. The program starts by checking if a name for a text file was found. If it
wasn't, the program exits. If it was found, the program attempts to populate
a LineList with each line included in the file.
2. After the lines are added, they are printed into the screen.
3. An infinite `while` loop with an embedded `switch` statement manages all the
operations. Helper method `getResponse()` returns a `char` value that the user
input. If the value is not one of the options, the program prints an error
message and asks the user to start again.
4. The options are:
  1. `I`, which then prompts the user to type the line they want to insert.
  2. `D`, which deletes the line that the user is currently on.
  3. `L`, which prints the entire list from top to bottom.
  4. `P`, which moves the user to the previous line if one is available.
  5. `N`, which moves the user to the next line if one is available.
  6. `E`, which quits the program and saves the changes to the file.
5. After `E` is passed the infinite `while` loop terminates and the changes are
saved to the file.

## A note on completion.
This program is not complete, and  I want to state this fact very clearly. I
don't want you to think that I was hiding the things I did not finish.

I did not manage to finish this program, due to many bugs. I spent most of the
previous week debugging, and honestly just trying to wrap my head around what
was going on. After finally understanding what was going on, I started to see
how linked lists are implemented.

I decided to try an IDE for this project, CLion, but the problem was that the
compiler it was using was not the same version of C++. This and other factors
that are under my control didn't allow me to finish this project. Thanks for
the opportunity to code it, it was super interesting.
