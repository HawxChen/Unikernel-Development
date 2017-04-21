# Add dup3, a system call, into osv
#### Implementation of Cloud OS functionalities
----
This practice includes 2 parts
- dup3.cc
  - place 
- tst-dup3.cc
  - Output
      isatty test!
      Process: dup3(tmpfd, STDIN\_FILENO, 0)
      PASS: isNOTatty stdin fd
      PASS: isatty stdout fd
      PASS: isatty stderr fd
      SUMMARY: 3 tests / 0 failures
