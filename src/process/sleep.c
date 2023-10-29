#include <time.h>
#include <internal/syscall.h>
#include <errno.h>

int sleep(unsigned sec)
{
    struct timespec req = {sec, 0};
    struct timespec rem = {0, 0};
    int ret = nanosleep(&req, &rem);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}
