/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/05 17:57:09 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool is_wall(t_map map,int x, int y)
{
    float new_x = (float)x / FRAME_WIDTH;
    float new_y = (float)y / FRAME_HEIGHT  ;
    if( x >= 0 && y >=0 && x < map.max_width*60 && y < map.map_height*60)
    {
        if(map.map[(int)new_y ][(int)new_x] != '1')
            return false;
    }
        
    return true;
}
float normalize(float angle)
{
    if (angle >= 2 * M_PI)
        angle = remainder(angle, 2 * M_PI);
    if (angle <= 0)
        angle += 2 * M_PI;
    return angle;
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
    if(is_wall(*map,new_x,new_y) == false)
    {
        map->player_pos.x = new_x;
        map->player_pos.y = new_y;
        return 1;
    }
    return 0;
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
    {
        //free_double_ptr(map->map);
       // free_double_ptr(map->);
       //destroy image and and free
       print_error("you exit the program");
    }
    if(update_player_position(map, turn_angle) == 1)
    {
        free_rays(&(map->rays));
        draw_3d_map(map);
    }
	return (code);
}

int	close_win(t_map *data)
{
    (void)*data;
    
    print_error("you exit the game!!!");
	exit(0);
	return (0);
}