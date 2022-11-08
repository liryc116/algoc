#ifndef REQUEST_H
#define REQUEST_H

#define BUFFER_SIZE 1024

enum method_type
{
    UNDEFINED,
    GET,
    HEAD,
};

struct request
{
    enum method_type method;
    char *target;
    char *host;
};

// Returns a request structure
// NULL if the HTPP version is incorrect (not 1.1)
struct request *parse_request(int socket);

#endif /* ! REQUEST_H */
