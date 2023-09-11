/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:50:29 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/11 21:28:01 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_color_of_ceiling(t_map *map, int ray_x, int top_pixel)
{
	t_coord pos_start;
   
	pos_start.x = ray_x;
	pos_start.y = 0;
	dda(map, &pos_start , ray_x, top_pixel, map->ceiling_color);
}

void    set_color_of_floor(t_map *map, int ray_x, int bottom_pixel)
{
	t_coord pos_start;
   
	pos_start.x = ray_x;
	pos_start.y = bottom_pixel; 
	dda(map, &pos_start , pos_start.x, WINDOW_HEIGHT, map->floor_color);
}

void    set_wall_texture(t_map *map, t_ray *ray, int i, int top_pixel, int bottom_pixel)
{
	int     y;
	double  offsetY;
	
	offsetY = 0;
	y = top_pixel;
	if (y < 0)
	{
		offsetY = (64 / ray->projection_wall) * abs(y); 
		y = 0;
	}
	while (y < bottom_pixel)
	{
		my_mlx_pixel_put(map->data, i,  y, get_texture_color(ray, map, &offsetY));
		y++;
	}
}

void    set_textures(t_map *map, t_ray *ray, int i)
{
	int top_pixel;
	int bottom_pixel;
	
	calculateWall_Top_Bottom_pixel((int)ray->projection_wall, &top_pixel, &bottom_pixel);
	set_color_of_ceiling(map, i, top_pixel);
	set_wall_texture(map, ray, i, top_pixel, bottom_pixel);
	set_color_of_floor(map, i, bottom_pixel);
}