#include "fillit.h"

void print_matrix(t_matrix matrix) 
{
    int i = 0;
    int j = 0;

	if (!matrix.grid)
	{
		printf("oh no\n");
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
            matrix.grid[i][j] = '.';
            j++;
        }
        i++;
    }
    return (matrix);
}

void solve(t_tetr *tetros)
{
	int i;
	int res;

	i = 0;
	t_point start;
	t_solution *solution;
    t_matrix matrix = create_matrix(8);
	get_next_coordinate(matrix, 0, 0);
	while (i < 4)
	{
		res = 0;
		start.row = 0;
		start.column = 0;
		while (res == 0)
		{
			res = place_tetro(start, &matrix, tetros[i]);
			start = get_next_coordinate(matrix, start.row, start.column);
		}
		i++;
	}
	print_matrix(matrix);
	solution = NULL;
	solution = save_solution(matrix, solution);
	printf("%d\n", solution->size);
//	printf("TL: %d,BL: %d \n", solution->top_left, solution->bottom_left, solution->top_right);

	// printf("%d\n", place_tetro(start, &matrix, tetros[0]));
	// printf("%d\n", place_tetro(start, &matrix, tetros[1]));
	// printf("%d\n", place_tetro(start, &matrix, tetros[2]));
	// printf("%d\n", place_tetro(start, &matrix, tetros[3]));
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

int main(int argc, char **argv)
{
    int		chars;
    int 	file;
    char	*buffer = (char *)malloc(sizeof(char) * 1000);
    file = open(argv[1], O_RDONLY);
    chars = read(file, buffer, 1000);
    buffer[chars] = '\0';
    close(file);
    t_tetr_array tetrimino = parse_input(buffer);
    for (int i = 0; i < (ft_strlen(buffer) + 1) / 21; i++)
    {
        print_tetrimino(tetrimino.array[i]);
        ft_putchar('\n');
    }
	//solve(tetrimino);
	t_solution *solution;
	solution = NULL;
	find_best(&tetrimino, 16, solution);
	print_matrix(solution->matrix);
    return (0);
}