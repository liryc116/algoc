#ifndef REQUEST_H
#define REQUEST_H

enum method_type
{
    GET,
    HEAD,
};

struct request
{
    enum method_type method;
    char *host;
    char *target;
};

struct request *parse_request(void);

#endif /* ! REQUEST_H */
