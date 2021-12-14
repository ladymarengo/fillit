#include <stdio.h>
#include <fcntl.h>

int check_input(char *input)
{
	int x = 0;
	int count = 0;
	int tetraminos = 0;
	int connection = 0;

	while (x < 21 || input[x] == '\0')
	{
		if (input[x] != '#' && input[x] != '.' && input[x] != '\n')
		{
			printf ("%s\n", input);
			return -3;
		}
		if (input[x] == '#')
		{
			count++;
			if (input[x + 1] == '#')
				connection++;
			if (input[x + 5] == '#')
				connection++;
			if (input[x - 1] == '#')
				connection++;
			if (input[x - 5] == '#')
				connection++;
		}
		if (count > 4)
			return -2;
		if (input[x] == '\n' && input[x + 1] == '\n' && count == 4)
		{
			tetraminos++;
			count = 0;
		}
		x++;
	}
	if ((connection == 6 || connection == 8) && (x == 21))
		return 1;
	return -1;
}

int main ()
{
	char *input = "...#\n...#\n...#\n...#\n\n##..\n.##.\n....\n....\n\n....\n....\n##..\n##..\n\n###.\n..#.\n....\n....\n\n#...\n#...\n##..\n....\n";
	printf("%d\n", check_input(input));
//	printf("%d\n", check_input(fd));
	return 0;
}

// -2 if too many #
// -1 if block not connected
// -3 if wrong input char