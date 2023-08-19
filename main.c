/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/19 11:25:20 by kel-baam         ###   ########.fr       */
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
           {    if(x > 26 && x <  30 && y > 26 && y < 30 )
               my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), player_color);
           }
           if(y == 59 || x== 59)
                 my_mlx_pixel_put(data, x + (60  *j), y + (i * 60), space_color);
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
        while (map && map->map[i][j])
        {  
            display_frame(data, map, i, j);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 23);
   
}

// void player_move(t_map *map)
// {
    
// }

int	key_hook(int code,t_map *map,t_data *data)
{
    (void)*data;
    int player_x = map->player_pos.x ;
    int player_y = map->player_pos.y;
    if (code == LEFT)
    {
        printf("is leeeft");
        player_x+=1;
    }
    if(code == RIGHT)
    {
        printf("RIIGHT\n");
        player_x+=1;
    }
    if(code == UP)
    {
        printf("UP\n");
        player_y+=1; 
    }
    if(code == DOWN)
    {
        printf("DDDDDOWN\n");
        player_y-=1;
    }
   // map->map[player_y][player_x] =map->map[map->player_pos.x][]
    //display_map(map, data);
	return (0);
}

int	close_win(t_data *data)
{
    //free
    (void)*data;
    print_error("you exit the game!!!");
	exit(0);
	return (0);
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
           // DDA(&map,&data,23,0);
            mlx_key_hook(data.win,key_hook, &data);
            mlx_hook(data.win,17,0, close_win, &data);
        }
        else
            print_error("wrong extension");
        printf("kkkk\n");
        	
        mlx_loop(data.mlx);
    }
    else
        write(1,"Please enter a file name\n",25);
}
