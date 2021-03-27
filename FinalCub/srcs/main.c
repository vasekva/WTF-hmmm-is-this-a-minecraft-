#include "cub3d.h"

int	ft_check_fileformat(char *argument)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (argument[i])
	{
		if (argument[i] == '.')
			pos = i;
		i++;
	}
	if (!ft_strncmp(&argument[pos], ".cub", ft_strlen(&argument[pos])))
		return (-1);
	return (0);
}

static int	create_window(t_cub3d *cub3d)
{
	cub3d->mlx->p_mlx = mlx_init();
	if (!cub3d->mlx->p_mlx)
		return (0);
	ft_read_textures(cub3d);
	cub3d->mlx->image
		= mlx_new_image(cub3d->mlx->p_mlx, cub3d->scr_w, cub3d->scr_h);
	if (!cub3d->mlx->image)
		return (0);
	cub3d->mlx->p_img
		= mlx_get_data_addr(cub3d->mlx->image, &cub3d->mlx->bits_per_pixel,
			&cub3d->mlx->line_length, &cub3d->mlx->endian);
	if (cub3d->screenshot)
	{
		write(1, "Creating a screenshot. Wait...\n", 32);
		ft_convert_bmp(cub3d);
		write(1, "Done!\n", 7);
		exit(0);
	}
	cub3d->mlx->p_win
		= mlx_new_window(cub3d->mlx->p_mlx, cub3d->scr_w,
			cub3d->scr_h, "cub3d");
	if (!cub3d->mlx->p_win)
		return (0);
	return (1);
}

void	ft_has_screen(t_cub3d *cub3d, char *arg, int argc, int flag)
{
	if (argc == 3)
	{
		flag = ft_strncmp(arg, "--save", ft_strlen(arg));
		if (flag == 1 || flag == -1)
			exception(THIRTYSIX);
		cub3d->screenshot = 1;
	}
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int		flag;

	flag = 0;
	if (argc > 1)
	{
		cub3d.file_path = ft_strdup(argv[1]);
		if (!cub3d.file_path)
			exception(THIRTYTWO);
		ft_init_cub3d(&cub3d);
		ft_has_screen(&cub3d, argv[2], argc, flag);
		flag = create_window(&cub3d);
		if (!flag)
			exception(TWELVE);
		mlx_hook(cub3d.mlx->p_win, 2, (1L << 0), key_press, &cub3d);
		mlx_hook(cub3d.mlx->p_win, 3, (1L << 1), key_release, &cub3d);
		mlx_loop_hook(cub3d.mlx->p_mlx, ft_start_game, &cub3d);
		mlx_loop(cub3d.mlx->p_mlx);
	}
	else
		ft_putstr("Вы не передали аргументы в программу!\n");
	return (0);
}
