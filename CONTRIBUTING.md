1.	All that can be written in C, should be written in C
Whilst C++ is great, c++ is also way more advanced than what most of you are capable of at this time. Therefore vanilla C is to be used for 90% or more of the final product, and c++ is only to be used as a QoL (Quality of Life) suplement, and not a replacement
2.	Restrict all code to simple control flow structs
Restrict yourself to simple CFS such as `if, else, while, for` and avoid more complicated flows such as `goto, setjmp and longjmp`
3.	Minimise memory allocation
To avoid memory leaks, and other memory related issues, memory allocation should ideally only be done in the initialisation phase of a program, and deallocation in the shut down part of the program.
4.	Proper initialisation and shut down
Have dedicated initialisation and shutdown parts of the program, to properly setup the environment, as well as close out of it in a controlled manner. This also enforces proper error and exception handling, as a crash obviously is not a propper shutdown
5.	No Function Should Be Longer Than What Can Be Printed on a Single Sheet of Paper
In coding you generally hear “One function, One thing”. This is interpretted in many different ways however. We code by a function not being longer than about 60 lines of code. So an input function for example, can get the user input, check for errors, and handle neccessarry conversions between data types, as long as it fits on 60 lines
It’s important to state though, that functions should also have a “purpose”. Just because i can fit an entire calculator on 60 lines, does not mean it’s acceptable to write it in 1 function. The input function handles user input, and therefore data conversion is also allowed. The calc function should handle the calculation however
6.	Global variables
Never! (arduino is an exception to this, cause the language heavily relies on global variables. Whilst they can be avoided, it’s going to be a mess)
7.	Warnings
Warnings when compiling the code should UNDER NO CIRCUMSTANCES go unnoticed. Every warning should be reviewed, and handled
Debugging flow should go like this: Errors -> warnings -> production bugs
8.	Upper bounds for loops
If a loop have the possibility of a runaway condition, were the loop could continue infinitely, provide an upper bound, to prevent such runaway condition
9.	Whitespace
Treat whitespace as “semi functions”. Meaning that lines of code that are directly related should not be seperated, and lines of code that aren’t should be seperated by exactly 1 newline
10.	No recurssive functions
A function may NEVER call itself
