/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:33:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/08 14:43:49 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


bool is_wall(t_map map, float x, float y, int flag)
{
    float new_x;
    float new_y;
    int len_line;
    
    new_x = x / FRAME_WIDTH;
    new_y = y / FRAME_HEIGHT;
    //if(map.map[(int)new_y])
        len_line = ft_strlen(map.map[(int)new_y]);
    if( new_x > 0 && new_y > 0 &&  new_y < map.map_height && new_x < len_line)
    {
        if(flag == 1)
        {
           if(map.map[(int)floor(map.player_pos.y /FRAME_HEIGHT)][(int)new_x] == WALL && 
                map.map[(int)new_y][(int)floor(map.player_pos.x / FRAME_WIDTH)] ==  WALL)
            return true;
        }
        if(map.map[(int)new_y][(int)new_x] != '1')
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
    new_x = map->player_pos.x + cos(normalize(map->player_pos.rotation_angle + turn_angle)) * moves;
    new_y = map->player_pos.y + sin(normalize(map->player_pos.rotation_angle + turn_angle)) * moves;
  
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
    {
       free_struct_args(map->args);
       print_error("you exit the program");
    }
    if(update_player_position(map, turn_angle) == 1)
    {
            draw_3d_map(map);
    }
	return (code);
}