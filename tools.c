#include <stdio.h>
#include <string.h>
#include "start.c"

/* solution storage */


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
				printf("%d,%d\n", row, column);
				return (point);
			}
			printf("%d,%d\n", row, column);
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
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro[j][i] == '#')
			{
				possible.row = start.row + j - tetropoint.row;
				possible.column = start.column + i - tetropoint.column;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

t_point find_tetropoint(t_tetr tetro)
[
	int i;
	int j;
	t_point tetropoint;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (tetro[j][i] == '#')
			{
				tetropoint.row = j;
				tetropoint.column = i;
			}
			i++;
		}
		j++;
	}
	return (tetropoint);
}
