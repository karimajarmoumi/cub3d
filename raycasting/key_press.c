/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/23 10:57:11 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool is_wall(t_map map,int x, int y)
{
    int new_x = (x) / FRAME_WIDTH  ;
    int new_y = (y) / FRAME_HEIGHT  ;
    
    if(map.map[new_y ][new_x] != '1')
        return false;
    return true;
}
void update_player_position(t_map *map, float turn_angle)
{ 
    int  moves;
    float new_x;
    float new_y;

    map->player_pos.rotation_angle += map->player_pos.turn_x * map->player_pos.rotation_speed;
    moves = map->player_pos.turn_y * map->player_pos.move_speed;
    new_x = map->player_pos.x + cos(map->player_pos.rotation_angle + turn_angle) * moves;
    new_y = map->player_pos.y + sin(map->player_pos.rotation_angle + turn_angle) * moves;
    if(is_wall(*map,new_x,new_y) == false)
    {
        map->player_pos.x = new_x;
         map->player_pos.y = new_y;
    }
}

int	key_pressed(int code,t_map *map)
{
    float turn_angle;
    
    map->player_pos.turn_x = 0;
    map->player_pos.turn_y = 0;
    turn_angle = 0;
    if (code == LEFT)
    {
        map->player_pos.turn_y = 1;
        turn_angle = -90*(PI/180);
    }
    if(code == RIGHT)
    {
        map->player_pos.turn_y = 1;
        turn_angle = 90*(PI/180);
    }
    if(code == UP)
        map->player_pos.turn_y = 1;
    if(code == DOWN)
        map->player_pos.turn_y = -1;
    if(code == LEFT_ROTATE)
        map->player_pos.turn_x = -1;
    if(code == RIGHT_ROTATE)
        map->player_pos.turn_x = 1;
    if(code == ESC)
       print_error("you exit the program");
    update_player_position(map, turn_angle);
    mlx_clear_window (map->data->mlx, map->data->win);
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