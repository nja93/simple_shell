#include "melsh.h"

/**
 * rel_prog_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void rel_prog_data(prog_data *data)
{
	if (data->tokens)
		free_argv_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * rmv_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void rmv_data(prog_data *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	rel_prog_data(data);
	free_argv_array(data->env);
	free_argv_array(data->alias_list);
}

/**
 * free_argv_array - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_argv_array(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}


