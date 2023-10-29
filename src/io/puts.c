// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#ifndef EOF
# define EOF (-1)
#endif

int puts(const char *s)
{
    int ret = 0;
    int i = 0;
    for( ;s[i] != '\0';++i)
    {
        ret = write(1, &s[i], 1);
        if(ret < 0)
            return EOF;
    }
    ret = write(1, "\n", 1);
    if (ret < 0)
        return EOF;
    return 0;
}

