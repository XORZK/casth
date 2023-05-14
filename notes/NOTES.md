# GENERAL NOTES 

## ON std::move
- Converter between ways the compiler considers an expression
  - l-value: Historically, l-values appear on the left-hand side of an assignment expression (functions that return a referennce [&], variable name, etc) --> yields an object reference.
  - r-value: A value that's not an l-value, including literals, and functions that return non-references.
  - x-value: Expiring value refers to an object near the end of its lifetime --> values are denoted as x-values so that efficient operations can be done on data. 
  - gl-value: Generalized l-value is an l-value or x-value.
  - pr-value: An r-value that is not an x-value --> function whose return type is not a reference.
- std::move converts an l-value to an x-value, and allows another object to contain the buffer of information contained by the, now, expiring object.

## FINITE STATE MACHINES

```
   start
     |
     v
   ->0
  |  |  (
  |  |-----> 1 return '(';
  |  |
  |  |  -         >
  |  |-----> 2 ------> 3 return TOK_ARROW;
  |  |    return '-';
  |  |
  |  |
  |  |                other      *
  |  |                ___       ___
  |  |               |   |     |   |
  |  |  /         *   \ /   *   \ /   /
  |   -----> 4 ------> 5 ------> 6 -----
  |                    ^         |      |
  |                    |         |      |
  |                     ---------       |
  |                       other         |
  |_____________________________________|
```

- FSM can be used to assign tokens for tokens that may share some characters --> divisor operator: /, commnet: /*

Taken from [here](http://www.cs.ecu.edu/karl/5220/spr16/Notes/Lexical/finitestate.html)