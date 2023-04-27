#include "melsh.h"
/**
 * alias_mng - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int alias_mng(prog_data *data, char *alias)
{
	int i, j, al_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		al_len = get_len(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (check_str(data->alias_list[i], alias, al_len)
				&&	data->alias_list[i][al_len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				expand_buffer(buffer, "'");
				expand_buffer(buffer, data->alias_list[i] + j + 1);
				expand_buffer(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * show_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *show_alias(prog_data *data, char *name)
{
	int i, al_len;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	al_len = get_len(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (check_str(name, data->alias_list[i], al_len) &&
			data->alias_list[i][al_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[i] + al_len + 1);
		}
	}
	return (NULL);

}

/**
 * alias_set - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int alias_set(char *alias_string, prog_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *tmp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			tmp = show_alias(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (check_str(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (tmp)
	{
		expand_buffer(buffer, "=");
		expand_buffer(buffer, tmp);
		data->alias_list[j] = copy_str(buffer);
	}
	else
		data->alias_list[j] = copy_str(alias_string);
	return (0);
}

