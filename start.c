#include "fillit.h"

void print_matrix(t_matrix matrix) 
{
    int i = 0;
    int j = 0;

	if (!matrix.grid)
	{
		return ;
	}
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

t_matrix *create_matrix(int size)
{
    t_matrix *matrix;

    int i = 0;
    int j = 0;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));

    matrix->size = size;
    matrix->grid = (char **)malloc(sizeof(char *) * size);
    while (i < size)
    {
        j = 0;
        matrix->grid[i] = (char *)malloc(sizeof(char) * size);
        while (j < size)
        {
            matrix->grid[i][j] = '.';
            j++;
        }
        i++;
    }
    return (matrix);
}

int main(int argc, char **argv)
{
    int		chars;
    int 	file;
    char	*buffer;
	int		size;

	if (argc != 2)
	{
		ft_putendl("usage: the number of parameters should be one");
		return (-1);
	}
	buffer = (char *)malloc(sizeof(char) * 1000);
    file = open(argv[1], O_RDONLY);
    chars = read(file, buffer, 1000);
	if (chars > 900 || chars < 1)
	{
		free(buffer);
		return (-1);
	}
    buffer[chars] = '\0';
    close(file);
    t_tetr_array tetrimino = parse_input(buffer);
	size = 3;
	while (find_best(&tetrimino, size) == 0)
		size++;
    return (0);
}
