/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:20:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/22 19:36:46 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
// void check_dda(int x, int y)
// {
//     int new_x;
//     int new_y;
//     int dest_y;
//     dest_y = y -1;
//     new_x = (y - dest_y )*tan(60);
    
// }
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

    dx = (target_x) - map->player_pos.x;
    dy = (target_y) - map->player_pos.y;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    Xin = dx /(float)steps;
    Yin = dy /(float)steps;
    x = map->player_pos.x;
    y = map->player_pos.y;
    //
    while(i <= steps )
    {
        my_mlx_pixel_put(data, x, y, 0x660033);
        
        x += Xin ;
        y += Yin  ;
        i++;  
    }
}