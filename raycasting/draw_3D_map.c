/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/04 20:33:57 by kjarmoum         ###   ########.fr       */
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

unsigned int  get_pixel_color(t_data *t, int x, int y)
{
	char	*dst = NULL;
    // int     x_t;
    // int     y_t;
    
    // x_t = x;
    // y_t = y;
    if (x >= 0 && y >= 0 && x <= 24*60 && y <= 11*60)
	    dst = t->addr + (y * t->line_length + x * (t->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

void init_textures(t_map *map)
{
    map->textures->line_length = 0;
    map->textures->endian = 0;
    map->textures->mlx = map->data->mlx;
    map->textures->win = map->data->win;
    map->textures->img = mlx_xpm_file_to_image(map->textures->mlx, WALL_PATH, &map->textures->width, &map->textures->height);
    map->textures->addr = mlx_get_data_addr(map->textures->img, &map->textures->bits_per_pixel, 
        &map->textures->line_length, &map->textures->endian);
    if (!map->textures->img || !map->textures->addr)
        print_error("** ERROR IN WALL TEXTURE");
}

void set_wall_texture(t_map *map, t_ray *ray, int i, int top_pixel, int bottom_pixel)
{
    int             y;
    int             offsetX;
    int             offsetY;
    unsigned int    color;
    // int             distance_from_top;
    
    if (ray->hit_wall_v)
        offsetX = (int)ray->y % 60;
    else
        offsetX = (int)ray->x % 60;
    y = top_pixel;
    while (y < bottom_pixel)
    {
       // distance_from_top = y + (ray->projection_wall / 2) - (map->map_height / 2);
        offsetY = (y - top_pixel) * ((float)FRAME_HEIGHT / ray->projection_wall);
        color = get_pixel_color(map->textures, offsetY,offsetX);
        my_mlx_pixel_put(map->data, i,  y, color);   
        y++;
    }
}

void    set_textures(t_map *map, t_ray *ray, int i)
{
    int     top_pixel;
    int     bottom_pixel;
    
    calculateWall_Top_Bottom_pixel(map, (int)ray->projection_wall, &top_pixel, &bottom_pixel);
    set_color_of_ceiling(map, i, top_pixel);
    set_wall_texture(map, ray, i, top_pixel, bottom_pixel);
    set_color_of_floor(map, i, bottom_pixel);
}

void draw_3d_view(t_map *map)
{
    int     i;
    int     map_center;
    t_coord pos_start;
    t_coord pos_end;
    t_ray   *ray;
    
    i = 0;
    map_center = map->map_height * 60 / 2;
    while(map->rays &&  i < map->max_width * 60)
    {
        ray = (t_ray*)map->rays->content;
        pos_start.x = i;
        pos_start.y = map_center - (ray->projection_wall / 2);
        pos_end.x = pos_start.x;
        pos_end.y = pos_start.y + ray->projection_wall;
        set_textures(map, ray, i);
        map->rays = map->rays->next;
        i++;
    }
}

void draw_3d_map(t_map *map)
{
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6  ,map->player_pos.rotation_angle + M_PI / 6, 0);
    draw_3d_view(map);
    draw_2D_map(map, map->data);
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6  ,map->player_pos.rotation_angle + M_PI / 6, 1);
    mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0, 0);
}