knode-language
==============
Compiler for knode, a language focused on making graph operations dead simple.
Developed by Jonathan Balsano, Jon Jia, Krista Kohler, Maria Moresco, and Ruby
Robinson.

Compiling the Compiler
======================
Run `make` to compile the knode compiler.


Running
=======
In order to compile a source program in knode, run the compiler with the following command

    ./knode <source_file> <output_executable>

Testing
=======
All testing knode files are kept within the `tests` directory and are formatted
with an appended -pass or -fail to designate whether the test should cause the
compiler to crash or not. Output is written to the file's name.log in the tests
folder and the executable is created as the file's name.out in the tests folder

Running the Test Suite
----------------------
After compiling the compiler, run:

    ./runTests

For every file in the tests folder, the tester will collect its output and give
live feedback as well as a concluding summary that outputs all errors.

To add a file to the test suite, create a knode program named 
`<your_file_name>-<pass_or_fail>.kn`, and place it in the `tests` folder. 

Memory testing
--------------
In order to print out helpful memory debugging statements when working with the
memory used in the abstract syntax tree, add the flag `-DMEMTRACE` to `CFLAGS` 
and `LDFLAGS` in the Makefile. This will indicate when memory is being freed 
for a node in the abstract syntax tree.

Components
==========
There are several components to the knode compilere each stored in different
locations.

The Preprocessor
----------------
Files for the preprocessor are kept in the `prep/` directory. The preprocessor
takes in a knode file and converts the whitespace into curly braces so that
the file is parsable by a CFG ready parser. It also removes comments at this
step. The precompiler is compiled as a part of the make process into `klp`.

The Translator
------------
Files for the translator are kept int the `comp/` directory. This is the bulk of
the compiler, written in C, and includes a variety of files:

  - **absyn.c/h**: Utilities for building the abstract syntax tree from a
    source file.
  - **lex.l**: The lexical analyzer, written as a flex parser.
  - **yacc.y**: The syntactic analyzer, written as a byson parser.
  - **codegen.c/h**: The functions used to generate C code from the nodes
    of the abstract syntrax tree. It's functions are called by...
  - **walker.c/h**: Walks the abstract syntax tree to perform typechecking
    using the functions from typecheck.c/h and then generate code using
    the functions in codegen.c/h.
  - **typecheck.c/h**: Contains functions that accept a node in the abstract
    syntax tree and check its children to ensure they are of matching/proper
    types.
  - **scope.c/h**: Contains scoping functionality, which is generated via a
    linked list of scopes that are contained in each set of compound statements.
  - **symtable.c/h**: Contains the auxiliary functions used by scopes to store
    and fetch symbols from the hashmap
  - **typechecktype.h**: Defines the struct for the typechecktype struct that
    can be associated with any node in the tree that can have a type.

All these files are used to generate `klc`, the knode compiler, which takes in
.kn files and translates them into C.

The Libraries
-------------
This folder contains a few libraries. The first is not node specific, but is a
common C library for hashmaps, UTHASH.h. It's a macro-based C library for
hashing and works wonders for what Knode needs to run. The other files bundled
in here provide the knode specific functionality that knode programs need to
run. They get bundled into `libknode.a` as a statically linked library. This
includes the functionality for dictionaries, nodes, edges, and smartpointers.

The Compiler
------------
The Knode compiler is a relatively simple sh script. It takes two arguments, the
first a knode source file, the second the desired output executable name. It
takes in the source file, runs it through the precompiler, into the compiler,
and then through gcc with the necessary libraries statically linked to produce
the desired executable.

The Test Suite
--------------
The test suite is contained within the `tests` directory. Here, we keep a series
of knode files that are run by the sh script, `runTests` in the base directory.
The script checks the file name to determine if it is a positive or negative
example of knode code, and runs it through, providing log output, and
executables in the `tests` directory, as well as a summary of all errors when it
completes.

Use Cases
---------
Contained in the folder `use-cases` this is mainly internal documentation for
how to use nodes, dicts, edges, and smartpointers in C.
