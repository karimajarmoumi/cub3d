/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:50:20 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/17 20:32:50 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void check_player_symbol(char character, t_player *player, int x, t_map *map)
{
    if (character == PLAYER_W  || character ==  PLAYER_E || character == PLAYER_S || character == PLAYER_N)
    {
        player->player_symbol= character;
        player->flag_on = 1;
        player->count_player++;
        map->player_pos.x = x;
        map->player_pos.y = map->map_height;
    }
    if (character != WALL && character != EMPTY && character != PLAYER_W && character !=PLAYER_E &&
            character != PLAYER_S && character!=PLAYER_N && character != SPACE)
        print_error("wrong character");
}
void check_player(t_player *player,char *line, t_map *map)
 {
    int i;
  
    i = 0;
    if(!ft_strcmp(line,""))
        print_error("map invalid");
    while(line && line[i])
    {
         if (player->flag_on == 0)
             check_player_symbol(line[i], player, i,map);
         else
         {
            if (line[i] == player->player_symbol)
                player->count_player++;
            if(player->count_player > 1)
                print_error("there is an error in counting player");
            if ((line[i] != WALL && line[i] != EMPTY && line[i]!= player->player_symbol && line[i] != SPACE))
                print_error("wrong character");
        }
        i++;
    }
 }
