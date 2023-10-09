/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:54:54 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	calculate_wall_top_bottom_pixel(int wall_slice_height,
		t_coord *top_bottom)
{
	top_bottom->x = (WINDOW_HEIGHT / 2) - (wall_slice_height / 2);
	top_bottom->y = top_bottom->x + wall_slice_height;
	if (top_bottom->y >= WINDOW_HEIGHT || top_bottom->y < 0)
		top_bottom->y = WINDOW_HEIGHT;
}

unsigned int	get_pixel_color(t_data *t, double x, double y)
{
	char	*dst;

	dst = NULL;
	if (x >= 0 && y >= 0 && x < t->width && y < t->height)
		dst = t->addr + ((int)y * t->line_length + (int)x * (t->bits_per_pixel
					/ 8));
	return (*(unsigned int *)dst);
}

double	calculate_offset_x(t_ray *ray, int hit_wall_flag, t_data *texture)
{
	if (hit_wall_flag == 1)
		return (((ray->y / FRAME_WIDTH) - (int)(ray->y / FRAME_WIDTH))
			* texture->width);
	else
		return (((ray->x / FRAME_WIDTH) - (int)(ray->x / FRAME_WIDTH))
			* texture->width);
}
