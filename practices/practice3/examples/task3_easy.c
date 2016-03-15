#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[]) {
	int pipefd[2];
	pipe(pipefd);
	pid_t cpid;
	cpid = fork();
	if (cpid == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("cat", "cat", argv[1], NULL);
	}
	else {
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execlp("grep", "grep", "int", NULL);
	}
	return;
}
