A Boolean Expression Parser, Evaluator, and Truth Table Generator written in C++.

LogicCraft reads a Boolean expression, validates its syntax, builds an Abstract Syntax Tree (AST) using a recursive-descent parser, and evaluates the expression for every possible combination of its variables. It also prints the tree structure so the parsing process is easy to inspect.
Features
- Boolean expression parsing with variables A–Z.
- Supported operators: NOT (!), AND (&), XOR (^), and OR (|).
- Parentheses for explicit grouping and operator precedence.
- Input validation for supported symbols, balanced parentheses, and expression structure.
- AST construction using a recursive-descent parser.
- Recursive evaluation of the AST for a given variable assignment.
- Automatic truth table generation for all 2^n assignments of the distinct variables.
- Alphabetically ordered variables in the generated table.
- Console AST visualization using an indented tree printout.
Operator Precedence
From highest to lowest:
Priority	Operator	Meaning	Example
1	!	NOT	!A
2	&	AND	A&B
3	^	XOR	A^B
4	|	OR	A|B


Binary operators of the same precedence are parsed from left to right. Parentheses override the default precedence.
Example
Input:
(A&B)|!C
Abstract Syntax Tree:
|
  &
    A
    B
  !
    C
Truth table:
A B C | Result
0 0 0 | 1
0 0 1 | 0
0 1 0 | 1
0 1 1 | 0
1 0 0 | 1
1 0 1 | 0
1 1 0 | 1
1 1 1 | 1
How It Works
1. Read and validate input. Whitespace is removed, and the expression is checked before parsing.
2. Collect variables. Distinct uppercase variables are identified and arranged alphabetically.
3. Build the AST. The recursive-descent parser processes precedence levels through parseOr(), parseXor(), parseAnd(), parseNot(), and parsePrimary().
4. Generate assignments. For n distinct variables, iterate through 2^n Boolean combinations using bit operations.
5. Evaluate. For each assignment, recursively evaluate the AST and print the result.
The AST is constructed once and reused for every truth-table row.
Getting Started
Requirements
- A C++ compiler with C++11 or newer support (C++17 recommended).
- A terminal or C++ IDE, such as Visual Studio.
- No external libraries are required.
Run
1. Open the C++ project in your IDE and build it.
2. Run the executable.
3. Enter a Boolean expression when prompted.
4. View the AST and generated truth table in the console.
For a single-source-file version of the project, a typical command-line build is:
g++ -std=c++17 your_source_file.cpp -o LogicCraft
./LogicCraft
Replace your_source_file.cpp with the actual source filename. If your project uses multiple .cpp files, include them all in the build command. On Windows, the executable may be named LogicCraft.exe.
Implementation Notes
- Node represents an AST node, storing its symbol and pointers to child nodes.
- Parser performs recursive-descent parsing and returns the AST root.
- printTree() displays the AST using a preorder traversal.
- evaluate() recursively computes the value of the Boolean expression.
- A variable list and a parallel Boolean value vector represent assignments during truth-table generation.
Current Limitations and Planned Improvements
- Strengthen error handling throughout the parser and evaluator, including malformed input and incomplete parses.
- Replace manual ownership of tree nodes with safer C++ memory-management techniques (for example, smart pointers).
- Add automated tests for operator precedence, nested parentheses, repeated NOT operators, and invalid input.
- Improve the console interface and support exporting truth tables to files.
- Consider performance and output-size limits for expressions with many distinct variables, since a truth table grows exponentially (2^n rows).
Project Purpose
This project is a hands-on exercise in C++, recursive descent parsing, tree data structures, recursion, bitwise operations, and Boolean logic. It provides a foundation for future digital-logic simulation features.
