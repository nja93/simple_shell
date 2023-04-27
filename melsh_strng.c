#include "melsh.h"

/**
 * get_len - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int get_len(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * copy_str - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *copy_str(char *string)
{
	char *res;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = get_len(string) + 1;

	res = malloc(sizeof(char) * len);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		res[i] = string[i];
	}

	return (res);
}

/**
 * check_str - Compare two strings
 * @string1: String one, or the shorter
 * @string2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int check_str(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (get_len(string1) != get_len(string2))
			return (0);
		for (i = 0; string1[i]; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < number ; i++)
		{
			if (string1[i] != string2[i])
			return (0);
		}
		return (1);
	}
}

/**
 * str_join - concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_join(char *string1, char *string2)
{
	char *res;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = get_len(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = get_len(string2);

	res = malloc(sizeof(char) * (length1 + length2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		res[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		res[length1] = string2[length2];
		length1++;
	}

	res[length1] = '\0';
	return (res);
}


/**
 * reverse_string - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void reverse_string(char *string)
{

	int i = 0, len = get_len(string) - 1;
	char hld;

	while (i < len)
	{
		hld = string[i];
		string[i++] = string[len];
		string[len--] = hld;
	}
}






