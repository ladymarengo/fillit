#include "libft/libft.h"
#include <stdio.h>

typedef struct s_point
{
	int	row;
	int	column;
} t_point;

typedef struct s_matrix
{
    char **grid;
    int	size;
} t_matrix;

typedef struct s_solution
{
    t_matrix matrix;
    int height;
    int width;
    int top_left[2];
    int top_right[2];
    int bottom_left[2];
} t_solution;

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


void print_tetrimino(int tetr[4][4]) 
{
    int i = 0;
    int j = 0;

    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            if (tetr[i][j] == 1) {
                ft_putchar('#');
            }
            else
            {
                ft_putchar('.');
            }
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

void print_matrix(t_matrix matrix) 
{
    int i = 0;
    int j = 0;

    while (i < matrix.size)
    {
        j = 0;
        while (j < matrix.size)
        {
            ft_putchar(matrix.grid[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

t_matrix create_matrix(int size)
{
    t_matrix matrix;

    int i = 0;
    int j = 0;

    matrix.size = size;
    matrix.grid = (char **)malloc(sizeof(char *) * size);
    while (i < size)
    {
        j = 0;
        matrix.grid[i] = (char *)malloc(sizeof(char) * size);
        while (j < size)
        {
            matrix.grid[i][j] = '#';
            j++;
        }
        i++;
    }
    return (matrix);
}

void solve()
{
    t_matrix matrix = create_matrix(8);
	print_matrix(matrix);
	get_next_coordinate(matrix, 0, 0);
//    t_solution solution;
//    int i = 0;
//    int j = 0;
//
//    while (i < y)
//    {
//        j = 0;
//        while (j < x)
//        {
//            find_solution(tetr);
//            j++;
//        }
//        i++;
//   }
}

int main()
{
    // int ***tetrimino[2][4][4] = {{{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
    // {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}}};

    // for (int i = 0; i < 2; i++)
    // {
    //     print_tetrimino(tetrimino[i]);
    //     ft_putchar('\n');
    // }
    solve();
    return (0);
}