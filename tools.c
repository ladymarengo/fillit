#include "fillit.h"

/* solution storage */
void	save_solution(t_matrix matrix, t_solution *solution)
{
	solution = (t_solution *)malloc(sizeof (t_solution));

	solution->matrix = matrix;
}

/* find best solution */

int find_best(t_tetr_array *tetriminos, int size, t_solution *solution)
{
	t_matrix *new;
	t_point start;
	int result = 0;
	int i = 0;

	
	
	start.row = 0;
	start.column = 0;
	//while (i < tetriminos->size)
	while (i < 1)
	{
		new = create_matrix(size * 2);
		result = place_tetro(start, new, tetriminos->array[i]);
		if (result == 1)
		{
			//print_matrix(*new);
			int *placed = create_placed(tetriminos->size);
			placed = update_placed(placed, i, tetriminos->size);
			result = put_tetrimino(tetriminos, new, size, placed, solution);
			if (result == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int put_tetrimino(t_tetr_array *tetriminos, t_matrix *matrix, int size, int *placed, t_solution *solution)
{
	int i = 0;
	int result;
	int if_solution;
	t_point next;
	t_matrix *new;
	int *new_placed;


	while (i < tetriminos->size) 
	{
		result = 0;
		next.row = 0;
		next.column = 0;
		if (!if_placed(i, placed, tetriminos->size))
		{
			new = copy_matrix(matrix);
			while (!result)
			{
				//ft_putnbr(i);
				//ft_putendl("here");
				result = place_tetro(next, new, tetriminos->array[i]);
				next = get_next_coordinate(*new, next.row, next.column);
			}
			new_placed = update_placed(placed, i, tetriminos->size);
			//ft_putnbr(calculate_size(*new));
			//ft_putendl("size");
			ft_putnbr(size);
			ft_putendl("");
			print_matrix(*new);
			if (calculate_size(*new) <= size)
			{
				if (all_placed(new_placed, tetriminos->size) == 1)
				{
					save_solution(*new, solution);
					return (1);
				}
				if_solution = put_tetrimino(tetriminos, new, size, new_placed, solution);
				free(new);
				free(new_placed);
				if (if_solution == 1)
				{
					return (1);
				}
			}

			result = 0;
			new = copy_matrix(matrix);
			next = get_next_coordinate(*new, next.row, next.column);
			while (!result)
			{
				//ft_putnbr(i);
				//ft_putendl("here");
				result = place_tetro(next, new, tetriminos->array[i]);
				next = get_next_coordinate(*new, next.row, next.column);
			}
			new_placed = update_placed(placed, i, tetriminos->size);
			//ft_putnbr(calculate_size(*new));
			//ft_putendl("size");
			ft_putnbr(size);
			ft_putendl("");
			print_matrix(*new);
			if (calculate_size(*new) <= size)
			{
				if (all_placed(new_placed, tetriminos->size) == 1)
				{
					save_solution(*new, solution);
					return (1);
				}
				if_solution = put_tetrimino(tetriminos, new, size, new_placed, solution);
				free(new);
				free(new_placed);
				if (if_solution == 1)
				{
					return (1);
				}
			}


		}
		if (size == 6)
			sleep(1);
		i++;
	}
	return (0);
}

int	if_placed(int index, int *placed, int size)
{
	int i = 0;

	while (i < size)
	{
		if (placed[i] == index)
			return (1);
		i++;
	}
	return (0);
}

int *create_placed(int size)
{
	int i = 0;
	int *placed = (int *)malloc(sizeof(int) * (size + 1));
	while (i < size + 1)
	{
		placed[i] = -1;
		i++;
	}
	return (placed);
}

int *update_placed(int *placed, int index, int size)
{
	int i = 0;
	int *new = (int *)malloc(sizeof(int) * (size + 1));
	while (placed[i] != -1)
	{
		new[i] = placed[i];
		i++;
	}
	new[i] = index;
	i++;
	while (i < size + 1)
	{
		new[i] = placed[i];
		i++;
	}
	return (new);
}

int	all_placed(int *placed, int size)
{
	int i = 0;
	while (placed[i] != -1)
		i++;
	if (i == size)
		return (1);
	return (0);
}

//4*3*2*1

t_matrix *copy_matrix(t_matrix *old)
{
    t_matrix *new;

    int i = 0;
    int j = 0;

	new = (t_matrix *)malloc(sizeof(t_matrix));
    new->grid = (char **)malloc(sizeof(char *) * old->size);
	new->size = old->size;
    while (i < new->size)
    {
        j = 0;
		new->grid[i] = (char *)malloc(sizeof(char) * new->size);
        while (j < new->size)
        {
            new->grid[i][j] = old->grid[i][j];
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
