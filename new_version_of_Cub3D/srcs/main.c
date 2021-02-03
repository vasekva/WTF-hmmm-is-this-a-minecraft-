#include "cub3D.h"

static int			check_line_for_map(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] == '1')
			{
				return (1);
			}
			else
			{
				printf("ERROR"); //TODO вывод ошибок
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static void			read_and_copy_in_array(int fd, t_cub3D *cub3D)
{
	char	*line;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while((i = get_next_line(fd, &line)) >= 0)
    {
		if (line[0] == ' ')
		{
			if (check_line_for_map(line) == 1)
			{
				// printf("%s\n", line);
				cub3D->array[count] = (char *)malloc(ft_strlen(line) + 1);
				ft_strcpy(cub3D->array[count], line);
				count++;
			}
		}
		if (line[0] == '1')
		{	
			cub3D->array[count] = (char *)malloc(ft_strlen(line) + 1);
			ft_strcpy(cub3D->array[count], line);
			count++;
		}
		if (i == 0)
			break;
    }
}

static void			init_array(t_cub3D *cub3D)
{
	int 	fd;
	int 	x = cub3D->parser->max_strlen_of_map;
	int		y = cub3D->parser->count_of_map_lines;

	cub3D->array = (char **)malloc(y + 1);
	cub3D->array[y] = NULL;
	fd = open(cub3D->file_path, O_RDONLY);
	read_and_copy_in_array(fd, cub3D);
}

static void    		init_cub3D(t_cub3D *cub3D, char *path)
{
	cub3D->file_path = path;
    cub3D->screen = init_screen(NULL);
    cub3D->map = init_map(NULL);
    cub3D->floor = init_floor(NULL);
    cub3D->ceiling = init_ceiling(NULL);
    cub3D->parser = init_parser(NULL);
}

int     			main(int argc, char **argv)
{
    t_cub3D cub3D;

    if (argc)
    {
        if (argc == 2)
        {
            init_cub3D(&cub3D, argv[1]);
            ft_parse(&cub3D); //TODO проверка наличия файла, откуда идет чтение
			init_array(&cub3D);
        }
    }
	ft_print_structs(&cub3D);
    return (0);
}