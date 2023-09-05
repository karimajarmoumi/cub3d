/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:29 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/05 20:01:19 by kjarmoum         ###   ########.fr       */
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
  
	dst = t->addr + (y * t->line_length + x * (t->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}


void init_texture(t_map *map, int id_t, char *path_image)
{
    map->textures[id_t].mlx = map->data->mlx;
    map->textures[id_t].win = map->data->win;
    map->textures[id_t].img = mlx_xpm_file_to_image(map->textures[id_t].mlx, path_image
    , &map->textures[id_t].width, &map->textures[id_t].height);
    map->textures[id_t].addr = mlx_get_data_addr(map->textures[id_t].img, &map->textures[id_t].bits_per_pixel, 
        &map->textures[id_t].line_length, &map->textures[id_t].endian);
    if (!map->textures[id_t].img || !map->textures[id_t].addr)
        print_error("** ERROR IN WALL TEXTURE");
}

void init_textures(t_map *map)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (map->args[i]->key[0] == 'N')
            init_texture(map, 0, map->args[i]->value);
        else  if (map->args[i]->key[0] == 'S')
            init_texture(map, 1, map->args[i]->value);
        else  if (map->args[i]->key[0] == 'E')
            init_texture(map, 2, map->args[i]->value);
        else
            init_texture(map, 3, map->args[i]->value);
        i++;   
    }
}

int get_texture_color(t_ray *ray, t_map *map, int offsetY)
{
    if (ray->hit_wall_v == 1)
    {
        if (cos(ray->angle) > 0)
            return (get_pixel_color(&map->textures[2], (int)ray->y % map->textures[2].width, offsetY));
        else 
            return (get_pixel_color(&map->textures[3], (int)ray->y % map->textures[3].width, offsetY)); 
    }
    if (ray->hit_wall_h == 1)
    {
        if (sin(ray->angle) > 0)
            return (get_pixel_color(&map->textures[0], (int)ray->x % map->textures[0].width , offsetY));
        else 
            return (get_pixel_color(&map->textures[1], (int)ray->x % map->textures[1].width, offsetY)); 
    }
    return (0);
}

void set_wall_texture(t_map *map, t_ray *ray, int i, int top_pixel, int bottom_pixel)
{
    int             y;
    // int             offsetX;
    int             offsetY;
    int             distance_from_top;
    
    // if (ray->hit_wall_v == 1)
    //     offsetX = (int)ray->y % 60;
    // if (ray->hit_wall_h == 1)
    //     offsetX = (int)ray->x % 60;
    y = top_pixel;
    while (y < bottom_pixel)
    {
        distance_from_top = y + (ray->projection_wall / 2) - ((map->map_height *60)/ 2);
        offsetY = distance_from_top * ((float)FRAME_HEIGHT / ray->projection_wall);
        my_mlx_pixel_put(map->data, i,  y, get_texture_color(ray, map, offsetY));
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
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6 
        ,map->player_pos.rotation_angle + M_PI / 6, 0);
    draw_3d_view(map);
    draw_2D_map(map, map->data);
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6
    , map->player_pos.rotation_angle + M_PI / 6, 1);
    mlx_put_image_to_window(map->data->mlx, map->data->win, map->data->img, 0, 0);
}