/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:12 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/05 11:14:14 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    float distance;

    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return distance;
}

t_coord get_f_vertical_intersection(t_map map, float angle, float *dx,float *dy)
{
    t_coord coord;
    coord.x = floor(map.player_pos.x / FRAME_WIDTH);
    if(is_right(angle) == 1)
        coord.x = coord.x * FRAME_WIDTH + FRAME_WIDTH;
    else 
        coord.x = coord.x * FRAME_WIDTH;
    if(is_right(angle) == 1)
        coord.y = map.player_pos.y + (tan(angle) * fabs( map.player_pos.x - coord.x));
    else
        coord.y = map.player_pos.y - (tan(angle) * fabs( map.player_pos.x - coord.x));
    *dy = tan(angle) * FRAME_WIDTH;
    if(is_up(angle)== 1 && *dy > 0)
        *dy *= -1;
    if(is_up(angle)== -1 && *dy < 0)
        *dy *= -1;
    *dx = is_right(angle) * FRAME_WIDTH;
    return  coord;
}
t_coord vertical_intersection(t_map map,float angle)
{
    t_coord coord;
    float dx;
    float dy;
    float inter_x;
    float inter_y;

    coord =  get_f_vertical_intersection(map, angle, &dx, &dy);
    coord.hit_wall = 0;
    float nextX = coord.x;
    float nextY = coord.y;

    while(nextX >= 0 &&nextY >= 0 && nextX <= map.max_width*60 &&nextY <= map.map_height*60)
    {
        inter_x = nextX;
        inter_y = nextY;
        if(is_right(angle) == -1)
            inter_x-= 1;
        if(is_wall(map,inter_x, inter_y) == true)
        {
            coord.hit_wall = 1;
            coord.x = nextX;
            coord.y = nextY;
            break;   
        }
        nextX += dx;
        nextY += dy;         
    }
    if (!coord.hit_wall)
        coord.distance = __FLT_MAX__;
    else
        coord.distance = calculate_distance(map.player_pos.x,map.player_pos.y, coord.x, coord.y);
    return coord;

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
    return coord;
}

t_coord horizontal_intersection(t_map map, float angle)
{
    t_coord coord;
    float dx;
    float dy;
    float inter_x;
    float inter_y;

    coord = get_f_horizontal_intersection(map, angle, &dx, &dy);
    coord.hit_wall = 0;
    float nextX = coord.x;
    float nextY = coord.y;

    while(nextX >= 0 && nextY >= 0 && nextX <= map.max_width*60 && nextY <= map.map_height*60)
    {
        inter_x = nextX;
        inter_y = nextY;
        if(is_up(angle) == 1)
            inter_y -= 1;
        if(is_wall(map,inter_x, inter_y) == true)
        {
            coord.hit_wall = 1;
            coord.x = nextX;
            coord.y = nextY;
            break;   
        }
        nextX += dx;
        nextY += dy;         
    }

    if (!coord.hit_wall)
        coord.distance =__FLT_MAX__;
    else
        coord.distance = calculate_distance(map.player_pos.x,map.player_pos.y, coord.x, coord.y);
    return coord;
}

void get_fov(t_map *map,float start_angle, float end_angle, int flag)
{
    t_coord pos;
    t_coord horizontal_coord;
    
    map->rays = NULL;
    pos.x = map->player_pos.x *FACTOR;
    pos.y = map->player_pos.y*FACTOR;
    t_coord vertical_coord;
    while(start_angle <= end_angle)
    {
        horizontal_coord = horizontal_intersection(*map, normalize(start_angle));
        vertical_coord = vertical_intersection(*map, normalize(start_angle));
        if ((vertical_coord.distance >= horizontal_coord.distance))
        {
            if(flag ==1)
                DDA(map,&pos,horizontal_coord.x *FACTOR,horizontal_coord.y*FACTOR, 0x00ff00);
            else
                ft_lstadd_back(&map->rays,ft_lstnew(ray_data(*map,start_angle,1,horizontal_coord)));
        }
        else
        {
            if(flag ==1)
                DDA(map,&pos,vertical_coord.x*FACTOR ,vertical_coord.y*FACTOR,0x00ff00);
            else
                ft_lstadd_back(&map->rays,ft_lstnew(ray_data(*map,start_angle,0,vertical_coord)));
        }
       start_angle += ANGLE_FOV  /(float)(map->max_width * 60);
    }
}