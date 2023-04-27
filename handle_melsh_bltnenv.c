#include "melsh.h"

/**
 * melsh_builtins - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int melsh_builtins(prog_data *data)
{
	int i;
	builtins options[] = {
		{"exit", melsh_exit},
		{"help", melsh_help},
		{"cd", melsh_cd},
		{"alias", melsh_bltn_alias},
		{"env", home_env},
		{"setenv", set_home_env},
		{"unsetenv", unset_home_env},
		{NULL, NULL}
	};

	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (check_str(options[i].builtin, data->command_name, 0))
		{
			return (options[i].function(data));
		}
	}
	return (-1);
}

