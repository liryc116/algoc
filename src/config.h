#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

struct config
{
	char *pid_file;
	char *log_file;
	bool log;
	char *server_name;
	int port;
	char *ip;
	char *root_dir;
	char *default_file;
};

struct config *parse_config_file(char *filepath);

#endif /* ! CONFIG_H */
