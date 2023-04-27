#ifndef MELSH_H
#define MELSH_H

#define PROMPT_MELSH "$"
#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1024

#define CD_HELP "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argumenthelp is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define EXIT_HELP "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define ENV_HELP "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define SETENV_HELP "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define UNSETENV_HELP "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP_MELSH "help=\n"\
"MELSH:\tShell help menu\n\n"\
"	A brief on the builtin commands within the MELSH shell.\n\n"\
"	A brief summary of builtin commands is displayed.If the command name is\n"\
"	specified a detailed help description is given on the command entered,\n"\
"	otherwise the help menu is printed.\n"\
"	Use the following format to use the builtin commands of this shell:\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\t[env variable]\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[command name]\n\n"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} prog_data;
/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(prog_data *data);
} builtins;

/*========  main.c  ========*/
void init_shell(prog_data *data, int arc, char *argv[], char **env);
void sys_info(char *prompt, prog_data *data);
void melsh_prompt(int opr UNUSED);

/*========  melsh_getline.c  ========*/
int melsh_getline(prog_data *data);
int handle_logical_operators(char *arr_cmnds[], int i, char arr_ops[]);

/*======== handle_melsh_memory.c ========*/
void melsh_var(prog_data *data);
void melsh_alias(prog_data *data);
int expand_buffer(char *buffer, char *string_to_add);

/*======== melsh_mytoken.c ========*/
void melsh_tokenizer(prog_data *data);

/*======== handle_melsh_tokens.c =======*/
char *melsh_strtok(char *line, char *delim);

/*======== handle_melsh_syscalls.c ========*/
int melsh_syscalls(prog_data *data);

/*======== handle_melsh_builtins.c ========*/
int melsh_builtins(prog_data *data);

/*======== handle_melsh_path.c ========*/
int read_path(char *full_path);
char **path_parsed(prog_data *data);
int locate_path(prog_data *data);

/*======== handle_melsh_data.c ========*/
void free_argv_array(char **directories);
void rel_prog_data(prog_data *data);
void rmv_data(prog_data *data);

/*======== handle_melsh_cmnds.c ========*/
int melsh_exit(prog_data *data);
int melsh_cd(prog_data *data);
int melsh_wrkng_dir(prog_data *data, char *new_dir);
int melsh_help(prog_data *data);
int melsh_bltn_alias(prog_data *data);

/*======== handle_melsh_bltnenv.c ========*/
int home_env(prog_data *data);
int set_home_env(prog_data *data);
int unset_home_env(prog_data *data);

/*======== handle_melsh_envs.c ========*/
char *get_env_value(char *name, prog_data *data);
int set_env_value(char *key, char *value, prog_data *data);
int rmv_env_value(char *key, prog_data *data);
void show_env(prog_data *data);

/*======== handle_melsh_stdout.c ========*/
int _write(char *string);
int _print(char *string);
int handle_errors(int errorcode, prog_data *data);

/*======== melsh_strng.c ========*/
int get_len(char *string);
char *copy_str(char *string);
int check_str(char *string1, char *string2, int number);
char *str_join(char *string1, char *string2);
void reverse_string(char *string);

/*======== mng_melsh_stdin.c ========*/
void num_to_str(long number, char *string, int base);
int _atoi(char *s);
int char_count(char *string, char *character);

/*======== handle_melsh_alias.c ========*/
int alias_mng(prog_data *data, char *alias);
char *show_alias(prog_data *data, char *name);
int alias_set(char *alias_string, prog_data *data);

#endif /* MELSH_H */
