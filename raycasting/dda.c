/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/25 19:46:00 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
void DDA(t_map *map,t_coord *pos , int target_x, int target_y)
{
    int dx;
    int dy;
    float Xin=0;
    float Yin =0;
    int steps;
    int i = 0;
    float x ;
    float y ;

    dx = (target_x) - pos->x;
    dy = (target_y) - pos->y;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    Xin = dx /(float)steps;
    Yin = dy /(float)steps;
    x = pos->x;
    y = pos->y;
    while(i <= steps)
    {
        my_mlx_pixel_put(map->data, x, y, 0x00ff00);
        x += Xin ;
        y += Yin  ;
        i++;  
    }
}