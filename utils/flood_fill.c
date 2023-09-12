/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:01:25 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/11 15:59:06 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void flood_fill(t_player *player, int pos_y, int pos_x)
{
    if (player->map_cpy[pos_y][pos_x] == WALL )
        return ;
    if (player->map_cpy[pos_y][pos_x] == SPACE)
        print_error("map invalid");
    player->map_cpy[pos_y][pos_x] = '1';
    flood_fill(player, pos_y, pos_x + 1);
    flood_fill(player, pos_y, pos_x - 1);
    flood_fill(player, pos_y + 1, pos_x);
    flood_fill(player, pos_y - 1, pos_x); 
}
