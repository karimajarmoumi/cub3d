/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/02 22:38:41 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void draw_ceiling_floor(t_map *map, int map_center)
{
    int i;
    t_coord pos;

    i = 0;
    //ceilling
    // printf("%d\n",map_center/60);
    while (i < map_center)
    {
        pos.x = 0;
        pos.y = i;
        DDA(map, &pos, map->max_width *60, i, map->ceiling_color);
        i++;
    }
    //floor
    i = map_center;
    while (i < map->map_height *60)
    {
        pos.x = 0;
        pos.y = i;
        DDA(map, &pos, map->max_width *60, i, map->floor_color);
        i++;
    }
}


void draw_wall_texture(t_map map, t_coord pos_start, t_coord pos_end, int *wall_texture)
{
    int y;

    y = pos_start.y;
    while (y < pos_end.y)
    {
        my_mlx_pixel_put(map.data, pos_start.x, y, wall_texture[(int)(pos_start.x) + y ]);
        y++;
    }
}

void calculateWall_Top_Bottom_pixel(t_map *map, int wall_slice_height, int *top, int *bottom)
{
    *top = (map->map_height / 2) - (wall_slice_height / 2);
    if (*top < 0)
        *top = 0;
    *bottom = (map->max_width / 2) + (wall_slice_height / 2);
    if (*bottom > map->map_height)
        *bottom = map->map_height;
}

int *set_color_of_ceiling(t_map *map, int ray_number, int top_pixel, int *color_window)
{
    int y;

    y = 0;
    while (y < top_pixel)
    {
        color_window[(map->max_width * y) + ray_number] = map->ceiling_color;
        y++;
    }
    return (color_window);
}

int *set_color_of_floor(t_map *map, int ray_number, int bottom_pixel, int *color_window)
{
   int y;

   y = bottom_pixel;
   while (y < map->map_height)
   {
        color_window[(map->max_width * y) + ray_number] = map->floor_color;
        y++;
   }
    return (color_window);
}

int *wall_texture()
{
    int x;
    int y;

    int *wall_texture;
    
    x = 0;
    wall_texture = malloc(sizeof(int) * FRAME_HEIGHT * FRAME_WIDTH);
    while (x < FRAME_WIDTH)
    {
        y = 0; 
        while (y < FRAME_HEIGHT)
        {
            wall_texture[(y * FRAME_WIDTH) + x] = (x % 8) ? 0xa2224e : 0x030103;
            y++;
        }
        x++;
    }
    return (wall_texture);
}





void textures(t_map *map)
{
    int     i;
    t_ray   *ray;
    int     top_pixel;
    int     bottom_pixel;
    int     *color_buffer;
    // int     offsetX;
    // int     offsetY;
    int     *texture_color;
    int     y;

    i = 0;
    color_buffer = malloc(sizeof(int) * map->max_width * map->map_height);
    texture_color = wall_texture();
    while (i < NUM_RAYS)
    {
        ray = (t_ray *) map->rays;
        calculateWall_Top_Bottom_pixel(map, (int)ray->projection_wall, &top_pixel, &bottom_pixel);
        //set color of ceiling
        color_buffer = set_color_of_ceiling(map, i, top_pixel, color_buffer);
        //set color of wall
        // if (ray->hit_wall_v)
        //     offsetX = 
        y = top_pixel;
        while (y < bottom_pixel)
        {
            // color_buffer[(map->max_width * y) + i] 
            //     = texture_color[(FRAME_WIDTH * offsetY) + offsetX];
            y++;
        }
        //set color of floor
        color_buffer = set_color_of_floor(map, i, bottom_pixel, color_buffer);
        map->rays = map->rays->next;
        i++;
    }
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
    draw_ceiling_floor(&map, map_center);
    while(map.rays &&  i < map.max_width*60)
    {
        ray = (t_ray*)map.rays->content;
        pos_start.x = i;
        pos_start.y = map_center - (ray->projection_wall / 2);
        pos_end.x = pos_start.x;
        pos_end.y = pos_start.y + ray->projection_wall;
       // DDA(&map,&pos,pos.x,pos.y + ray->projection_wall, 0xFFFFFF);
        draw_wall_texture(map, pos_start, pos_end, wall_texture());
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