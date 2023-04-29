#include "main.h"

/**
 * _printf - printf function
 * @format: format.
 * Return: printed chars
 */

void print_buffer(char buffer[], int *buff_ind);

int _printf(const char *format, ...)
{
	int count, print = 0, print_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (count = 0; format && format[count] != '\0'; count++)
	{
		if (format[count] != '%')
		{
			buffer[buff_ind++] = format[count];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			print_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &count);
			width = get_width(format, &count, list);
			precision = get_precision(format, &count, list);
			size = get_size(format, &count);
			++count;
			print = handle_print(format, &count, list, buffer,
				flags, width, precision, size);
			if (print == -1)
				return (-1);
			print_chars += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (print_chars);
}

/**
 * print_buffer - prints contents of the buffer if it exists
 * @buffer: array of chars
 * @buff_ind: index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

