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

typedef struct s_action
{
	t_point point;
	int index;
	int *placed;
} t_action;

typedef struct s_matrix
{
    char **grid;
    int	size;
} t_matrix;

typedef struct s_solution
{
    t_matrix matrix;
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

typedef struct s_tetr_array
{
	t_tetr	*array;
	int		size;
} t_tetr_array;

t_point		get_next_coordinate(t_matrix matrix, int lastrow, int lastcolumn);
void		print_tetrimino(t_tetr tetr);
void		print_matrix(t_matrix matrix);
t_matrix	*create_matrix(int size);
void		solve(t_tetr *tetros);
t_tetr_array	parse_input(char *buffer);
t_matrix	*copy_matrix(t_matrix *old);
int			copy_tetr(char *buffer, int index, t_tetr *tetr, int i);
t_point		find_tetropoint(t_tetr tetro);
int			ft_linesandchar(char *s);
// int			calculate_size(t_matrix matrix);
int			place_tetro(t_point start, t_matrix *matrix, t_tetr tetro);
// void		save_solution(t_matrix matrix, t_solution *solution);
// void		calculate_corners(t_matrix matrix, t_solution *solution);
int			find_best(t_tetr_array *tetriminos, int size);
int			put_tetrimino(t_tetr_array *tetriminos, t_matrix *matrix, int size, int index);
// int			*update_placed(int *placed, int index, int size);
// int			*create_placed(int size);
// int			if_placed(int index, int *placed, int size);
// int			all_placed(int *placed, int size);
int			remove_tetro(t_point start, t_matrix *matrix, t_tetr tetro);

#endif