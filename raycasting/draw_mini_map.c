/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:37 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/12 22:36:52 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_data_mlx(t_map *map)
{
	t_data	*data;

	data = map->data;
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error("error mlx_init");
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"./cub3d");
	if (!data->win)
		print_error("Window can't open try again");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		print_error("error to create image");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		print_error("error to get the memory address for the pixel data");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	frame_color(t_map *map, t_coord pos, int tmp_y, int tmp_x)
{
	t_data	*data;

	data = map->data;
	if (map->map[tmp_y][tmp_x] == EMPTY
		|| map->map[tmp_y][tmp_x] == map->player_pos.player_symbol)
		my_mlx_pixel_put(data, pos.x, pos.y, FLOOR_COLOR);
	else if (map->map[tmp_y][tmp_x] == WALL)
		my_mlx_pixel_put(data, pos.x, pos.y, WALL_COLOR);
	if ((pos.y == 100 && pos.x == 100) || (pos.y == 100 && pos.x == 101))
		my_mlx_pixel_put(data, pos.x, pos.y, PLAYER_COLOR);
}

void	draw_mini_map(t_map *map, t_data *data)
{
	int		y;
	int		x;
	int		tmp_x;
	int		tmp_y;
	t_coord	coord;

	y = -1;
	while (y++ < MINIMAP_HEIGHT)
	{
		x = -1;
		while (x++ < MINIMAP_WIDTH)
		{
			tmp_x = ((map->player_pos.x - MINIMAP_WIDTH / 2) + x) / FRAME_WIDTH;
			tmp_y = ((map->player_pos.y - MINIMAP_HEIGHT / 2) + y)
				/ FRAME_HEIGHT;
			my_mlx_pixel_put(data, x, y, SPACE_COLOR);
			coord.x = x;
			coord.y = y;
			if (tmp_x >= 0 && tmp_y >= 0 && tmp_x < map->max_width
				&& tmp_y < map->map_height)
				frame_color(map, coord, tmp_y, tmp_x);
		}
	}
}
