/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:49:52 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/03 11:28:12 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int is_up(float angle)
{
    if(angle >= M_PI)
        return 1;
    return -1;
}
int is_right(float angle)
{
    if(angle > 3 * M_PI / 2 || angle  < M_PI / 2)
        return 1;
    return -1;
}


t_ray* ray_data (t_map map,float angle, int flag, t_coord inter_type)
{
    t_ray *ray =NULL; 
    
    ray = malloc(sizeof(t_ray));
    ray->x = inter_type.x;
    ray->y = inter_type.y;
    ray->distance = inter_type.distance;
    ray->angle = angle;
    ray->projection_wall = (FRAME_HEIGHT * ((map.max_width*FRAME_WIDTH /2) / tan(FOV / 2)))/ray->distance;
    if(flag == 1)
        ray->hit_wall_h = 1;
    else
        ray->hit_wall_v = 1;
    return ray;
}


