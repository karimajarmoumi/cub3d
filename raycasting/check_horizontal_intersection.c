/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal_intersection.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:14:49 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/11 15:59:06 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int check_horizontal_wall(t_map map,t_coord next, float angle, t_coord *coord)
{
    float inter_x;
    float inter_y;
      
    inter_x = next.x;
    inter_y = next.y;
    if(is_up(angle) == 1)
        inter_y -= 1;
    if(is_wall(map,inter_x, inter_y,0) == true)
    {
        coord->hit_wall = 1;
        coord->x = next.x;
        coord->y = next.y;
            return (1);  
    }
    return (0);
}
t_coord get_f_horizontal_intersection(t_map map, float angle, float *dx,float *dy)
{
    t_coord coord;
    
    coord.y = floor(map.player_pos.y  / FRAME_HEIGHT);
    if(is_up(angle) == 1)
        coord.y = (coord.y * FRAME_HEIGHT);
    else
        coord.y = (coord.y * FRAME_HEIGHT) + FRAME_HEIGHT;
    if(is_up(angle)==1)
        coord.x = map.player_pos.x - fabs(map.player_pos.y - coord.y) / tan(angle);
    else
        coord.x = map.player_pos.x + fabs(map.player_pos.y - coord.y )/ tan(angle);
    *dx = FRAME_HEIGHT/tan(angle);
    if(is_right(angle)== -1 && *dx > 0)
        *dx *= -1;
    if(is_right(angle)== 1 &&  *dx <0)
        *dx *= -1;
    *dy = -is_up(angle)* FRAME_HEIGHT;
    coord.hit_wall = 0;
    return (coord);
}

t_coord horizontal_intersection(t_map map, float angle)
{
    t_coord coord;
    float dx;
    float dy;
    t_coord next;
    
    coord = get_f_horizontal_intersection(map, angle, &dx, &dy);
    next.x = coord.x;
    next.y = coord.y;
    while(next.x >= 0 && next.y >= 0 && next.x <= map.max_width * FRAME_WIDTH && next.y <= map.map_height * FRAME_HEIGHT)
    {
        if(check_horizontal_wall(map,next,angle,&coord) == 1)
            break;
        next.x += dx;
        next.y += dy;         
    }
    if (!coord.hit_wall)
        coord.distance =__FLT_MAX__;
    else
        coord.distance = calculate_distance(map.player_pos.x,map.player_pos.y, coord.x, coord.y);
    return (coord);
}
