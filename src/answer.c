#include "answer.h"

#include <stdlib.h>

#include "config.h"

static char *build_date(void)
{
    return NULL;
}

static char *build_path(char *root_dir, char *file_path)
{
    //
}

struct answer *build_answer(struct request *request, struct vhost *host)
{
    struct answer *answer = calloc(1, sizeof(struct request));
    answer->status_code = 200;
    if (request == NULL)
    {
        answer->status_code = 505;
        return answer;
    }
    else if (request->target == NULL || request->host == NULL)
        answer->status_code = 400;
    else if (request->method == UNDEFINED)
        answer->status_code = 405;

    char *filepath = build_path(host->root_dir, request->target);
    if (access(filepath, F_OK) == -1)
        answer->status_code = 404;
    else if (access(filepath, R_OK) == -1)
        answer->status_code = 403;
    // write HTTP/1.1 status_code reason_phrase
    // Date: build_date()
    build_date();
    // Content-Length: stat(2)
    // Connectino: close
    // \r\n
}

void send_answer(struct request *request)
{
    // Send the answer to the client
    // send file content with sendfile
}
