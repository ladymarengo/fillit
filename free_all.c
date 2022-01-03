#include "fillit.h"


void	free_matrix(t_matrix *matrix)
{
	int i = 0;

    while (i < matrix->size)
    {
        free(matrix->grid[i]);
        i++;
    }
	free(matrix->grid);
	free(matrix);
}

void	free_tetriminos(t_tetr *tetriminos, char *buffer, int i, int row)
{
	while (i >= 0)
	{
		while (row >= 0)
		{
			free(tetriminos[i].grid[row]);
			row--;
		}
		free(tetriminos[i].grid);
		i--;
		row = 3;
	}
	free(tetriminos);
	if (buffer)
		free(buffer);
	exit(-1);
}

void	end_game(t_tetr_array *tetriminos, t_matrix *matrix)
{
	print_matrix(*matrix);
	free_matrix(matrix);
	free_tetriminos(tetriminos->array, NULL, tetriminos->size - 1, 3);
	exit(0);
}