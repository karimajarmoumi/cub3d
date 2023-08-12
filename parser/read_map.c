/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 16:45:59 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char *getLine(int fd)
{
    char character;
    int nbyt;
    int i = 0;
    char *tmp;
    char *line;

    line =NULL;
    nbyt = read(fd,&character,1);
    while(nbyt >0)
    {
        if(i == 0)
            line=ft_strdup("");
        if(character =='\n' || character=='\0')
             return line;
        tmp = line;
        line = ft_charjoin(line,character);
        ft_free(tmp);
        nbyt = read(fd,&character,1);
        i = 1;
    }
    return line;
}
void init(t_player *player, t_map *map)
{
    player->flag_on = 0;
    player->count_player = 0 ;
    map->height = 0;
}

//flood

void flood_fill(t_player *player, int pos_y, int pos_x)
{


    if (pos_y < 0 || pos_x < 0 || pos_y >= 3|| pos_x >=10 || player->map_cpy[pos_y][pos_x] == WALL || player->map_cpy[pos_y][pos_x] == 'F' )
        return ;

    if (player->map_cpy[pos_y][pos_x] == SPACE )
    {
        printf("heere|%c|\n",player->map_cpy[pos_y][pos_x]);
        player->map_cpy[pos_y][pos_x] = 'F';
        return;
    }
    flood_fill(player, pos_y + 1, pos_x);
    flood_fill(player, pos_y - 1, pos_x);
    flood_fill(player, pos_y, pos_x + 1);
    flood_fill(player, pos_y, pos_x - 1);
}

void readMap(char *fileName,t_map *map)
{
    char        *line;
    int         fd;
    t_player    player;

    init(&player, map);
    line = ft_strdup("");
    fd = open (fileName,O_RDONLY);
    while(line)
    {
        ft_free(line);
        line = getLine(fd);
        //check_textures(line);
        check_player(&player, line, map);
        map->height++;
    }
    ft_free(line);
    close(fd);
    map->height--;

    fillArray(map, &player,fileName);
    // check_errors()
    displayArray(player.map_cpy);
   flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
   displayArray(player.map_cpy);

}


