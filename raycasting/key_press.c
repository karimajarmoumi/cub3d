/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/06 20:44:25 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


bool is_wall(t_map map,int x, int y, int flag)
{
    float new_x;
    float new_y;

    new_x = (float)x / FRAME_WIDTH;
    new_y = (float)y / FRAME_HEIGHT;
    if( x >= 0 && y >=0 && x < map.max_width * FRAME_WIDTH && y < map.map_height * FRAME_HEIGHT)
    {
        if(flag == 1)
        {
    
           if(map.map[(int)new_x][(int)floor(map.player_pos.y /FRAME_HEIGHT)] == WALL && 
                map.map[(int)new_y][(int)floor(map.player_pos.x / FRAME_WIDTH)] ==  WALL)
            return true;
        }
        if(map.map[(int)new_y ][(int)new_x] != '1')
            return (false);
    }
        
    return (true);
}

int update_player_position(t_map *map, float turn_angle)
{ 
    int  moves;
    float new_x;
    float new_y;

    map->player_pos.rotation_angle += map->player_pos.turn_x * ROTATION_SPEED;
    map->player_pos.rotation_angle= normalize(map->player_pos.rotation_angle);
    moves = map->player_pos.turn_y * map->player_pos.move_speed;
    new_x = map->player_pos.x + cos(map->player_pos.rotation_angle + turn_angle) * moves;
    new_y = map->player_pos.y + sin(map->player_pos.rotation_angle + turn_angle) * moves;
    if(is_wall(*map,new_x,new_y,1) == false)
    {
        map->player_pos.x = new_x;
        map->player_pos.y = new_y;
        return (1);
    }
    return (0);
}

void init_vars(int *turn_x, int *turn_y, float *turn_angle)
{
    *turn_angle = 0;
    *turn_x = 0;
    *turn_y = 0;
}

int	key_pressed(int code,t_map *map)
{
    float turn_angle;
    init_vars(&(map->player_pos.turn_x), &(map->player_pos.turn_y), &turn_angle);
    turn_angle = 0;
    if (code == LEFT)
    {
        map->player_pos.turn_y = 1;
        turn_angle = -90*(M_PI/180);
    }
    if(code == RIGHT)
    {
        map->player_pos.turn_y = 1;
        turn_angle = 90*(M_PI/180);
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
    if(update_player_position(map, turn_angle) == 1)
            draw_3d_map(map);
	return (code);
}