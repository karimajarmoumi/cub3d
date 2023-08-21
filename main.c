/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/21 16:23:22 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


// void rotate_player(t_map *map)
// {
//     map->player_pos.x += map->speed *cos();
//     map->player_pos.y += map->speed *sin(map->angle);
// }


int main(int ac, char **av)
{
    t_map   map;

    map.angle = 10;
    map.speed = 0.1;
    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            readMap(av[1],&map);
            draw_map(&map, (map.data));
           // rotate_player(&map);
            //draw_map(&map, map.data);
            mlx_hook(map.data->win, 2,1L<<0, key_pressed,&map);
            mlx_hook(map.data->win,17,0, close_win, &map); 
            mlx_loop(map.data->mlx);
        }
        else
            print_error("wrong extension");        	
    }
    else
        write(1,"Please enter a file name\n",25);
}
