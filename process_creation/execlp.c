#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(void){

	pid_t pid;

	pid = fork();

	if (pid < 0){

		fprintf(stderr, "error -- failed to fork()");
		exit(EXIT_FAILURE);
	}

	if (pid > 0){

		int child_ret;

		waitpid(pid, &child_ret, 0);
		printf("Child exited with return code %d\n", WEXITSTATUS(child_ret));

	} else {

		execlp("ls", "ls", "-lh", NULL);

		printf("child - failed to exec\n");
		exit(EXIT_FAILURE);

	}

	return 0;

}