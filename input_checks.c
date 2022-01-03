#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int ft_linesandchar(char *s)
{
	int i = 0;
	int count = 0;
	int lines = 0;
	int tetraminos = 0;

	while (s[i] != '\0')
	{
		if (s[i] != '#' && s[i] != '.' && s[i] != '\n')
			return (-1);
		if (s[i] == '#')
			count++;
		if (count > 4)
			return (-1);
		if (s[i] == '\n')
		{
			if (s[i + 1] != '\n')
				lines++;
			else
			{
				tetraminos++;
				count = 0;
			}
		}
		i++;
	}
	if (i % 21 != 0 || lines % 4 != 0 || tetraminos > 26)
		return (-1);
	printf("Checked input\n");
	return (1);
}

int	ft_check_tetros(char *s)
{
	int i;
	int connection;

	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			if (s[i + 1] == '#')
				connection++;
			if (s[i + 5] == '#')
				connection++;
			if (s[i - 1] == '#')
				connection++;
			if (s[i - 5] == '#')
				connection++;
		}
		if (s[i] == '\n' && s[i + 1] == '\n')
		{
			if (connection == 6 || connection == 8)
				return (1);
			else
				return (-1);
		}
		i++;
	}
	printf ("checked if tetros are connected\n");
	return (1);
}

// void print_error(char *str)
// {
// 	write (2, &str, ft_strlen(str));
// 	str++;
// }

// int main(int argc, char **argv)
// {
//     int		chars;
//     int file;
//     char	*buffer = (char *)malloc(sizeof(char) * 1000);
// 	int ret = 0;

//     file = open(argv[1], O_RDONLY);
//     chars = read(file, buffer, 1000);
//     buffer[chars] = '\0';
// 	if (ft_linesandchar(buffer) != 1 || ft_check_tetros(buffer) != 1)
// 		printf ("invalid input");
//     close(file);
// //    t_tetr *tetrimino = parse_input(buffer);
// //    for (int i = 0; i < (ft_strlen(buffer) + 1) / 21; i++)
// //    {
// //        print_tetrimino(tetrimino[i]);
// //        ft_putchar('\n');
// //    }
//     return (0);
// }
