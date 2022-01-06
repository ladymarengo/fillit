/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:56:33 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/06 13:49:44 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <string.h>
# include <sys/stat.h>

typedef struct s_point
{
	int	row;
	int	column;
}	t_point;

typedef struct s_matrix
{
	char	**grid;
	int		size;
}	t_matrix;

typedef struct s_tetr
{
	char	**grid;
	char	symbol;
}	t_tetr;

typedef struct s_tetr_array
{
	t_tetr	*array;
	int		size;
}	t_tetr_array;

t_tetr_array	parse_input(char *buffer);
t_point			find_tetropoint(t_tetr tetro);
int				ft_linesandchar(char *s, int i, int count, int lines);
int				place_tetro(t_point start, t_matrix *m, t_tetr t, t_point p);
int				find_best(t_tetr_array *tetriminos, int size);
int				remove_tetro(t_point start, t_matrix *matrix, t_tetr tetro);
int				check_tetro(t_point start, t_matrix *m, t_tetr t, t_point p);
void			free_matrix(t_matrix *matrix);
void			free_tetriminos(t_tetr *tetros, char *buffer, int i, int row);
void			end_game(t_tetr_array *tetriminos, t_matrix *matrix);
void			check_input(char *buffer);

#endif