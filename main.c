/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/17 20:28:54 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
    int space_color;
    (void)map;
    wall_color = 0x3333FF;
    player_color = 0xFF0000;
    space_color = 0x008000;
    y = 0; 
    while (y < 60)
    {
        x = 0;
        while (x < 60)
        {
            if (map->map[i][j] == WALL)
                my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), wall_color);
            else if (map->map[i][j] == PLAYER_N)
           {
               my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), player_color);
           }
            x++;
        }
        y++;
    }
}


void display_map(t_map *map, t_data *data)
{
    int i;
    int j;

    j = 0;
    i = 0;
    init_data_mlx(data);
    while (map && map->map[i])
    {         
        j = 0;
        printf("|%s|",map->map[i]);
        while (map && map->map[i][j])
        {  
            display_frame(data, map, i, j);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 23);
   
}


int main(int ac, char **av)
{
    t_map   map;
    t_data  data;
    
    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            readMap(av[1],&map);
            display_map(&map, &data);
            DDA(&map,&data,23,0);
        }
        else
            print_error("wrong extension");
             mlx_loop(data.mlx);
      //  printf("%d %dwwwwoooow\n",map.floor_color,map.ceiling_color);
    }
    else
        write(1,"Please enter a file name\n",25);
}
