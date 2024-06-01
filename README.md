# Custom Programming Language Design with YACC

## Overview

This project involves designing an original programming language using YACC. The language includes various features such as type declarations, control statements, function definitions, and predefined functions. The project also requires creating a symbol table, performing semantic analysis, and implementing functions to evaluate expressions and determine their types.

## Features

### Type Declarations (0.75 pt)

Your language should include:
- Predefined types: `int`, `float`, `char`, `string`, `bool`
- Array types
- User-defined data types (similar to classes in object-oriented languages, but with custom syntax):
  - Specific syntax to allow initialization and use of variables of user-defined types
  - Specific syntax for accessing fields and methods
- Variable declarations/definitions, constant definitions, function definitions (0.25 pt)

### Control Statements and Assignments (0.25 pt)

- Control statements: `if`, `for`, `while`, etc.
- Assignment statements should be of the form: `left_value = expression` where `left_value` can be an identifier, an element of an array, or other valid elements.

### Expressions and Function Calls (2.25 pt)

- Arithmetic and boolean expressions (1.5 pt)
- Function calls that can have parameters such as expressions, other function calls, identifiers, constants, etc. (0.75 pt)

### Predefined Functions

Your language should include:
- `Eval(arg)`: Evaluates an arithmetic expression, variable, or number.
- `TypeOf(arg)`: Determines the type of the argument.

### Program Structure

Programs in your language should be structured into four sections:
1. Global variables
2. Functions
3. User-defined data types
4. A special function representing the entry point of the program

## Symbol Table (1.5 pt)

Create a symbol table for every input source program in your language, which includes:
- Information regarding variable or constant identifiers (type, value) (0.75 pt)
- Information regarding function identifiers (the returned type, the type and name of each formal parameter) (0.75 pt)

The symbol table should be printable in two files: `symbol_table.txt` and `symbol_table_functions.txt` (for functions).

## Semantic Analysis (2 pt)

Provide semantic analysis and check that:
1. Any variable that appears in a program has been previously defined, and any function that is called has been defined (0.25 pt).
2. A variable should not be declared more than once (0.25 pt).
3. All operands on the right side of an expression must have the same type (the language should not support casting) (0.5 pt).
4. The left side of an assignment has the same type as the right side (the left side can be an element of an array, an identifier, etc.) (0.5 pt).
5. The parameters of a function call have the types specified in the function definition (0.5 pt).

Detailed error messages should be provided if these conditions do not hold (e.g., which variable is not defined or is defined twice and the program line).

A program in your language should not execute if there are semantic or syntactic errors.

## Eval and TypeOf Functions (3 pt)

### Implementing TypeOf

`TypeOf(x + f(y))` should cause a semantic error if `TypeOf(x) != TypeOf(f(y))` (see semantic analysis point 3).

### Implementing Eval

Build abstract syntax trees (AST) for arithmetic expressions in a program. For every call of the form `Eval(expr)` where `expr` is of type `int`, the AST for the expression will be evaluated, and the actual value of `expr` will be printed.

For every assignment instruction `left_value = expr` (where `left_value` is an identifier or element of an array with `int` type), the AST will be evaluated, and its value will be assigned to `left_value`.

## Abstract Syntax Tree (AST)

#### AST Structure

- Inner nodes: Operators
- Leaves: Operands of expressions (numbers, identifiers, vector elements, function calls, etc.)

Example: `x + y * 5`

#### AST Data Structure

Write a data structure representing an AST.

#### AST Construction Function

buildAST(root, left_tree, right_tree, type)  
root: a number, an identifier, an operator, a vector element, other operands  
type: an integer or element of an enum representing the root type  

#### AST Evaluation Function 
Write a function evalAST(ast) which evaluates an AST and returns an int:  

If ast is a leaf labeled with:  
- A number: return the number  
- An identifier: return the value of the identifier  
- Anything else: return 0  
- Otherwise (if ast is a tree with the root labeled with an operator):  
Evaluate AST for left and right trees   
Combine the results according to the operation  
## Additional Notes  
Besides the homework presentation, students should be able to answer specific questions regarding grammars and parsing algorithms (related to the first part of your homework) or YACC details related to the second part (the answers will also be graded).
