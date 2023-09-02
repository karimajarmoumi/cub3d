/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/02 11:48:51 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
void DDA(t_map *map,t_coord *pos , float target_x, float target_y)
{
    float dx;
    float dy;
    float Xin=0;
    float Yin =0;
    float steps;
    int i = 0;
    float x ;
    float y ;

    dx = (target_x) - pos->x;
    dy = (target_y) - pos->y;
    steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    
    Xin = dx /(float)steps;
    Yin = dy /(float)steps;
    x = pos->x;
    y = pos->y;
    while(i < steps && x >= 0 && y >= 0)
    {
        my_mlx_pixel_put(map->data, x, y, 0x00ff00);
        x += Xin ;
        y += Yin  ;
        i++;
    }
}