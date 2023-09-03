/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/03 22:46:17 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void calculateWall_Top_Bottom_pixel(t_map *map, int wall_slice_height, int *top, int *bottom)
{
    *top = ((map->map_height * 60) / 2) - (wall_slice_height / 2);
    if (*top < 0 || *top > map->map_height  *60)
        *top = 0;
    *bottom = *top + wall_slice_height ;
    if (*bottom > map->map_height *60 || *bottom < 0)
        *bottom = map->map_height * 60;
}

void    set_color_of_ceiling(t_map *map, int ray_x, int top_pixel)
{
    t_coord pos_start;
   
    pos_start.x = ray_x;
    pos_start.y = 0;
    DDA(map, &pos_start , ray_x, top_pixel, map->ceiling_color);
}

void    set_color_of_floor(t_map *map, int ray_x, int bottom_pixel)
{
    t_coord pos_start;
   
    pos_start.x = ray_x;
    pos_start.y = bottom_pixel;
    DDA(map, &pos_start , ray_x, map->map_height * 60, map->floor_color);
}

void    set_textures(t_map *map, t_ray *ray, int i)
{
    int     top_pixel;
    int     bottom_pixel;
    int     offsetX;
    // int     offsetY;
    int     y;
    
    calculateWall_Top_Bottom_pixel(map, (int)ray->projection_wall, &top_pixel, &bottom_pixel);
    set_color_of_ceiling(map, i, top_pixel);
    if (ray->hit_wall_v)
        offsetX = (int)ray->y % 60;
    else
        offsetX = (int)ray->x % 60;
    y = top_pixel;
    while (y < bottom_pixel)
    {
        //offsetY = (y - top_pixel) * ((float)FRAME_HEIGHT / ray->projection_wall);
        my_mlx_pixel_put(map->data, i,  y, ((i % 50) && ( y  % 50))? 0x000000 : 0xffffff);   
        y++;
    }
    set_color_of_floor(map, i, bottom_pixel);
}


void draw_3d_view(t_map map)
{
    int     i;
    int     map_center;
    t_coord pos_start;
    t_coord pos_end;
    t_ray   *ray;
    
    i = 0;
    map_center = map.map_height * 60 / 2;
    while(map.rays &&  i < map.max_width*60)
    {
        ray = (t_ray*)map.rays->content;
        pos_start.x = i;
        pos_start.y = map_center - (ray->projection_wall / 2);
        pos_end.x = pos_start.x;
        pos_end.y = pos_start.y + ray->projection_wall;
        set_textures(&map, ray, i);
        //draw_window(map)
       // DDA(&map,&pos_start,pos_start.x,pos_start.y + ray->projection_wall, 0xFFFFFF);
        //draw_wall_texture(map, pos_start, pos_end, wall_texture());
        map.rays = map.rays->next;
        i++;
    }
}

void draw_3d_map(t_map *map)
{
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6  ,map->player_pos.rotation_angle + M_PI / 6,0);
    draw_3d_view(*map);
    draw_2D_map(map, map->data);
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6  ,map->player_pos.rotation_angle + M_PI / 6,1);
    mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0, 0);
}