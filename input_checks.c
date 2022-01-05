#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/*changed location of count check, so checks if number of #'s is exactly 4 after each tetramino*/

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
		if (s[i] == '\n')
		{
			if (s[i + 1] != '\n')
				lines++;
			if (s[i + 1] == '\n' || s[i + 1] == '\0')
			{
				if (count != 4)
					return (-1);
				tetraminos++;
				count = 0;
			}
		}
		i++;
	}
	i++;
	if (i % 21 != 0 || lines % 4 != 0 || tetraminos > 26)
		return (-1);
	printf("Checked input\n");
	return (1);
}

/*changed index, and added offset to cut down connections from other tetraminos, its again way too big for norminette*/
/*but it passed all the testmaps i had, you could try to break it.
also i have no clue why condition i + 5 < j works, but i + 5 <= j doesn't? (lines 62 to 65)
EDIT: OH i guess its since offset is already at 21, and last tetramino wont have that many? u could still break it if u find a way*/
int	ft_check_tetros(char *s)
{
	int i;
	int connection;
	int j;
	int k;

	i = 0;
	connection = 0;
	k = 0;
	j = 21;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			if (s[i + 1] == '#' && i + 1 < j)
				connection++;
			if (s[i + 5] == '#' && i + 5 < j)
				connection++;
			if (s[i - 1] == '#' && i - 1 >= k)
				connection++;
			if (s[i - 5] == '#' && i - 5 >= k)
				connection++;
		}
		if (s[i] == '\n' && s[i + 1] == '\n' || s[i] == '\n' && s[i + 1] == '\0')
		{
			if (connection == 6 || connection == 8)
			{
				j = j + 21;
				k = k + 21;
				connection = 0;
			}
			else
				return (-1);
		}
		i++;
	}
	printf ("checked if tetros are connected\n");
	return (1);
}

//void print_error(char *str)
//{
//	write (2, &str, ft_strlen(str));
//	str++;
//}

int main(int argc, char **argv)
{
   int		chars;
   int file;
	char	*buffer = (char *)malloc(sizeof(char) * 1000);
	int ret = 0;

   file = open(argv[1], O_RDONLY);
   chars = read(file, buffer, 1000);
   buffer[chars] = '\0';
	if (ft_linesandchar(buffer) != 1 || ft_check_tetros(buffer) != 1)
		printf ("invalid input");
   close(file);
//   t_tetr *tetrimino = parse_input(buffer);
//   for (int i = 0; i < (ft_strlen(buffer) + 1) / 21; i++)
//   {
//       print_tetrimino(tetrimino[i]);
//       ft_putchar('\n');
//   }
   return (0);
}
