/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical_intersection.c.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:43:12 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/08 14:32:31 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
    coord.hit_wall = 0;
    return  (coord);
}
int check_vertical_wall(t_map map,t_coord next, float angle, t_coord *coord)
{
    t_coord inter;
    inter.x = next.x;
    inter.y = next.y;
    if(is_right(angle) == -1)
            inter.x-= 1;
    if(is_wall(map,inter.x, inter.y,0) == true)
    {
        coord->hit_wall = 1;
        coord->x = next.x;
        coord->y = next.y;
        return (1);   
    }
    return (0);
}

t_coord vertical_intersection(t_map map,float angle)
{
    t_coord coord;
    t_coord next;
    float dx;
    float dy;
    
    coord =  get_f_vertical_intersection(map, angle, &dx, &dy);
    next.x = coord.x;
    next.y = coord.y;
    while(next.x >= 0 &&next.y >= 0 && next.x <= map.max_width*FRAME_WIDTH &&next.y <= map.map_height*FRAME_HEIGHT)
    {
        if(check_vertical_wall(map,next,angle,&coord) == 1)
            break;
        next.x += dx;
        next.y += dy;        
    }
    if (!coord.hit_wall)
        coord.distance = __FLT_MAX__;
    else
        coord.distance = calculate_distance(map.player_pos.x,map.player_pos.y, coord.x, coord.y);
    return (coord);
}

void get_fov(t_map *map,float start_angle, float end_angle)
{
    t_coord horizontal_coord;
    
    map->rays = NULL;
    t_coord vertical_coord;
    while(start_angle <= end_angle)
    {
        horizontal_coord = horizontal_intersection(*map, normalize(start_angle));
        vertical_coord = vertical_intersection(*map, normalize(start_angle));
        if ((vertical_coord.distance >= horizontal_coord.distance))

            ft_lstadd_back(&map->rays,ft_lstnew(ray_data(map,normalize(start_angle),1,horizontal_coord)));
        else
            ft_lstadd_back(&map->rays,ft_lstnew(ray_data(map,normalize(start_angle),0,vertical_coord)));
       start_angle += ANGLE_FOV  /(float)WINDOW_WIDTH;
    }
}