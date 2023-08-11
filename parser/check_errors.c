/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:50:20 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/09 11:50:21 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void check_player_symbol(char map,t_player *player)
{
        if(map == PLAYER_W  || map ==  PLAYER_E || map == PLAYER_S || map == PLAYER_N)
        {
            player->player_symbol= map;
            player->flag_on = 1;
            player->count_player++;
        }
        if(map !=WALL && map != EMPTY && map !=PLAYER_W && map !=PLAYER_E &&
             map != PLAYER_S && map!=PLAYER_N && map != SPACE)
            print_error("wrong character");
}
void check_player(char map,t_player *player)
 {
    if(player->flag_on == 0)
        check_player_symbol(map,player);
    else
    {
        if(map == player->player_symbol)
            player->count_player++;
        if(player ->count_player > 1 ||  (map != WALL && map != EMPTY &&
             map!= player ->player_symbol && map != SPACE))
             print_error("wrong character or you duplicated player");
    } 
 }

// void   check_errors_space(t_map mapp, int height, int width,int index)
// {
//     int len = ft_strlen(mapp.map[index]);
//     if(width==len-1)
//         index++;
    
//     if (mapp.map && (height < 0 || width <0 || height >=mapp.height || width >= len))
//         return ;
//     if(mapp.map[height][width] == SPACE)
//     {
//         if(mapp.map[height][width +1]&&(mapp.map[height][width +1] != SPACE || mapp.map[height][width +1]!=WALL))
//             print_error("Spaces is not surrender by walls");
//     }
//     check_errors_space(mapp,height, width+1,index);
//     check_errors_space(mapp,height, width-1,index);
//     check_errors_space(mapp,height-1, width,index);
//     check_errors_space(mapp,height+1, width,index);
// }

void check_errors(t_map mapp)
{
    char **tmp_map;
    int i = 0;
    int len ;
    int j;
    t_player player;
    tmp_map = mapp.map;
    //init struct player
  
}

