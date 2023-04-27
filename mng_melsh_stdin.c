#include "melsh.h"

/**
 * num_to_str - converts a number to a string.
 * @number: number to be convertn into a string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nothing.
 */
void num_to_str(long number, char *string, int base)
{
	int i = 0, inNegative = 0;
	long quotient = number;
	char letters[] = {"0123456789abcdef"};

	if (quotient == 0)
		string[i++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[i++] = letters[-(quotient % base)];
		else
			string[i++] = letters[quotient % base];
		quotient /= base;
	}
	if (inNegative)
		string[i++] = '-';

	string[i] = '\0';
	reverse_string(string);
}


/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to string origin.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * char_count - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int char_count(char *string, char *character)
{
	int i = 0, x = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			x++;
	}
	return (x);
}




