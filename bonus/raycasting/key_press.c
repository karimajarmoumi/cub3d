/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

bool	is_wall(t_map map, float x, float y, int flag)
{
	float	new_x;
	float	new_y;
	int		len_line;

	new_x = x / FRAME_WIDTH;
	new_y = y / FRAME_HEIGHT;
	len_line = ft_strlen(map.map[(int)new_y]);
	if (new_x > 0 && new_y > 0 && new_y < map.map_height && new_x < len_line)
	{
		if (flag == 1)
		{
			if (map.map[(int)floor(map.player_pos.y
						/ FRAME_HEIGHT)][(int)new_x] == WALL
				&& map.map[(int)new_y][(int)floor(map.player_pos.x
					/ FRAME_WIDTH)] == WALL)
				return (true);
		}
		if (map.map[(int)new_y][(int)new_x] != '1')
			return (false);
	}
	return (true);
}

int	update_player_position(t_map *map, float turn_angle)
{
	int		moves;
	float	new_x;
	float	new_y;
	float	rotation_speed;

	rotation_speed = M_PI / 36;
	map->player_pos.rotation_angle += map->player_pos.player_rotation
		* rotation_speed;
	map->player_pos.rotation_angle = normalize(map->player_pos.rotation_angle);
	moves = map->player_pos.player_moves * map->player_pos.move_speed;
	new_x = map->player_pos.x + cos(normalize(map->player_pos.rotation_angle
				+ turn_angle)) * moves;
	new_y = map->player_pos.y + sin(normalize(map->player_pos.rotation_angle
				+ turn_angle)) * moves;
	if (is_wall(*map, new_x, new_y, 1) == false)
	{
		map->player_pos.x = new_x;
		map->player_pos.y = new_y;
		return (1);
	}
	return (0);
}

void	init_vars(int *player_rotation, int *player_moves, float *turn_angle)
{
	*turn_angle = 0;
	*player_rotation = 0;
	*player_moves = 0;
}

int	key_pressed(int code, t_map *map)
{
	init_vars(&(map->player_pos.player_rotation),
		&(map->player_pos.player_moves), &map->player_pos.turn_angle);
	if (code == LEFT)
	{
		map->player_pos.player_moves = 1;
		map->player_pos.turn_angle = -90 * (M_PI / 180);
	}
	if (code == RIGHT)
	{
		map->player_pos.player_moves = 1;
		map->player_pos.turn_angle = 90 * (M_PI / 180);
	}
	if (code == UP || code == UP_KEY)
		map->player_pos.player_moves = 1;
	if (code == DOWN || code == DOWN_KEY)
		map->player_pos.player_moves = -1;
	if (code == LEFT_ROTATE)
		map->player_pos.player_rotation = -1;
	if (code == RIGHT_ROTATE)
		map->player_pos.player_rotation = 1;
	if (code == ESC)
		print_error("you exit the program");
	if (update_player_position(map, map->player_pos.turn_angle) == 1)
		draw_3d_map(map);
	return (code);
}
