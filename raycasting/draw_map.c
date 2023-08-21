/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:37 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/21 20:03:18 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void init_data_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        print_error("error mlx_init");
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH * 60, WINDOW_HEIGHT * 60, "./cub3d");
    if (!data->win)
        print_error("Window can't open try again");
    data->img = mlx_new_image(data->mlx, WINDOW_WIDTH * 60, WINDOW_HEIGHT * 60);
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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
    while (y < 60)
    {
        x = 0;
        while (x < 60)
        {
            if (map->map[i][j] == WALL)
                my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), wall_color);
            else if (map->map[i][j] == EMPTY || map->map[i][j] == PLAYER_N)
            { 
                my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), floor_color);
            }
            if(y == 59 || x== 59)
                my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), sep_color);
            x++;
        }
        y++;
    }
    int p = 0;
    while(p < 20)
    {
        my_mlx_pixel_put(data, 30 + p * cos(map->player_pos.rotation_angle) + (map->player_pos.x), 25 + p * sin(map->player_pos.rotation_angle) + (map->player_pos.y), 0x0000FF);
        p++;
    }
    
}

void draw_map(t_map *map, t_data *data)
{
    int i;
    int j;

    j = 0;
    i = 0;
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
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
   //  DDA(map,map->data,map->player_pos.x + cos(map->player_pos.rotation_angle)*20,
     //    map->player_pos.y + sin(map->player_pos.rotation_angle)*20);
}