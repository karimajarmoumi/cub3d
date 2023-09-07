/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/07 16:53:21 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int mouse_hook(int code,int x, int y ,t_map *map)
{
    (void)x;
    (void)y;
    int turn_angle;
    
    turn_angle = 0;
    if(code == RIGHT_CLICK)
        map->player_pos.turn_x = 1;
    if(code == LEFT_CLICK)
        map->player_pos.turn_x = -1;
    update_player_position(map, turn_angle);
   draw_3d_map(map);
    return (1);
}

int main(int ac, char **av)
{
    t_map   map;

    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            parse(av[1],&map);
             init_data_mlx(&map);
            init_textures(&map);
            draw_3d_map(&map);
            mlx_hook(map.data->win, 2, 1L<<0, key_pressed, &map);
            mlx_mouse_hide(map.data->mlx,map.data->win);
            mlx_mouse_hook(map.data->win, mouse_hook, &map);
            mlx_hook(map.data->win, 17, 0, close_win, NULL);
            mlx_loop(map.data->mlx);
        }
        else
            print_error("wrong extension");
    }
    else
        write(1, "Please enter a file name\n",25);
}
