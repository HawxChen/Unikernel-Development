#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>


unsigned int tests_total = 0, tests_failed = 0;

void report(const char* name, bool passed)
{
   static const char* status[] = {"FAIL", "PASS"};
   printf("%s: %s\n", status[passed], name);
   tests_total += 1;
   tests_failed += !passed;
}

int main(void)
{
   int fds[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
   int tmpfd = open("/tmp", 0, O_DIRECTORY);
   int retfd = 0;
   int new_stdinfd = 45;

   retfd = dup3(STDIN_FILENO, new_stdinfd, 0);
   report("Return value should be 45\0", retfd == new_stdinfd);

   retfd = dup3(tmpfd, STDIN_FILENO, 0);
   report("Return value should be 0 \0", retfd == STDIN_FILENO);


   retfd = dup3(100, STDOUT_FILENO, 0);
   report("Return value should be EBADF \0", EBADF == errno);

   retfd = dup3(STDOUT_FILENO, STDOUT_FILENO, 0);
   report("Return value should be EINVAL \0", EINVAL == errno);

   report("isNOTatty stdin fd\0", !isatty(fds[0]));
   report("isatty stdout fd\0", isatty(fds[1]));
   report("isatty stderr fd\0", isatty(fds[2]));

   close(tmpfd);
   printf("SUMMARY: %u tests / %u failures\n", tests_total, tests_failed);

   return 0;
}
