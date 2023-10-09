/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/14 16:25:09 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac == 2)
	{
		if (check_extension(av[1]) == true)
		{
			parse(av[1], &map);
			init_mlx_ptr(&map);
			init_textures(&map);
			init_data_mlx(&map);
			draw_3d_map(&map);
			mlx_hook(map.data->win, 2, 1L << 0, key_pressed, &map);
			mlx_hook(map.data->win, 17, 0, close_win, NULL);
			mlx_loop(map.data->mlx);
		}
		else
			print_error("Wrong extension");
	}
	else
		print_error("Please enter a file name");
}
