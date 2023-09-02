/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/02 11:47:22 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
            mlx_hook(map.data->win, 17, 0, close_win, &map);
            mlx_loop(map.data->mlx);
        }
        else
            print_error("wrong extension");        	
    }
    else
        write(1,"Please enter a file name\n",25);
}
