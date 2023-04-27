#include "melsh.h"
/**
* melsh_getline - read one line from the prompt.
* @data: struct for the program's data
* Return: reading counting bytes.
*/
int melsh_getline(prog_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *arr_cmnds[10] = {NULL};
	static char arr_ops[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!arr_cmnds[0] || (arr_ops[0] == '&' && errno != 0) ||
		(arr_ops[0] == '|' && errno == 0))
	{
		for (i = 0; arr_cmnds[i]; i++)
		{
			free(arr_cmnds[i]);
			arr_cmnds[i] = NULL;
		}
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);
		i = 0;
		do {
			arr_cmnds[i] = copy_str(melsh_strtok(i ? NULL : buff, "\n;"));
			i = handle_logical_operators(arr_cmnds, i, arr_ops);
		} while (arr_cmnds[i++]);
	}
	data->input_line = arr_cmnds[0];
	for (i = 0; arr_cmnds[i]; i++)
	{
		arr_cmnds[i] = arr_cmnds[i + 1];
		arr_ops[i] = arr_ops[i + 1];
	}
	return (get_len(data->input_line));
}
/**
* handle_logical_operators - checks and split for && and || operators
* @arr_cmnds: array of the commands.
* @i: index in the arr_cmnds to be checked
* @arr_ops: array of the logical operators for each previous command
* Return: index of the last command in the arr_cmnds.
*/
int handle_logical_operators(char *arr_cmnds[], int i,
char arr_ops[])
{
	char *temp = NULL;
	int j;

	for (j = 0; arr_cmnds[i] != NULL  && arr_cmnds[i][j]; j++)
	{
		if (arr_cmnds[i][j] == '&' && arr_cmnds[i][j + 1] == '&')
		{
			temp = arr_cmnds[i];
			arr_cmnds[i][j] = '\0';
			arr_cmnds[i] = copy_str(arr_cmnds[i]);
			arr_cmnds[i + 1] = copy_str(temp + j + 2);
			i++;
			arr_ops[i] = '&';
			free(temp);
			j = 0;
		}
		if (arr_cmnds[i][j] == '|' && arr_cmnds[i][j + 1] == '|')
		{
			temp = arr_cmnds[i];
			arr_cmnds[i][j] = '\0';
			arr_cmnds[i] = copy_str(arr_cmnds[i]);
			arr_cmnds[i + 1] = copy_str(temp + j + 2);
			i++;
			arr_ops[i] = '|';
			free(temp);
			j = 0;
		}}
	return (i);
}
