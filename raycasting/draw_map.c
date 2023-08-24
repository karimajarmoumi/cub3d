/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:37 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/24 15:15:51 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void init_data_mlx(t_map *map)
{
    t_data *data = map->data;
    
    data->mlx = mlx_init();
    if (!data->mlx)
        print_error("error mlx_init");
    data->win = mlx_new_window(data->mlx, map->max_width * 60,map->map_height* 60, "./cub3d");
    if (!data->win)
        print_error("Window can't open try again");
    data->img = mlx_new_image(data->mlx, map->max_width * 60, map->map_height * 60);
    if (!data->img)
        print_error("error to create image");   
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
        &data->line_length, &data->endian);
    if (!data->addr)
        print_error("error to get the memory address for the pixel data");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
    int nx = x;
    int ny = y;
	dst = data->addr + (ny * data->line_length + nx * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void display_frame(t_data *data, t_map *map, int i, int j)
{
    int y;
    int x;
    int wall_color;
    int player_color;
    int floor_color;
    int sep_color;

    wall_color = 0xA0A0A0;
    player_color = 0x0000FF;
    floor_color = 0xFFFFFF;
    sep_color = 0x000000;
    y = 0; 
    while (y < FRAME_HEIGHT)
    {
        x = 0;
        while (x < FRAME_WIDTH)
        {
            if (map->map[i][j] == WALL)
                my_mlx_pixel_put(data, x + (FRAME_WIDTH  *j), y + (i * FRAME_HEIGHT), wall_color);
            else if (map->map[i][j] == EMPTY || map->map[i][j] == map->player_pos.player_symbol)
            { 
                my_mlx_pixel_put(data, x + (FRAME_WIDTH *j), y + (i * FRAME_HEIGHT), floor_color);
            }
            if(y == 59 || x== 59)
                my_mlx_pixel_put(data, x + (FRAME_WIDTH  *j), y + (i * FRAME_HEIGHT), sep_color);
            x++;
        }
        y++;
    }
}

t_ray* ray_data (t_map map,int x, int y,int distance)
{
    (void)x;
    (void)y;
    (void)distance;
    t_ray *ray =NULL;
   ray=(t_ray*) map.rays->content;
   if(x >= 0)
       ray->x = x;
   printf("heere\n");
   if(y >= 0)
       ray->y = y;
   if(distance >= 0)
       ray->distance = distance;
    return ray;
}

void draw_rays(t_map map, t_data data, double start, double end)
{
    double x;
    double y;
    
    map.rays->content = malloc(sizeof(t_ray));
    while (start < end)
    {
        x = map.player_pos.x;
        y = map.player_pos.y;
        while (1)
        {
            if (map.map[(int)y / 60][(int)x / 60] == WALL)
            {
                ft_lstadd_back(&map.rays,ft_lstnew((t_ray*)ray_data(map,x,y,-1)));
                break;
            }
            my_mlx_pixel_put(&data, x , y, 0xff0000);
            x += cos(start);
            y += sin(start);
        }
        start += 60*(PI/180)/180;
    }
}

void draw_map(t_map *map, t_data *data)
{
    int i;
    int j;
    double start;
    double end;

    j = 0;
    i = 0;
    start = map->player_pos.rotation_angle - 30*(PI/180);
    end = map->player_pos.rotation_angle + 30*(PI /180);
    while (map && map->map[i])
    {  
        j = 0;
        while (map && map->map[i][j])
        { 
            display_frame(data, map, i, j);
            j++;
        }
        i++;
    }
    draw_rays(*map, *data, start, end);
    // Draw3D();
    // Draw2D();
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);        
}