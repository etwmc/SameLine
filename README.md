# SameLine
No one like switching between source code and test code to see what's wrong, or spend time writing test code after writing finish writing the code itself. So why not write them together?  
Same Line is a preprocessor/parser that let you write unit test just like writing comments on the function: same file, same location, together. Before compiling the code, just use SameLine to extract all the test code, written in the form of comments, and generate the correspondent test case. 
And because it's written in comment format, so it will backward compaible if you choose not to use it in the future.  

# Grammar Strucutre
A test in SameLine has three parts: section, case, and the code itself.

Section:
A section is a logical compose of subsections and test cases, which is used to organize test cases, and the source code itself into more readable format. 
An example of section would be the following: the function square() and squareRoot() could has its own section respectively ("Square", "SquareRoot"), which contains the test cases of each function. Then, a parent section Math could separate the two functions from the rest of the code. 

Case:
A case is a collection of code, which itself represent a test case, as in unit test.
Code: 
There is two types of code: setup code, and test code
A setup code is a line or more, of statement, that responsible to setup the variables, objects, etc in order for the test code to carry out. It can be attached to a case, or a section, which its subsection will also contain the setup code. 
A test code is a condition statment, which return true if success, false if fail. 

# Grammar
A section begins with "//Test: section start [Section Name]", and end with "//Test: section stop". If [Section Name] is empty (The space after start still exist), it automatically jump back to the root section. 
A case begins with "//Test: case [Case Name]", and end with "//Test: endCase". [Case Name] must be at least one character.
As section and case are generated into separate functions, the naming must follow the proper function naming in the function. However, any space inside the name will be trimmed before hand, in order to improve readability
A setup code is declare as "//Test: setup [Setup code]". If the language require a semicolon (or a designated symbol) following the statment, please include the semicolon. 
A test code is declare as "//Test: testCode [actual code]". If the language does not require a semicolon (or a designated symbol) after a condition, please do NOT include semicolon. (fast way to verify: does it require you have a semicolon in the condition of if([condition])? )

# Run
SameLine [all the files you are inputting]
C/C++: All the C/C++ source files will generate a test_[filename] file, and a test.c/cpp. Then, compile all the generated file using a compiler, and execute the binary. 
Javascript: Open test.html

#Sample output
C/C++ [example/bootupTest.c]:
bootupTest
    Para
        Success on line 31 in example/bootupTest.c
        Success on line 35 in example/bootupTest.c
    SquareFunction
        Success on line 22 in example/bootupTest.c
        Success on line 17 in example/bootupTest.c

JS [example/bootupTest.js]:
bootupTest

 Para

  Success on line 20 in example/bootupTest.js
 SquareFunction

  Success on line 14 in example/bootupTest.js


#Tools for compile
Currently: Xcode
Makefile compile will come in the next push
