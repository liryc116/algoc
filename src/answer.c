#include "answer.h"

#include <stdlib.h>

static char *build_date(void)
{
    return NULL;
}

struct answer *build_answer(struct request *request)
{
    struct answer *answer = calloc(1, sizeof(struct request));
    answer->status_code = 200;
    if (request == NULL)
    {
        answer->status_code = 505;
        return;
    }
    if (request->method == UNDEFINED)
        answer->method = 405;
    // write HTTP/1.1 status_code reason_phrase
    // Date: build_date()
    build_date();
    // Content-Length: stat(2)
    // Connectino: close
    // \r\n
    return NULL;
}

void send_answer(struct request *request)
{
    // Send the answer to the client
    // send file content with sendfile
}
