#include "request.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

static void request_free(struct request *request)
{
    free(request);
}

static void *request_err(struct request *request)
{
    request_free(request);
    return NULL;
}
// suppose perfect request
struct request *parse_request(int socket)
{
    struct request *request = calloc(1, sizeof(struct request));
    char buffer[BUFFER_SIZE];
    ssize_t read_len = recv(socket, buffer, BUFFER_SIZE, 0);
    if (read_len < 0)
        return NULL;
    char *meth = strtok(buffer, " ");
    if (strcmp(meth, "GET") == 0)
        request->method = GET;
    else if (strcmp(meth, "HEAD") == 0)
        request->method = HEAD;

    request->target = strtok(NULL, " ");
    char *version = strtok(NULL, "\r");
    if (strcmp("HTTP/1.1", version) != 0)
        return request_err(request);

    char *host = strtok(NULL, " ");
    if (strcmp(host, "\nHost:") == 0)
        request->host = strtok(NULL, "\r");

    return request;
}
