#include <unistd.h>
#define open __open_variadic
#define fcntl __fcntl_variadic
#include <fcntl.h>
#undef open
#undef fcntl
#include <osv/file.h>
#include <sys/file.h>
#include <errno.h>
#include <fcntl.h>

int dup3(int oldfd, int newfd, int flags)
{
    struct file *fp;
    int error;

    /*
     * Don't allow any argument but O_CLOEXEC.  But we even ignore
     * that as we don't support exec() and thus don't care.
     */
    if ((flags & ~O_CLOEXEC) != 0) {
        error = EINVAL;
        goto out_errno;
    }

    if (oldfd == newfd) {
        error = EINVAL;
        goto out_errno;
    }

    error = fget(oldfd, &fp);
    if (error)
        goto out_errno;

    error = fdset(newfd, fp);
    if (error) {
        fdrop(fp);
        goto out_errno;
    }

    fdrop(fp);
    return newfd;

    out_errno:
    errno = error;
    return -1;
}
