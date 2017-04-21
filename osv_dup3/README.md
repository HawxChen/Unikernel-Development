# Add dup3, a system call, into osv
#### Implementation of Cloud OS functionalities
----
This practice achieves the dup3 system call through 2 parts
- dup3.cc
  - Remove the multiple definitions of dup3(int, int, int) in fs folder
  - This file construct the main program, dup3 system call.
- tst-dup3.cc
  - This test case replaces the STDIN_FILENO with tmpfd.
  - Output
  ````
    isatty test!
    Process: dup3(tmpfd, STDIN\_FILENO, 0)
    PASS: isNOTatty stdin fd
    PASS: isatty stdout fd
    PASS: isatty stderr fd
    SUMMARY: 3 tests / 0 failures
  ````
