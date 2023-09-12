/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:50:29 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/12 23:26:30 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_color_of_ceiling(t_map *map, int ray_x, int top_pixel)
{
	t_coord	pos_start;
	t_coord	pos_end;

	pos_start.x = ray_x;
	pos_start.y = 0;
	pos_end.x = pos_start.x;
	pos_end.y = top_pixel;
	dda(map, &pos_start, &pos_end, map->ceiling_color);
}

void	set_color_of_floor(t_map *map, int ray_x, int bottom_pixel)
{
	t_coord	pos_start;
	t_coord	pos_end;

	pos_start.x = ray_x;
	pos_start.y = bottom_pixel;
	pos_end.x = pos_start.x;
	pos_end.y = WINDOW_HEIGHT;
	dda(map, &pos_start, &pos_end, map->floor_color);
}



void	set_wall_texture(t_map *map, t_ray *ray, int i, int top_pixel,
		int bottom_pixel)
{
	int		y;
	double	offsety;
	double	offsetx;
	t_data	*img_data;

	offsety = 0;
	y = top_pixel;
	if (ray->hit_wall_v == 1)
	{
		if (cos(ray->angle) > 0)
			img_data = &map->textures[2];
		else
			img_data = &map->textures[3];
		offsetx = calculate_offset_x(ray, 1, img_data);
	}
	if (ray->hit_wall_h == 1)
	{
		if (sin(ray->angle) > 0)
			img_data = &map->textures[1];
		else
			img_data = &map->textures[0];
		offsetx = calculate_offset_x(ray, 0, img_data);
	}
	if (y < 0)
	{
		offsety = (img_data->height / ray->projection_wall) * abs(y);
		y = 0;
	}
	while (y < bottom_pixel)
	{
		my_mlx_pixel_put(map->data, i, y, get_pixel_color(img_data, offsetx,
				offsety));
		offsety += (img_data->height / ray->projection_wall);
		y++;
	}
}

void	set_textures(t_map *map, t_ray *ray, int i)
{
	int	top_pixel;
	int	bottom_pixel;

	calculate_wall_top_bottom_pixel((int)ray->projection_wall, &top_pixel,
		&bottom_pixel);
	set_color_of_ceiling(map, i, top_pixel);
	set_wall_texture(map, ray, i, top_pixel, bottom_pixel);
	set_color_of_floor(map, i, bottom_pixel);
}
