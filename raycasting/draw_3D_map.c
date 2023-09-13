/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/13 22:48:51 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_3d_view(t_map *map, float start_angle, float end_angle)
{
	t_coord	horizontal_coord;
	t_coord	vertical_coord;
	t_ray	ray;
	int		i;

	i = 0;
	while (start_angle <= end_angle)
	{
		horizontal_coord = horizontal_intersection(*map,
				normalize(start_angle));
		vertical_coord = vertical_intersection(*map, normalize(start_angle));
		if (vertical_coord.distance >= horizontal_coord.distance)
			ray = ray_data(map, normalize(start_angle), 1, horizontal_coord);
		else
			ray = ray_data(map, normalize(start_angle), 0, vertical_coord);
		set_textures(map, &ray, i);
		i++;
		start_angle += (M_PI / 3) / (float)WINDOW_WIDTH;
	}
}

void	draw_3d_map(t_map *map)
{
	draw_3d_view(map, map->player_pos.rotation_angle - M_PI / 6,
		map->player_pos.rotation_angle + M_PI / 6);
	draw_mini_map(map, map->data);
	mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0,
		0);
}
