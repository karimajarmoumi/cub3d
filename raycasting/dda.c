/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/22 14:23:41 by kel-baam         ###   ########.fr       */
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
    int i = 0;
    float x ;
    float y ;

    dx = target_x   - map->player_pos.x + 30;
    dy = target_y -map->player_pos.y + 30;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    Xin = dx /(float)steps;
    Yin = dy /(float)steps;
    x = map->player_pos.x + 30;
    y = map->player_pos.y + 30;
    while(i <= steps)
    {
        mlx_pixel_put(data-> mlx,data->win,x ,y,0xFFFF66);
        x += (Xin);
        y += Yin;
        i++;  
    }
}