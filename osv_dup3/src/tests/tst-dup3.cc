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
   printf("isatty test!\n");
   // Basic flow for test
   // 1) Take fds for stdin, stdout and stderr and call ttyname_r and ttyname
   // 2) Use an invalid fd (-1) and call ttyname_r and ttyname

   int fds[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
   int tmpfd = open("/tmp", 0, O_DIRECTORY);
   dup3(tmpfd, STDIN_FILENO, 0);
   report("isNOTatty std* fd\0", !isatty(fds[0]));
   report("isatty std* fd\0", isatty(fds[1]));
   report("isatty std* fd\0", isatty(fds[2]));

   close(tmpfd);
   printf("SUMMARY: %u tests / %u failures\n", tests_total, tests_failed);
#if 0
      int retval = ttyname_r(fds[i], buf, sizeof(buf));
      printf("fd: %d ttyname_r retval: %d, buf: %s\n", fds[i], retval, buf);
      if (fds[i] < 0) {
         report("[ttyname_r] bad fds\0", retval == EBADF);
      } else {
         report("[ttyname_r] std* fd\0",
                retval == 0 && strcmp(buf, "/dev/console\0") == 0);
      }
      char* tty = ttyname(fds[i]);
      printf("fd: %d ttyname retval: %s\n", fds[i], tty);
      if (fds[i] < 0) {
         report("[ttyname] bad fds\0", tty == NULL);
      } else {
         report("[ttyname] std* fds\0", strcmp(buf, "/dev/console\0") == 0);
      }
      memset(buf, 0, sizeof(buf));
   }
#endif

   return 0;
}
