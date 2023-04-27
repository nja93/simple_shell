#include "melsh.h"

/**
 * home_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int home_env(prog_data *data)
{
	int i;
	char c_name[50] = {'\0'};
	char *val_dup = NULL;

	if (data->tokens[1] == NULL)
		show_env(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				val_dup = copy_str(get_env_value(c_name, data));
				if (val_dup != NULL)
					set_env_value(c_name, data->tokens[1] + i + 1, data);

				show_env(data);
				if (get_env_value(c_name, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					set_env_value(c_name, val_dup, data);
					free(val_dup);
				}
				return (0);
			}
			c_name[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * set_home_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_home_env(prog_data *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	set_env_value(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * unset_home_env - Deals with the unset variable
 * @data: struct for the program's data'
 * Return: ret val on Success and -1 on failure.
 */
int unset_home_env(prog_data *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	rmv_env_value(data->tokens[1], data);
	return (0);
}

