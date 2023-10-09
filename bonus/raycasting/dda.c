/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	dda(t_map *map, t_coord *pos, t_coord *target, int color)
{
	float	next_x;
	float	next_y;
	float	dist;
	float	x;
	float	y;

	if (fabs(target->x - pos->x) > fabs(target->y - pos->y))
		dist = fabs(target->x - pos->x);
	else
		dist = fabs(target->y - pos->y);
	next_x = (target->x - pos->x) / (float)dist;
	next_y = (target->y - pos->y) / (float)dist;
	x = pos->x;
	y = pos->y;
	while (dist >= 0 && x >= 0 && y >= 0)
	{
		my_mlx_pixel_put(map->data, x, y, color);
		x += next_x;
		y += next_y;
		dist--;
	}
}
