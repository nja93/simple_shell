#include "melsh.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	prog_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_shell(data, argc, argv, env);

	signal(SIGINT, melsh_prompt);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MELSH;
	}
	errno = 0;
	sys_info(prompt, data);
	return (0);
}

/**
 * melsh_prompt - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void melsh_prompt(int opr UNUSED)
{
	_write("\n");
	_write(PROMPT_MELSH);
}

/**
 * init_shell - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void init_shell(prog_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_print(data->program_name);
			_print(": 0: Can't open ");
			_print(argv[1]);
			_print("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = copy_str(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sys_info - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void sys_info(char *prompt, prog_data *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = melsh_getline(data);

		if (error_code == EOF)
		{
			rmv_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			melsh_alias(data);
			melsh_var(data);
			melsh_tokenizer(data);
			if (data->tokens[0])
			{
				error_code = melsh_syscalls(data);
				if (error_code != 0)
					handle_errors(error_code, data);
			}
			rel_prog_data(data);
		}
	}
}





