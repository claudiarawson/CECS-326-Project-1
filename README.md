# CECS-326 Project 1
Group: Reichen Brown (ID: 029657509) & Claudia Rawson (ID: 030782685)

## SUMMARY
The project files contain a Makefile that will compile the code and provide a run function.

To begin, the director should contain the following files:

    1. FileCopy.c
    2. Makefile
    3. input.txt

    Note: The input file should be called: input.txt
        However, it can handle other file names.

Commands provided by the Makefile:

    1. make
    2. make run
    3. make clean

## HOW TO RUN
**Command: make**

    To compile the code, use the "make" command in the terminal by typing: make
        This will generate the executable file, filecopy.

**Command: make run**\
OR (If substituting input AND/OR output file names)\
**Command: make run INPUT=x OUTPUT=y**\
    x = yourInputFile.txt | y = yourOutputFile.txt

    Use the "run" command in the terminal by typing: make run
        If using unique file name(s), add: INPUT={yourInputFile.txt} OUTPUT={yourOutputFile.txt} 
            Ex. Command: make run INPUT=example.txt
            Ex. Command: make run INPUT=example.txt OUTPUT=exampleCopy.txt
            Ex. Command: make run OUTPUT=output.txt
    This should output a copy of your input file, default OUTPUT=copy.txt

**Command: make clean**\
OR (if output file name was substituted)\
**Command: make clean OUTPUT=y**\
    y = yourOutputFile.txt

    For more tests, you can remove the output files using "make clean"
        If using an output file with a unique name, add OUTPUT={yourOutputFile.txt}
            Ex. Command: make clean OUTPUT=exampleCopy.txt
    This should clean up your directory from previous test outputs.
