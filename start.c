#include "libft/libft.h"

typedef struct s_matrix
{
    char **grid;
    int height;
    int width;
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

    while (i < matrix.height)
    {
        j = 0;
        while (j < matrix.width)
        {
            ft_putchar(matrix.grid[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

t_matrix create_matrix(int x, int y)
{
    t_matrix matrix;

    int i = 0;
    int j = 0;

    matrix.height = y;
    matrix.width = x;
    matrix.grid = (char **)malloc(sizeof(char *) * y);
    while (i < y)
    {
        j = 0;
        matrix.grid[i] = (char *)malloc(sizeof(char) * x);
        while (j < x)
        {
            matrix.grid[i][j] = '.';
            j++;
        }
        i++;
    }
    return (matrix);
}

void solve(int tetr[2][4][4])
{
    t_matrix matrix = create_matrix(8, 8);
    print_matrix(matrix);
    t_solution solution;
    int i = 0;
    int j = 0;

    while (i < y)
    {
        j = 0;
        while (j < x)
        {
            find_solution(tetr);
            j++;
        }
        i++;
    }
}

int main()
{
    int ***tetrimino[2][4][4] = {{{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}}};

    for (int i = 0; i < 2; i++)
    {
        print_tetrimino(tetrimino[i]);
        ft_putchar('\n');
    }
    solve(tetrimino);
    return (0);
}