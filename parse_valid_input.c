#include "libft/libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_tetr
{
	char	**grid;
}	t_tetr;

int	copy_tetr(char *buffer, int index, t_tetr *tetr)
{
	int	row;
	int	letter;

	row = 0;
	tetr->grid = (char **)malloc(sizeof(char *) * 4);
	while (row < 4)
	{
		tetr->grid[row] = (char *)malloc(sizeof(char) * 5);
		letter = 0;
		while (letter < 4)
		{
			tetr->grid[row][letter] = buffer[index];
			index++;
			letter++;
		}
		index++;
		row++;
	}
	return (index);
}

t_tetr	*parse_input(char *buffer)
{
	t_tetr	*tetriminos;
	int		i;
	int		index;
	int		amount;

	i = 0;
	index = 0;
	amount = (ft_strlen(buffer) + 1) / 21;
	tetriminos = (t_tetr *)malloc(sizeof(t_tetr) * amount);
	while (i < amount)
	{
		index = copy_tetr(buffer, index, &(tetriminos[i]));
		index++;
		i++;
	}
	return (tetriminos);
}

/*void    print_tetrimino(t_tetr tetr) 
{
    int i = 0;
    int j = 0;

    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            ft_putchar(tetr.grid[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

int main(int argc, char **argv)
{
    int		chars;
    int file;
    char	*buffer = (char *)malloc(sizeof(char) * 1000);
    file = open(argv[1], O_RDONLY);
    chars = read(file, buffer, 1000);
    buffer[chars] = '\0';
    close(file);
    t_tetr *tetrimino = parse_input(buffer);
    for (int i = 0; i < (ft_strlen(buffer) + 1) / 21; i++)
    {
        print_tetrimino(tetrimino[i]);
        ft_putchar('\n');
    }
    return (0);
}*/