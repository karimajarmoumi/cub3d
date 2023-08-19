/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/19 12:20:37 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void DDA(t_map *map,t_data *data, int target_x, int target_y)
{
    int dx;
    int dy;
    float Xin=0;
    float Yin =0;
    int steps;
    int i =0;
    float x ;
    float y ;

    dx = target_x * 60   - map->player_pos.x * 60;
    dy = target_y * 60 - map->player_pos.y * 60 ;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    Xin = dx /(float)steps;
    Yin = dy /(float)steps;
    x = map->player_pos.x*60;
    y = map->player_pos.y*60;
    while(i <= steps)
    {
        mlx_pixel_put(data-> mlx,data->win,x + 60,y,0xFFFF66);
        x += Xin;
        y += Yin;
        i++;  
    }
}