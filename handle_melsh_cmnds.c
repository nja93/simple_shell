#include "melsh.h"

/**
 * melsh_exit- exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int melsh_exit(prog_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	rmv_data(data);
	exit(errno);
}

/**
 * melsh_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int melsh_cd(prog_data *data)
{
	char *home_directory = get_env_value("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (check_str(data->tokens[1], "-", 0))
		{
			dir_old = get_env_value("OLDPWD", data);
			if (dir_old)
				error_code = melsh_wrkng_dir(data, dir_old);
			_print(get_env_value("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (melsh_wrkng_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_directory)
			home_directory = getcwd(old_dir, 128);

		return (melsh_wrkng_dir(data, home_directory));
	}
	return (0);
}

/**
 * melsh_wrkng_dir - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int melsh_wrkng_dir(prog_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!check_str(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_env_value("PWD", new_dir, data);
	}
	set_env_value("OLDPWD", old_dir, data);
	return (0);
}

/**
 * melsh_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int melsh_help(prog_data *data)
{
	int i, length = 0;
	char *msg[6] = {NULL};

	msg[0] = HELP_MELSH;

	if (data->tokens[1] == NULL)
	{
		_print(msg[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	msg[1] = EXIT_HELP;
	msg[2] = ENV_HELP;
	msg[3] = SETENV_HELP;
	msg[4] = UNSETENV_HELP;
	msg[5] = CD_HELP;

	for (i = 0; msg[i]; i++)
	{
		length = get_len(data->tokens[1]);
		if (check_str(data->tokens[1], msg[i], length))
		{
			_print(msg[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * melsh_bltn_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int melsh_bltn_alias(prog_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (alias_mng(data, NULL));

	while (data->tokens[++i])
	{
		if (char_count(data->tokens[i], "="))
			alias_set(data->tokens[i], data);
		else
			alias_mng(data, data->tokens[i]);
	}

	return (0);
}




