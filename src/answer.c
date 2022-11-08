#include "answer.h"

static char *build_date(void)
{
	return NULL;
}

char *build_answer(void)
{
	// write HTTP/1.1 status_code reason_phrase
	// Date: build_date()
	// Content-Length: stat(2)
	// \r\n
	return NULL;
}

void send_answer(void)
{
	// Send the answer to the client
	// send file content with sendfile
}
