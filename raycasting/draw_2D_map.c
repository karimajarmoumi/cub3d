/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:37 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/05 20:25:12 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void init_data_mlx(t_map *map)
{
    t_data *data = map->data;
    
    data->mlx = mlx_init();
    if (!data->mlx)
        print_error("error mlx_init");
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH,WINDOW_HEIGHT, "./cub3d");
    if (!data->win)
        print_error("Window can't open try again");
    data->img = mlx_new_image(data->mlx,WINDOW_WIDTH, WINDOW_HEIGHT);
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


void draw_mini_map(t_map *map, t_data *data)
{
    int i;
    int j;
    int tmp_x ;
    int tmp_y;

    i = 0;
    while (i <=MINIMAP_HEIGHT)
    {  
        j = 0;   
        while (j <=  MINIMAP_WIDTH)
        { 
             tmp_x = ((map->player_pos.x - MINIMAP_WIDTH/2 ) + j) / FRAME_WIDTH;
             tmp_y = ((map->player_pos.y  - MINIMAP_HEIGHT /2) + i) /FRAME_HEIGHT;
             if(tmp_x>=0 && tmp_y >=0 && tmp_x < map->max_width && tmp_y < map->map_height)
             {
                if(map->map[tmp_y][tmp_x ] == EMPTY || map->map[tmp_y][tmp_x] == map->player_pos.player_symbol)
                    my_mlx_pixel_put(data, j,i, FLOOR_COLOR);
                else if(map->map[tmp_y][tmp_x] == WALL)
                     my_mlx_pixel_put(data, j,i,WALL_COLOR);
                if((i == 100 && j == 100) || (i == 100 && j == 101))
                    my_mlx_pixel_put(data, j, i,PLAYER_COLOR);
             }
             else
                    my_mlx_pixel_put(data, j, i,  SPACE_COLOR);
            j++;
        }
        i++;
    }
}