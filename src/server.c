#include "server.h"

void handle_request(void)
{
	// call parse_request()
	// call build_answer()
	// call send_answer()
}

static void server_loop(void)
{
	// copy from getaddrinfo(3)
	// call handle_request()
}

void launch_daemon(void)
{
	// fork
	// close child fd
	// terminate parent
}
