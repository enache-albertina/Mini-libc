#ifndef _TIME_H
#define _TIME_H

typedef long time_t;
typedef long suseconds_t;

struct timespec{
    time_t seconds;
    long n_seconds;
};


int nanosleep(const struct timespec *req, struct timespec *rem);

#endif
