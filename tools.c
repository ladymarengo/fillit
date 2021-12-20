#include "fillit.h"

/* solution storage */
t_solution	*save_solution(t_matrix matrix, t_solution *prevsolution)
{
	t_solution *new;
	new = (t_solution *)malloc(sizeof (t_solution));

	new->size = calculate_size(matrix);
	calculate_corners(matrix, new);
	
	if (!prevsolution || new->size < prevsolution->size)
	{
		return (new);
	}
	return (prevsolution);
}

/* find best solution */

void find_best(t_tetr_array *tetriminos, int size, t_solution *prev)
{
	t_matrix new;
	t_action action;
	int i;

	action.point.row = 0;
	action.point.column = 0;
	action.index = 0;
	action.placed = (int *)malloc(sizeof(int) * tetriminos.size);
	new = create_matrix(size);
	put_tetrimino(tetriminos, new, action, prev);
}

void put_tetrimino(t_tetr_array *tetriminos, t_matrix matrix, t_action action, t_solution *prev)
{
	t_matrix new;
	t_point next;
	t_action next_action;
	int i;

	new = copy_matrix(matrix);
	printf("%d %d\n", action.index, tetriminos->size);
	
	
	while (!place_tetro(action.point, &new, tetriminos->array[action.index]))
	{
		action.point = get_next_coordinate(new, action.point.row, action.point.column);
	}
	if (action.index + 1 >= tetriminos->size)
	{
		printf("saving\n");
		prev = save_solution(new, prev);
	}
	else 
	{
		next_action.point = get_next_coordinate(new, 0, 0);
		i = action.index + 1;
		while (i < tetriminos->size)
		{
			next_action.index = i;
			put_tetrimino(tetriminos, new, next_action, prev);
			i++;
		}
	}
}

//4*3*2*1

t_matrix copy_matrix(t_matrix old)
{
    t_matrix new;

    int i = 0;
    int j = 0;

    new.grid = (char **)malloc(sizeof(char *) * old.size);
	new.size = old.size;
    while (i < new.size)
    {
        j = 0;
		new.grid[i] = (char *)malloc(sizeof(char) * new.size);
        while (j < new.size)
        {
            new.grid[i][j] = old.grid[i][j];
            j++;
        }
        i++;
    }
    return (new);
}

/*calculate size of solution*/
int	calculate_size(t_matrix matrix)
{
	int	i;
	int j;
	int size;
	int countheight;
	int countwidth;

	size = 0;
	j = matrix.size - 1;
	while (j >= 0)
	{
		i = matrix.size - 1;
		countwidth = matrix.size;
		while (i >= 0 && matrix.grid[j][i] == '.')
		{
			i--;
			countwidth--;
		}
		if (countwidth > size)
			size = countwidth;
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
		if (countheight > size)
			size = countheight;
		i--;
	}
	return (size);
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
