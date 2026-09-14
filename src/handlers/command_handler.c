#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.h"

static void execute_external(char *args[]) {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return;
	}
	if (pid == 0) {
		execvp(args[0], args);
		perror(args[0]);
		_exit(EXIT_FAILURE);
	} else {
		int status;
		waitpid(pid, &status, 0);
	}
} 
void execute_command(int argc, char *args[]){
  if (argc == 0) {
    return;
  }
  if (strcmp(args[0], "ls") == 0){
    built_ls(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "cd") == 0) {
    builtin_cd(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "cat") == 0) {
    builtin_cat(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "clear") == 0) {
    builtin_clear();
  }
  else if (strcmp(args[0], "pwd") == 0) {
    builtin_pwd();
  }
  else if (strcmp(args[0], "mkdir") == 0) {
    builtin_mkdir(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "touch") == 0) {
    if (argc > 1) {
      builtin_touch(argc, args);
    } else {
      fprintf(stderr, "touch: missing file operand\n");
    }
  }
  else {
	  execute_external(args);
  }
}


