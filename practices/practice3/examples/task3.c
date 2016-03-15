#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[]) {
	int pipefd[2];
	pipe(pipefd);
	pid_t cat, grep;
	int cat_status, grep_status;
	cat = fork();
	if (cat == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("cat", "cat", argv[1], NULL);
	}
	else {
		grep = fork();
		if (grep == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execlp("grep", "grep", "int", NULL);
		}
		else {
			waitpid(cat, &cat_status, WIFEXITED(cat_status));
			waitpid(grep, &grep_status, WIFEXITED(grep_status));
		}
	}
	return;
}
