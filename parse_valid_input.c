#include "fillit.h"


int	copy_tetr(char *buffer, int index, t_tetr *tetriminos, int i)
{
	int	row;
	int	letter;

	row = 0;
	tetriminos[i].grid = (char **)malloc(sizeof(char *) * 4);
	if (!tetriminos[i].grid)
		free_tetriminos(tetriminos, buffer, i - 1, 3);
	while (row < 4)
	{
		tetriminos[i].grid[row] = (char *)malloc(sizeof(char) * 5);
		if (!tetriminos[i].grid[row])
			free_tetriminos(tetriminos, buffer, i, row - 1);
		letter = 0;
		while (letter < 4)
		{
			tetriminos[i].grid[row][letter] = buffer[index];
			index++;
			letter++;
		}
		index++;
		row++;
	}
	tetriminos[i].symbol = 'A' + i;
	return (index);
}

t_tetr_array	parse_input(char *buffer)
{
	t_tetr	*tetriminos;
	t_tetr_array array;
	int		i;
	int		index;
	int		amount;

	i = 0;
	index = 0;
	amount = (ft_strlen(buffer) + 1) / 21;
	tetriminos = (t_tetr *)malloc(sizeof(t_tetr) * amount + 1);
	if (!tetriminos)
	{
		free(buffer);
		exit(-1);
	}
	while (i < amount)
	{
		index = copy_tetr(buffer, index, tetriminos, i);
		index++;
		i++;
	}
	array.array = tetriminos;
	array.size = amount;
	free(buffer);
	return (array);
}

void    print_tetrimino(t_tetr tetr) 
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
