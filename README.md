knode-language
==============
Compiler for knode, a language focused on making graph operations dead simple.

Compiling the Compiler
======================
Run `make` to compile the knode compiler.


Running
=======
In order to create the compiler, run the following command:

    ./knode <source_file>

Testing
=======
For tests, there are two folders that can be found and used- that is the folders testPass and testFail. testPass is used for files that
we expect and want to pass while testFail is used for files that are expected to fail.

Running the test suite
----------------------
After compiling the compiler, run:

    ./testPassFail.sh

For every test file in the folder testPass, this should output 

    <file_name>...Done testing
    OK
    
if the test passed, or

    <file_name>...<ERROR TYPE>
    FAILED
    
For every test file in the folder testFail, this should output 

    <file_name>...<ERROR TYPE>
    OK
    
if the test failed, or

    <file_name>...Done testing
    FAILED

if the test passed. This is because we want files to fail if they are in testFail.

To add a file to the test suite, create a knode program named `test-<your_file_name>.kn`, and place it in the correct testing folder. The correct folder for tests you want passed is ./testPass and the correct folder for tests you want failed is ./testFail

Memory testing
--------------
In order to print out helpful memory debugging statements when working with the memory used in the abstract syntax tree, 
add the flag `-DMEMTRACE` to `CFLAGS` and `LDFLAGS` in the Makefile. This will indicate when memory is being freed for a node
in the abstract syntax tree.

Grammar
=======
A high level view of the grammar

Lexer & Parser
==============
In order to compile the lexer, run `make lexer`.
