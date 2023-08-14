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

    line = NULL;
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
void  affect_value(t_args **arg,char *key,char *value,int flag)
{
    if(flag == 1)
    {
        *arg = malloc(sizeof(t_args));
        (*arg)->key=ft_strdup(key);
        (*arg)->flag = 0;
    }
    else
        (*arg)->value=ft_strdup(value);
}
void init(t_player *player, t_map *map)
{
    player->flag_on = 0;
    player->count_player = 0 ;
    map->args = malloc(sizeof(t_args*)*7);
    affect_value(&(map->args[0]),"NO",NULL,1);
    affect_value(&(map->args[1]),"SO",NULL,1);
    affect_value(&(map->args[2]),"WE",NULL,1);
    affect_value(&(map->args[3]),"EA",NULL,1);
    affect_value(&(map->args[4]),"F",NULL,1);
    affect_value(&(map->args[5]),"C",NULL,1);
    map->args[6]=NULL;   
    map->height = 0;
}
void check_color_rang(char **key_value)
{
    char **range;
    int num;
    int i;
    i = 0;
    if(!ft_strcmp(key_value[0], "F")|| !ft_strcmp(key_value[0], "C"))
       {
            range = ft_split(key_value[1],',');
            while(range[i])
            {
                num = ft_atoi(range[i]);
                if(num < MIN_RANGE ||  num >MAX_RANGE)
                    print_error("range error");
                i++;
            }
       }
}
void  check_identifier(char *line, t_map *map,int *count)
{
    char **key_value;
    int   i;

    *count = 0;
    key_value = ft_split(line,' ');
    i = 0;
    if(key_value && key_value[0] && key_value[1])
    {
        while(map->args[i] && map->args[i]->key)
        {
            if(!strcmp(key_value[0],map->args[i]->key))
            {
                map->args[i]->flag++;
                affect_value(&(map->args[0]),NULL,key_value[1],0);
                check_color_rang(key_value);
            }
            if(map->args[i]->flag==1)
                (*count)++;
            if(map->args[i]->flag > 1)
                print_error("a path is duplicated");
            i++;
        }
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
            check_identifier(line,map,&count);
        else if(count == 6)
             check_player(&player, line, map);
        map->height++;
    } 
    ft_free(line);
    close(fd);
    if(count < 6)
        print_error("there is a problem with identifier");
    map->height--;
    fillArray(map, &player,fileName);
    flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
   // displayArray(player.map_cpy);
}


