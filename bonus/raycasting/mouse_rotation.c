/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:28:49 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/14 16:35:08 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	mouse_hook(int code, int x, int y, t_map *map)
{
	int	turn_angle;

	(void)x;
	(void)y;
	turn_angle = 0;
	map->player_pos.player_moves = 0;
	if (code == RIGHT_CLICK)
		map->player_pos.player_rotation = 1;
	if (code == LEFT_CLICK)
		map->player_pos.player_rotation = -1;
	if (update_player_position(map, map->player_pos.turn_angle) == 1)
		draw_3d_map(map);
	return (1);
}
