/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 18:32:00 by kjarmoum         ###   ########.fr       */
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
void  affect_value(t_args **arg,char *key)
{
    *arg = malloc(sizeof(t_args));
    (*arg)->key=ft_strdup(key);
    (*arg)->flag = 0;
}
void init(t_player *player, t_map *map)
{
    player->flag_on = 0;
    player->count_player = 0 ;
    map->args = malloc(sizeof(t_args*)*7);
    affect_value(&(map->args[0]),"NO");
    affect_value(&(map->args[1]),"SO");
    affect_value(&(map->args[2]),"WE");
    affect_value(&(map->args[3]),"EA");
    affect_value(&(map->args[4]),"F");
    affect_value(&(map->args[5]),"C");
    map->args[6]=NULL;   
    map->height = 0;
}

void check_textures(char *line, t_map *map,int *count)
{
    char *key;
    char *tmp;
    int i;
    *count = 0;
    i = 0;
    key = ft_strdup("");
    while(line && ft_isalpha(line[i]))
    {
        tmp =key;
        key=ft_charjoin(key,line[i]);
        ft_free(tmp);
        i++;
    }
    i = 0;
    while(map->args[i] && map->args[i]->key)
    {
        if(!strcmp(key,map->args[i]->key))
            map->args[i]->flag++;
        if(map->args[i]->flag==1)
            (*count)++;
        if(map->args[i]->flag > 1)
            print_error("a path is duplicated");
        i++;
    }
}

void readMap(char *fileName,t_map *map)
{
    char        *line;
    int         fd;
    t_player    player;
    int count = 0;

    init(&player, map);
    line = ft_strdup("");
    fd = open (fileName,O_RDONLY);
    while(line)
    {
        ft_free(line);
        line = getLine(fd);

        if(count < 6)
            check_textures(line,map,&count);
        else if(count == 6)
             check_player(&player, line, map);
        map->height++;
    }

    if(count < 6)
        print_error("a path is missing");
    ft_free(line);
    close(fd);
    map->height--;

    fillArray(map, &player,fileName);
    // check_errors()
    displayArray(player.map_cpy);
   flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
   displayArray(player.map_cpy);

}


