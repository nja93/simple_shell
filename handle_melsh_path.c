#include "melsh.h"

int read_path(char *full_path);

/**
 * locate_path - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int locate_path(prog_data *data)
{
	int i = 0, ret_code = 0;
	char **dirs;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (read_path(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_join(copy_str("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dirs = path_parsed(data);

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{
		dirs[i] = str_join(dirs[i], data->tokens[0]);
		ret_code = read_path(dirs[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = copy_str(dirs[i]);
			free_argv_array(dirs);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_argv_array(dirs);
	return (ret_code);
}

/**
 * path_parsed - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **path_parsed(prog_data *data)
{
	int i = 0;
	int count_dirs = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = get_env_value("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = copy_str(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirs++;
	}

	tokens = malloc(sizeof(char *) * count_dirs);
	i = 0;
	tokens[i] = copy_str(melsh_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = copy_str(melsh_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * read_path - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int read_path(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}



