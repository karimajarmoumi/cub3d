/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 12:18:23 by kjarmoum         ###   ########.fr       */
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
    while(nbyt > 0)
    {
        if(i == 0)
            line = ft_strdup("");
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
void  affect_value(t_args **arg,char *key,char *value)
{
    if(key)
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
    player->map_begin = 0;
    map->player_pos.x = -1;
    map->player_pos.y = -1;
    map->args = malloc(sizeof(t_args*)*7);
    affect_value(&(map->args[0]),"NO",NULL);
    affect_value(&(map->args[1]),"SO",NULL);
    affect_value(&(map->args[2]),"WE",NULL);
    affect_value(&(map->args[3]),"EA",NULL);
    affect_value(&(map->args[4]),"F",NULL);
    affect_value(&(map->args[5]),"C",NULL);
    map->args[6]=NULL;   
    map->map_height = 0;
    map-> total_height = 0;
}
void check_color_rang(char **key_value)
{
    char **range;
    int num;
    int i;
    int len =ft_strlen(key_value[1]);
    
    i = 0;
    if(!ft_strcmp(key_value[0], "F")|| !ft_strcmp(key_value[0], "C"))
       {
            range = ft_split(key_value[1],',');
            if(!ft_isdigit(key_value[1][len -1]))
                print_error("error in range color"); 
            if(count_words(range) == 3)
            {
                while(range[i])
                {
                    if(i >= 3) 
                        print_error("these is not a RGB forme");
                    num = ft_atoi(range[i]);
                    if(num < MIN_RANGE ||  num >MAX_RANGE)
                        print_error("error in range color");
                    i++;
                }
            }
            else
                print_error("error in range color");
       }
}

void  check_identifier(char *line, t_map *map,int *count)
{
    char **key_value;
    int   i;

    i = 0;
    *count = 0;
    if (line && line[i] != 10)
    {
        key_value = ft_split(line,' ');
        if(count_words(key_value) == 2)
        {
            while(map->args[i] && map->args[i]->key)
            {
                if(!strcmp(key_value[0],map->args[i]->key))
                {
                    map->args[i]->flag++;
                    affect_value(&(map->args[0]),NULL,key_value[1]);
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
}

void readMap(char *fileName, t_map *map)
{
    int         fd;
    int         count;
    char        *line;
    t_player    player;

    count = 0;
    init(&player, map);
    line = ft_strdup("");
    fd = open (fileName, O_RDONLY);
    while (line)
    {
        ft_free(line);
          printf("%d\n",count);
        line = getLine(fd);
        if(count == 6 && ft_strcmp(line,""))
            player.map_begin = 1;
        if(count < 6)
            check_identifier(line, map, &count);
        else if(count == 6 && player.map_begin == 1)
        {
            check_player(&player, line, map);
            map->map_height++;
        }
        map->total_height++;
    }
  
    ft_free(line);
    close(fd);
    if (count < 6)
        print_error("there is a problem with identifier");
    map->map_height--;
    if(!map->map_height)
        print_error("there is no map");
    fillArray(map, &player,fileName);
    //displayArray(map->map);
    flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
    //displayArray(player.map_cpy);
}


