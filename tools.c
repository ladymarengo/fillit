#include "fillit.h"

/* solution storage */
t_solution	*save_solution(t_matrix matrix, t_solution *prevsolution)
{
	t_solution *new;
	int	i;
	int j;
	int countheight;
	int countwidth;

	j = matrix.size - 1;
	new = (t_solution *)malloc(sizeof (t_solution));
	new->height = 0;
	new->width = 0;
	while (j >= 0)
	{
		i = matrix.size - 1;
		countwidth = matrix.size;
		while (i >= 0 && matrix.grid[j][i] == '.')
		{
			i--;
			countwidth--;
		}
		if (countwidth > new->width)
			new->width = countwidth;
		j--;
	}
	i = matrix.size - 1;
	while (i >= 0)
	{
		j = matrix.size - 1;
		countheight = matrix.size;
		while (j >= 0 && matrix.grid[j][i] == '.')
		{
			j--;
			countheight--;
		}
		if (countheight > new->height)
			new->height = countheight;
		i--;
	}
	calculate_corners(matrix, new);
	if (new->height > new->width)
		new->size = new->height;
	else
		new->size = new->width;
	if (!prevsolution || new->size < prevsolution->size)
		return (new);
	return (prevsolution);
}

/*calculating most topleft */
void	calculate_corners(t_matrix matrix, t_solution *solution)
{
	int i;

	i = 0;
	while (i < matrix.size && matrix.grid[0][i] == '.')
	{
		i++;
	}
	solution->top_left = i;
	i = 0;
	while (i < matrix.size && matrix.grid[i][0] == '.')
	{
		i++;
	}
	solution->bottom_left = i;
	i = matrix.size - 1;
	while (i >= 0 && matrix.grid[0][i] == '.')
	{
		i--;
	}
	solution->top_right = i;
}

/* geeting next valid coordinates */
t_point	get_next_coordinate(t_matrix matrix, int lastrow, int lastcolumn)
{
	int i = lastrow + lastcolumn;
	int row = lastrow + 1;
	int column = lastcolumn - 1;
	t_point point;


	while (i < matrix.size * 2 - 1)
	{
		while (column >= 0)
		{
			if (row < matrix.size && column < matrix.size && matrix.grid[row][column] == '.')
			{
				point.row = row;
				point.column = column;
//				printf("%d,%d\n", row, column);
				return (point);
			}
//			printf("%d,%d\n", row, column);
			row++;
			column--;
		}
		i++;
		column = i;
		row = 0;
	}
	return (point);
}

/* to place tetro in matrix */
int	place_tetro(t_point start, t_matrix *matrix, t_tetr tetro)
{
	//iterate thru tetro && find starting point (topleft)
	//check if place on the grid is empty
	//(check for neighbours)
	// if good, place it on grid
	int i;
	int j;
	t_point tetropoint;
	t_point possible;

	tetropoint = find_tetropoint(tetro);
	i = tetropoint.column;
	j = tetropoint.row;
	// printf("tetro start: %d, %d\n", tetropoint.row, tetropoint.column);
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				possible.row = start.row + j - tetropoint.row;
				possible.column = start.column + i - tetropoint.column;
				// printf("%d, %d\n %d, %d\n\n", j, i , possible.row, possible.column);
				if (possible.row < 0 || possible.row >= matrix->size || possible.column < 0 || possible.column >= matrix->size || matrix->grid[possible.row][possible.column] != '.')
					return (0);
			}
			i++;
		}
		i = 0;
		j++;
	}
	i = tetropoint.column;
	j = tetropoint.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				possible.row = start.row + j - tetropoint.row;
				possible.column = start.column + i - tetropoint.column;
				matrix->grid[possible.row][possible.column] = tetro.symbol;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

t_point find_tetropoint(t_tetr tetro)
{
	int i;
	int j;
	t_point tetropoint;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				tetropoint.row = j;
				tetropoint.column = i;
				return (tetropoint);
			}
			i++;
		}
		j++;
	}
	return (tetropoint);
}
