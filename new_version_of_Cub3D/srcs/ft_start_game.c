#include "cub3D.h"
#include "mlx.h"

static void            my_mlx_pixel_put(t_mlx *mlx_img, int x, int y, int color)
{
    char    *dst;

    dst = mlx_img->addr + (y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		draw_cub_in_pixel(int y, int x, t_cub3D *cub3D)
{
	int posX = x * SIZE_OF_CUB;
	int posY = y * SIZE_OF_CUB;

	int posXFinal = posX + SIZE_OF_CUB;
	int posYFinal = posY + SIZE_OF_CUB;
	while (posY < posYFinal - 1)
	{
		while (posX < posXFinal - 1)
		{
			if (cub3D->array[y][x] == '1')
				my_mlx_pixel_put(cub3D->mlx_img, posX, posY, color_of_wall_minimap);
			else
				my_mlx_pixel_put(cub3D->mlx_img, posX, posY, color_of_field_minimap);
			posX++;
		}
		posX = x * SIZE_OF_CUB;
		posY++;
	}
}

void		ft_draw_cub_from_cubs(t_cub3D *cub3D)
{
	int x;
	int y;

	x = 0;
	y = 0;

	int count_of_block_in_array_y = cub3D->parser->count_of_map_lines;
	int	count_of_block_in_array_x = cub3D->parser->max_strlen_of_map;
	while (y < count_of_block_in_array_y)
	{
		while (x < count_of_block_in_array_x)
		{
			draw_cub_in_pixel(y, x, cub3D);
			x++;
		}
		x = 0;
		y++;
	}
}

// void					ft_draw_ray(t_cub3D *cub3D)
// {
// 	int Xa = SIZE_OF_CUB / tan(cub3D->player->degree);

// 	int userCenterPosX = posX - SIZE_OF_PLAYER / 2;
// 	int	userCenterPosY = posY + SIZE_OF_PLAYER / 2;

// 	for (int i = 0; i < 5; i++)
// 	{
// 		int Xend = userCenterPosX + cub3D->player->posDirX * 20;
// 		int Yend = userCenterPosY + cub3D->player->posDirY * 20;
// 		print_DDALine(userCenterPosX, userCenterPosY, Xend, Yend, cub3D);
// 	}
// }

void					ft_draw_user(t_cub3D *cub3D)
{
	int	posX = cub3D->player->posX - SIZE_OF_PLAYER / 2;
	int posY = cub3D->player->posY - SIZE_OF_PLAYER / 2;

	for (int x = 0; x < SIZE_OF_PLAYER; x++)
	{
		for (int y = 0; y < SIZE_OF_PLAYER; y++)
		{
			my_mlx_pixel_put(cub3D->mlx_img, posX, posY, 0x00FFFF00);
			posY++;
		}
		posY = cub3D->player->posY - SIZE_OF_PLAYER / 2;
		posX++;
	}
	int userCenterPosX = posX - SIZE_OF_PLAYER / 2;
	int	userCenterPosY = posY + SIZE_OF_PLAYER / 2;


	// int Xa = SIZE_OF_CUB / tan(cub3D->player->degree);
	// printf("XA %d\n", Xa);
	int Xend = userCenterPosX + cub3D->player->posDirX * 20;
	int Yend = userCenterPosY + cub3D->player->posDirY * 20;
	// for (int i = 0; i < 2; i++)
	// {
	// 	Xend += Xa;
	// 	Yend += SIZE_OF_CUB;
	// }
	print_DDALine(userCenterPosX, userCenterPosY, Xend, Yend, cub3D, 0x00FF0000);
	ft_draw_rays(cub3D);
	//print_DDALine(userCenterPosX, userCenterPosY, userCenterPosX + cub3D->player->posDirX * 20, userCenterPosY + cub3D->player->posDirY * 20, cub3D);
}

void					ft_fill_background(t_cub3D *cub3D)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < cub3D->screen->w)
	{
		while (y < cub3D->screen->h)
		{
			my_mlx_pixel_put(cub3D->mlx_img, x, y, 0x00696969);
			y++;
		}
		y = 0;
		x++;
	}
}

void					ft_start_game(t_cub3D *cub3D)
{
	//ft_print_structs(cub3D);

	cub3D->env->img = mlx_new_image(cub3D->env->mlx, cub3D->screen->w, cub3D->screen->h);
	cub3D->mlx_img->addr = mlx_get_data_addr(cub3D->env->img, &cub3D->mlx_img->bits_per_pixel, &cub3D->mlx_img->line_length,
                                &cub3D->mlx_img->endian);
	ft_fill_background(cub3D);

	ft_draw_cub_from_cubs(cub3D);	//рисует карту и массив в консоль		
	ft_draw_user(cub3D);

	mlx_put_image_to_window(cub3D->env->mlx, cub3D->env->win, cub3D->env->img, 0, 0);
 
	//Degree
	mlx_string_put(cub3D->env->mlx, cub3D->env->win, cub3D->player->posX - (SIZE_OF_PLAYER / 2 - 5), cub3D->player->posY + (SIZE_OF_PLAYER / 2 + 10), 0x00FF0000, ft_itoa(cub3D->player->degree));
	//X
	mlx_string_put(cub3D->env->mlx, cub3D->env->win, cub3D->player->posX + (SIZE_OF_PLAYER / 2 + 5), cub3D->player->posY + (SIZE_OF_PLAYER / 2 + 10), 0x00FF0000, ft_itoa(cub3D->player->posX));
	//Y
	mlx_string_put(cub3D->env->mlx, cub3D->env->win, cub3D->player->posX + (SIZE_OF_PLAYER / 2 + 35), cub3D->player->posY + (SIZE_OF_PLAYER / 2 + 10), 0x00FF0000, ft_itoa(cub3D->player->posY));
}