/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/08 13:53:17 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void dda(t_map *map,t_coord *pos , float target_x, float target_y,int color)
{
    float next_x;
    float next_y;
    float dist;
    float x ;
    float y ;

    if(fabs(target_x - pos->x) > fabs(target_y - pos->y))
         dist =  fabs(target_x - pos->x);
    else
    dist = fabs(target_y - pos->y);
    
    next_x = (target_x - pos->x) /(float)dist;
    next_y = (target_y - pos->y) /(float)dist;
    x = pos->x;
    y = pos->y;
    while(dist >= 0  && x >= 0 && y >= 0)
    {
        my_mlx_pixel_put(map->data, x, y,color);
        x += next_x;
        y += next_y  ;
        dist--;
    }
}