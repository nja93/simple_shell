#include "melsh.h"
/**
 * melsh_syscalls - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int melsh_syscalls(prog_data *data)
{
	int val = 0, status;
	pid_t pidd;

	val = melsh_builtins(data);
	if (val != -1)
		return (val);

	val = locate_path(data);
	if (val)
	{
		return (val);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			val = execve(data->tokens[0], data->tokens, data->env);
			if (val == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}




