#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#include "utils/vector.h"

struct vhost
{
    char *server_name;
    int port;
    char *ip;
    char *root_dir;
    char *default_file;
};

struct config
{
    char *pid_file;
    char *log_file;
    bool log;
    struct vector *vhost_list;
};

struct config *parse_config_file(char *filepath);

struct config *get_config(struct config *conf);

#endif /* ! CONFIG_H */
