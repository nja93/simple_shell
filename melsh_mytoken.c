#include "melsh.h"
/**
 * melsh_tokenizer - function separates string using a delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void melsh_tokenizer(prog_data *data)
{
	char *delimiter = " \t";
	int i, j, count = 2, len;

	len = get_len(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}
	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				count++;
		}
	}
	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = copy_str(melsh_strtok(data->input_line, delimiter));
	data->command_name = copy_str(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = copy_str(melsh_strtok(NULL, delimiter));
	}}
