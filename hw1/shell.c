#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1
#define INPUT_STRING_SIZE 80

#include "io.h"
#include "parse.h"
#include "process.h"
#include "shell.h"

int cmd_quit(tok_t arg[]) {
  printf("Bye\n");
  exit(0);
  return 1;
}

int cmd_help(tok_t arg[]);
int cmd_cd(tok_t arg[]);

/* Command Lookup table */
typedef int cmd_fun_t (tok_t args[]); /* cmd functions take token array and return int */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_quit, "quit", "quit the command shell"},
	{cmd_cd, "cd", "change the current working directory to the directory specified"}
};

int cmd_help(tok_t arg[]) {
  int i, ncmds;
  fun_desc_t cmd_desc;

	ncmds = sizeof(cmd_table)/sizeof(fun_desc_t);
	for (i = 0; i < ncmds; i++) {
    cmd_desc = cmd_table[i];
		printf("%s - %s\n",cmd_desc.cmd, cmd_desc.doc);
  }
  return 1;
}

int cmd_cd(tok_t args[]) {
	tok_t path = args[0];
	
	if (path != NULL)
	{
		if (chdir(path) < 0)
			fprintf(stdout, "cd: %s: No such file or directory\n", path);
	}

	return 1;
}

int lookup(char cmd[]) {
  int i, ncmds;
	
	ncmds = sizeof(cmd_table) / sizeof(fun_desc_t);
  for (i=0; i < ncmds; i++) {
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0)) return i;
  }
  return -1;
}

void init_shell()
{
  /* Check if we are running interactively */
  shell_terminal = STDIN_FILENO;
	printf("shell_terminal = %d\n", shell_terminal);

  /** Note that we cannot take control of the terminal if the shell
      is not interactive */
	shell_is_interactive = isatty(shell_terminal);

  if(shell_is_interactive){
		
		printf("shell pgid=%d\n", getpgrp());
		printf("shell pid=%d\n", getpid());
		printf("terminal pgid=%d\n", tcgetpgrp(shell_terminal));

    /* force into foreground */
    while(tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp()))
      kill( - shell_pgid, SIGTTIN);

    shell_pgid = getpid();
    /* Put shell in its own process group */
    if(setpgid(shell_pgid, shell_pgid) < 0){
      perror("Couldn't put the shell in its own process group");
      exit(1);
    }

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);
    tcgetattr(shell_terminal, &shell_tmodes);
  } else {
		printf("shell is not interactive\n");
	}
  /** YOUR CODE HERE */
}

/**
 * Add a process to our process list
 */
void add_process(process* p)
{
  /** YOUR CODE HERE */
}

/**
 * Creates a process given the inputString from stdin
 */
process* create_process(char* inputString)
{
  /** YOUR CODE HERE */
  return NULL;
}



int shell (int argc, char *argv[]) {
  char dir_buf[1024];
	char *line;
  tok_t *t;			/* tokens parsed from input */
	int  line_num, fundex, status;
	pid_t pid, ppid, cpid, cpgid, tcpid, w;

	line = malloc(INPUT_STRING_SIZE+1);			/* user input string */
  line_num = 0;
  fundex = -1;
  
	pid = getpid();		/* get current processes PID */
  ppid = getppid();	/* get parents PID */

  init_shell();

  printf("%s running as PID %d under %d\n",argv[0],pid,ppid);

	getcwd(dir_buf, sizeof(dir_buf));
  fprintf(stdout, "%d (%s): ", line_num, dir_buf);
  while ((line = freadln(stdin))){
    t = get_toks(line); /* break the line into tokens */
    if (t[0] == NULL) {
			// do nothing
    } else if((fundex = lookup(t[0])) >= 0) {
			cmd_table[fundex].fun(&t[1]);
    } else {
			cpid = fork();
			if (cpid == 0) { // child process
				if (execv(t[0], t) < 0) {
					perror(t[0]);
					exit(EXIT_FAILURE);
					return -1;
				}
			} else if (cpid > 0) { // parent process
				w = wait(&status);
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			} else {
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		getcwd(dir_buf, sizeof(dir_buf));
    fprintf(stdout, "%d (%s): ", ++line_num, dir_buf);
	}
  return 0;
}
  	
  	
