/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/02 11:49:26 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void draw_3d_view(t_map map)
{
    int map_center = map.map_height*60 / 2;
    t_coord pos;
    t_ray *ray;
    int i;
    i = 0;
    while(map.rays &&  i < map.max_width*60)
    {
        ray = (t_ray*)map.rays->content;
        pos.x = i;
        pos.y = map_center - (ray->projection_wall/2);
        DDA(&map,&pos,pos.x,pos.y + ray->projection_wall);
        map.rays = map.rays->next;
        i++;
    }
}

void draw_3d_map(t_map *map)
{
   
   draw_2D_map(map, map->data);
    draw_3d_view(*map);
    mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0, 0);
}