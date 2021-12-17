#ifndef FILLIT_H
# define FILLIT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include <string.h>
#include <sys/stat.h>
#include <stdio.h> //REMEMBER TO DELETE, JUST FOR TESTPRINTS

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
    int top_left;
    int top_right;
    int bottom_left;
	int size;
} t_solution;

typedef struct s_tetr
{
	char	**grid;
	char	symbol;
}	t_tetr;


t_point		get_next_coordinate(t_matrix matrix, int lastrow, int lastcolumn);
void		print_tetrimino(t_tetr tetr);
void		print_matrix(t_matrix matrix);
t_matrix	create_matrix(int size);
void		solve();
t_tetr		*parse_input(char *buffer);
int			copy_tetr(char *buffer, int index, t_tetr *tetr, int i);
t_point		find_tetropoint(t_tetr tetro);
int			ft_linesandchar(char *s);
int			place_tetro(t_point start, t_matrix *matrix, t_tetr tetro);
t_solution	*save_solution(t_matrix matrix, t_solution *prevsolution);
void		calculate_corners(t_matrix matrix, t_solution *solution);

#endif