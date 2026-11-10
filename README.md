# Algorithms & Data Structures (C++)

Two assignments from 159.201 Algorithms and Data Structures at Massey University. Both scored 10/10. Each one is built on a data structure implemented by hand, with no STL containers for the core structure.

## A4: Big integer addition

[`a4-big-integer-addition/`](a4-big-integer-addition/main.cpp)

Adds two positive integers of any length, well past the range of `unsigned long long`.

- Digits are read as strings into a hand-written templated singly linked list (`List<T>` with `AddtoFront`, `AddtoBack` and iteration)
- Adds right to left with a carry, the way you would on paper
- Each result digit is pushed onto the front of the result list, so it comes out in the right order with no reversal step

```
$ printf '535953791669899051588630937807\n40058549908817013181945150931\n' | ./a4
576012341578716064770576088738
```

## A5: Reverse Polish notation to infix

[`a5-rpn-to-infix/`](a5-rpn-to-infix/main.cpp)

Reads an RPN expression and prints the fully bracketed infix version.

- Builds an expression tree with a stack of tree pointers: digits are pushed as leaves, and each operator pops two subtrees and pushes a new node
- In-order traversal prints the infix form, wrapping every operator node in brackets
- The stack is a hand-written linked list

```
$ echo '123*4-+' | ./a5
(1+((2*3)-4))
```

## Build and test

```sh
make test
```

## Possible improvements

- Free list and tree nodes in the destructors (both currently leak, which doesn't matter for a single-run program)
- A4 copies the lists into vectors to walk them backwards. A doubly linked list, or storing digits in reverse order, would avoid the copy
- Validate input: non-digit characters in A4, malformed RPN (stack underflow) in A5
