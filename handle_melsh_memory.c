#include "melsh.h"

/**
 * melsh_var - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void melsh_var(prog_data *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	expand_buffer(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			num_to_str(errno, exp, 10);
			expand_buffer(line, exp);
			expand_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			num_to_str(getpid(), exp, 10);
			expand_buffer(line, exp);
			expand_buffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				exp[j - 1] = line[i + j];
			tmp = get_env_value(exp, data);
			line[i] = '\0', exp[0] = '\0';
			expand_buffer(exp, line + i + j);
			tmp ? expand_buffer(line, tmp) : 1;
			expand_buffer(line, exp);
		}
	if (!check_str(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = copy_str(line);
	}
}

/**
 * melsh_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void melsh_alias(prog_data *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	expand_buffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			exp[j] = line[i + j];
		exp[j] = '\0';

		tmp = show_alias(data, exp);
		if (tmp)
		{
			exp[0] = '\0';
			expand_buffer(exp, line + i + j);
			line[i] = '\0';
			expand_buffer(line, tmp);
			line[get_len(line)] = '\0';
			expand_buffer(line, exp);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = copy_str(line);
	}
}

/**
 * expand_buffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @string_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int expand_buffer(char *buffer, char *string_to_add)
{
	int len, i;

	len = get_len(buffer);
	for (i = 0; string_to_add[i]; i++)
	{
		buffer[len + i] = string_to_add[i];
	}
	buffer[len + i] = '\0';
	return (len + i);
}




