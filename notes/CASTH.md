# CASTH DESIGN NOTES

CASTH is a (functional?) programming language which works primarily on vectors/array of data. 

## OPERATIONS
- Binary operators (+, /, -, *) on individual and vectors of data:
    - a = {1,2,3,4} => a+4 = {5,6,7,8}
    - a = 4 => a+4 = 8

## IMPLEMENTATION NOTES
- Lexical Analysis
    * Process of onverting a sequence of characters into lexical tokens
    * Lexical tokens is a string with an assigned meaning, which contains a token name and (optional) value.
    * Types of lexical tokens: 
        1. Identifier (Variables)
        2. Keyword (If, While, ...)
        3. Separator ({}, (), ;)
        4. Operator (+, -, *, /)
        5. Literal  (Raw values of Data) --> Char, Float, Integer...
        6. Comment (/* Hello */) 
- Parsing
- Semantic Analysis
- Optimization
- Code Generation

### LEXICAL TOKENS
- Tokens:
    - Binary Operators: +, -, *, /, %
    - Comparison Operators: >, <, <=, >=, ==, !=
    - Keywords: If, While, For
    - Identifiers: Variables --> Any Variable Name
    - Literals: Integer, Float, Character...
    - Comments: /* */
    - Separators: {, }, [, ], (, )

### PARSING


### BIBLIOGRAPHY
- [How to Build a new Programming Language](https://pgrandinetti.github.io/compilers/page/how-to-build-a-new-programming-language/)
- [Parsing Tokens](https://tomassetti.me/guide-parsing-algorithms-terminology/)
- [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
- [Compilers: Principles, Techniques and Tools](https://github.com/qshadun/books/blob/master/Compilers%20Principles%20Techniques%20and%20Tools%20(2nd%20Edition)%20.pdf)