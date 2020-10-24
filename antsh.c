#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 4096
#define CMD_NOT_FOUND 127

void die(const char *msg, ...);

int main(void) {

	char buf[MAXLINE];
	pid_t pid;
	int status;

	// Print prompt
	printf("🐜 ");

	while (fgets(buf, MAXLINE, stdin)) {

		if (buf[strlen(buf) - 1] == '\n') {
			// Replace newlines with null terminators
			buf[strlen(buf) - 1] = 0;
		}

		if ((pid = fork()) < 0) {
			// Fork error
			die("fork error\n");
		} else if (pid == 0) {
			// Child
			execlp(buf, buf, NULL);
			die("error executing `%s`\n", buf);
			exit(CMD_NOT_FOUND);
		} else {
			// Parent
			if ((pid = waitpid(pid, &status, 0)) < 0) {
				die("waitpid() failure\n");
			}
			printf("🐜 ");
		}
	}

	return 0;
}

void die(const char *msg, ...) {
	va_list argptr;
	va_start(argptr, msg);
	vfprintf(stderr, msg, argptr);
	va_end(argptr);
	die(0);
}

