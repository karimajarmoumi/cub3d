/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/07 22:48:49 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void draw_3d_view(t_map *map)
{
    int     i;
    t_coord pos_start;
    t_coord pos_end;
    t_ray   *ray;
    t_list *tmp_list;

    tmp_list = map->rays;
    
    i = 0;
    while(tmp_list &&  i < WINDOW_WIDTH)
    {
        ray = (t_ray*)tmp_list->content;
        pos_start.x = i;
        pos_start.y = MAP_CENTER - (ray->projection_wall / 2);
        pos_end.x = pos_start.x;
        pos_end.y = pos_start.y + ray->projection_wall;
        set_textures(map, ray, i);
        tmp_list = tmp_list->next;
        i++;
    }
}

void draw_3d_map(t_map *map)
{
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6 
        ,map->player_pos.rotation_angle + M_PI / 6);
    draw_3d_view(map);
    free_rays(&(map->rays));
    draw_mini_map(map, map->data);
    mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0, 0);
}