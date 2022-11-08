#ifndef ANSWER_H
#define ANSWER_H

#include <stddef.h>

#include "request.h"

struct answer
{
    unsigned int status_code;
    char *reason_phrase;
    size_t len;
};

struct answer *build_answer(struct request *request);

void send_answer(struct request *request);

#endif /* ! ANSWER_H */
