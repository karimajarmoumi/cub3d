/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/04 20:25:07 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int mouse_hook(int x, int y, void *map)
{
    (void)y;
    int turn_angle = 0;
    t_map *tmp_map;
    tmp_map = (t_map*)map;
    if(x >= tmp_map->player_pos.x)
        tmp_map->player_pos.turn_x = 1;
    else
        tmp_map->player_pos.turn_x = -1;
    update_player_position(tmp_map, turn_angle);

        draw_3d_map(tmp_map);
    return 1;
}

int main(int ac, char **av)
{
    t_map   map;

    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            readMap(av[1],&map);
            init_data_mlx(&map);
            draw_3d_map(&map);
            mlx_hook(map.data->win, 2, 1L<<0, key_pressed, &map);
           // mlx_hook(map.data->win, 6, 1L<<6, mouse_hook, &map);
            mlx_hook(map.data->win, 17, 0, close_win, &map);
            mlx_loop(map.data->mlx);
        }
        else
            print_error("wrong extension");
    }
    else
        write(1, "Please enter a file name\n",25);
}
