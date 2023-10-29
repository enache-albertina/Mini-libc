#include <time.h>
#include <internal/syscall.h>
#include <errno.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    return syscall(__NR_nanosleep, req, rem);
}
