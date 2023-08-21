/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/21 20:55:46 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	key_pressed(int code,t_map *map)
{
    // float moves;
    map->player_pos.turn_x =0;
    map->player_pos.turn_y =0;

    if (code == LEFT)
        map->player_pos.x -= cos(map->player_pos.rotation_angle);
    else if(code == RIGHT)
        map->player_pos.x+= cos(map->player_pos.rotation_angle);
    else if(code == UP)
        map->player_pos.y-= sin(map->player_pos.rotation_angle);
    else if(code == DOWN)
        map->player_pos.y+= sin(map->player_pos.rotation_angle);
    else if(code == ESC)
        print_error("you exit the program");
    else if(code == LEFT_ROTATE)
        map->player_pos.turn_x = -1;
    else if(code == RIGHT_ROTATE)
        map->player_pos.turn_x = 1;
    else if(code == UP_ROTATE)
        map->player_pos.turn_y = 1;
    else if(code == DOWN_ROTATE)
        map->player_pos.turn_y = -1;
    mlx_clear_window (map->data->mlx, map->data->win);
    if(map->player_pos.turn_x != 0 || map->player_pos.turn_y != 0)
    {
        map->player_pos.rotation_angle+=map->player_pos.turn_x*map->player_pos.rotation_speed;
      //  moves = map->player_pos.turn_y*map->player_pos.move_speed;
        map->player_pos.x += cos(map->player_pos.rotation_angle)* 10;
        map->player_pos.y += sin(map->player_pos.rotation_angle)*10;
        printf("%f %f \n",map->player_pos.y,map->player_pos.x);
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