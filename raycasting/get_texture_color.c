/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:54:54 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/07 21:42:39 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void calculateWall_Top_Bottom_pixel(int wall_slice_height, int *top, int *bottom)
{
    *top = (WINDOW_HEIGHT / 2) - (wall_slice_height / 2);
    if (*top < 0 || *top >= WINDOW_HEIGHT)
        *top = 0;
    *bottom = *top + wall_slice_height ;
    if (*bottom >= WINDOW_HEIGHT || *bottom < 0)
        *bottom = WINDOW_HEIGHT;
}

unsigned int  get_pixel_color(t_data *t, double x, double y)
{
	char	*dst = NULL;
  
	dst = t->addr + ((int)y * t->line_length + (int)x * (t->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

double calculate_offsetX(t_ray *ray, int hit_wall_flag, t_data *texture)
{
    if (hit_wall_flag == 1)
        return ((ray->y / FRAME_WIDTH) - (int)(ray->y / FRAME_WIDTH)) * texture->width;
    else 
        return ((ray->x / FRAME_WIDTH) - (int)(ray->x / FRAME_WIDTH)) * texture->width;
}   

int get_texture_color(t_ray *ray, t_map *map, double *offsetY)
{
    if (ray->hit_wall_v == 1)
    {
        if (cos(ray->angle) > 0)
        {
            (*offsetY) += (map->textures[0].height / ray->projection_wall ) ;
            return (get_pixel_color(&map->textures[0], calculate_offsetX(ray, 1, &map->textures[0]), *offsetY));
        }
        else 
        {
            *offsetY += map->textures[1].height / ray->projection_wall;
            return (get_pixel_color(&map->textures[1], calculate_offsetX(ray, 1, &map->textures[1]), *offsetY)); 
        }
    }
    if (ray->hit_wall_h == 1)
    {
        if (sin(ray->angle) > 0)
        {
            *offsetY += map->textures[2].height / ray->projection_wall;
            return (get_pixel_color(&map->textures[2], calculate_offsetX(ray, 0, &map->textures[2]), *offsetY));
        }
        else
        {
            *offsetY += map->textures[3].height / ray->projection_wall;
            return (get_pixel_color(&map->textures[3], calculate_offsetX(ray, 0, &map->textures[3]), *offsetY)); 
        } 
    }
    return (0);
}