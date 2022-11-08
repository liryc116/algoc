#include "config.h"

#include <stdio.h>

// suppose perfect config
struct config *parse_config_file(char *filepath)
{
    (void)filepath;
    return NULL;
}

// pass NULL to get the config
// pass a pointer to set the config
struct config *get_config(struct config *conf)
{
    static struct config *saved_conf = NULL;
    if (conf != NULL)
        saved_conf = conf;
    return saved_conf;
}
