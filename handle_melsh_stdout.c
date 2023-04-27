#include "melsh.h"

/**
 *  _write- writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write(char *string)
{
	return (write(STDOUT_FILENO, string, get_len(string)));
}

/**
 * _print - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDERR_FILENO, string, get_len(string)));
}

/**
 * handle_errors - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int handle_errors(int errorcode, prog_data *data)
{
	char n_str[10] = {'\0'};

	num_to_str((long) data->exec_counter, n_str, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_print(data->program_name);
		_print(": ");
		_print(n_str);
		_print(": ");
		_print(data->tokens[0]);
		if (errorcode == 2)
			_print(": Illegal number: ");
		else
			_print(": can't cd to ");
		_print(data->tokens[1]);
		_print("\n");
	}
	else if (errorcode == 127)
	{
		_print(data->program_name);
		_print(": ");
		_print(n_str);
		_print(": ");
		_print(data->command_name);
		_print(": not found\n");
	}
	else if (errorcode == 126)
	{
		_print(data->program_name);
		_print(": ");
		_print(n_str);
		_print(": ");
		_print(data->command_name);
		_print(": Permission denied\n");
	}
	return (0);
}






