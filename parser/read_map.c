/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/11 18:16:40 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char *getLine(int fd)
{
    char character;
    int nbyt ;
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
    player->count_player =0 ;
    map->height = 0;
}
void readMap(char *fileName,t_map *map)
{
    char *line;
    int fd;
    t_map *tmp_map;
    t_player player;

    init(&player, map);
    tmp_map = map;
    line = ft_strdup("");
    fd = open (fileName,O_RDONLY);
    while(line)
    {
          ft_free(line);
          line = getLine(fd);
          check_player(&player,line,map->height);
          map->height++;
    }
    ft_free(line);
    close(fd);
    tmp_map->height--;
    tmp_map->map = malloc(sizeof(char*)*( tmp_map->height + 1));
    fillArray(tmp_map->map ,fileName);
   //displayArray(map->map);
}
