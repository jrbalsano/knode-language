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
We include a folder of test programs to test different components of our language.

Running the test suite
----------------------
After compiling the compiler, run:

    ./testall.sh

For every test file in the folder, this should output 

    <file_name>...Done testing
    OK
    
if the test passed, or

    <file_name>...<ERROR TYPE>
    FAILED
    
if the test failed.
To add a file to the test suite, create a knode program named `test-<your_file_name>.kn`, and place it in the /tests folder.

Testing Pass and Fail Files
=======
We include two folders in this second round of testing. One is called testPass and testFail.
Running the test suite
----------------------
After compiling the compiler, run:

    ./testall2.sh

Make sure to place your files that are expected to pass in the passFail folder and 
those that are expected to fail in the testFail folder. For every test file in the folders, this should output 

    <file_name>...Done testing
    OK
    
if the test passed, or

    <file_name>...<ERROR TYPE>
    FAILED
    
if the test failed.
If the file is in the testPass folder and it passes that means the code is working. If the file is in the testFail folder and it has an 
Ok that means that it failed as is expected.

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
