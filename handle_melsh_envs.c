#include "melsh.h"

/**
 * get_env_value - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *get_env_value(char *key, prog_data *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_len = get_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (check_str(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			return (data->env[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * set_env_value - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int set_env_value(char *key, char *value, prog_data *data)
{
	int i, key_len = 0, new_key_value = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_len = get_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (check_str(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			new_key_value = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = str_join(copy_str(key), "=");
	data->env[i] = str_join(data->env[i], value);

	if (new_key_value)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * rmv_env_value - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int rmv_env_value(char *key, prog_data *data)
{
	int i, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	key_len = get_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (check_str(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * show_env - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void show_env(prog_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}



