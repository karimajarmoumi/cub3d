/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:37 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/02 11:49:19 by kel-baam         ###   ########.fr       */
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
    int pos_x;
    int pos_y;
    

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
            pos_x = (x + (FRAME_WIDTH  *j))*FACTOR;
            pos_y = (y + (i * FRAME_HEIGHT))*FACTOR;
            if (map->map[i][j] == WALL)
                my_mlx_pixel_put(data, pos_x,pos_y , wall_color);
            else if (map->map[i][j] == EMPTY || map->map[i][j] == map->player_pos.player_symbol)
            { 
                my_mlx_pixel_put(data,pos_x ,pos_y , floor_color);
            }
            if(y == 59 || x== 59)
                my_mlx_pixel_put(data, pos_x, pos_y, sep_color);
            x++;
        }
        y++;
    }
}



void draw_2D_map(t_map *map, t_data *data)
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
    get_fov(map,map->player_pos.rotation_angle - M_PI / 6  ,map->player_pos.rotation_angle + M_PI / 6);
}