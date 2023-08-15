/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:01:25 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 16:01:16 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void flood_fill(t_player *player, int pos_y, int pos_x)
{
     if (player->map_cpy[pos_y][pos_x] == WALL || player->map_cpy[pos_y][pos_x]  == 'F')
        return ;

    if (player->map_cpy[pos_y][pos_x] == SPACE )
        print_error("map invalid");
    player->map_cpy[pos_y][pos_x] = '1';
    flood_fill(player, pos_y, pos_x + 1);
    flood_fill(player, pos_y, pos_x - 1);
    flood_fill(player, pos_y + 1, pos_x);
    flood_fill(player, pos_y - 1, pos_x);
}
