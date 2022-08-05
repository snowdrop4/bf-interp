bf-interp
=========

About
-----
Mildly optimising brainfuck interpreter written in C++.
Has an optional debug and step-through mode.

Implementation details
----------------------
Default tape data type is unsigned char.
Default tape size is 30,000.

Data values loop round, eg. increasing the default data type (unsigned char) from 255 will yield 0.
Checks are done to make sure the dataPtr does not exceed the tape size, or is less than 0.

When an EOF is received with the command `,` a 0 is returned by the interpreter.

Strings of `>`, `<`, `+`, `-` are compressed into a single command.
