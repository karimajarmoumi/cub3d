/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/21 18:33:57 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

int	key_pressed(int code,t_map *map)
{
    int moves;
    map->player_pos.turn_x =0;
    map->player_pos.turn_y =0;

    if (code == LEFT)
    {
        map->player_pos.x -= 1;
       // map->player_pos.x-=1;
    }
    if(code == RIGHT)
        map->player_pos.x+=1;
    if(code == UP)
        map->player_pos.y-=1;
    if(code == DOWN)
        map->player_pos.y+=1;
    if(code == ESC)
        print_error("you exit the program");
    if(code == LEFT_ROTATE)
        map->player_pos.turn_x = -1;
    if(code == RIGHT_ROTATE)
        map->player_pos.turn_x = 1;
    if(code == UP_ROTATE)
        map->player_pos.turn_y = 1;
     if(code == DOWN_ROTATE)
        map->player_pos.turn_y = -1;
    mlx_clear_window (map->data->mlx, map->data->win);
    if(map->player_pos.turn_x != 0 || map->player_pos.turn_y != 0)
    {
        map->player_pos.rotation_angle+=map->player_pos.turn_x*map->player_pos.rotation_speed;
        moves = map->player_pos.turn_y*map->player_pos.move_speed;
        map->player_pos.x +=cos(map->player_pos.rotation_angle)*moves;
        map->player_pos.y+= sin(map->player_pos.rotation_angle)*moves;
    }
    draw_map(map, map->data);
	return (code);
}

int	close_win(t_map *data)
{
    (void)*data;
    
    print_error("you exit the game!!!");
	exit(0);
	return (0);
}