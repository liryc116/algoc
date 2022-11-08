#ifndef ANSWER_H
#define ANSWER_H

#include <stddef.h>

struct answer
{
    unsigned int status_code;
    char *reason_phrase;
    size_t len;
};

char *build_answer(void);

void send_answer(void);

#endif /* ! ANSWER_H */
