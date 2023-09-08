/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:05 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/07 19:14:49 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void line_of_spaces(t_player *player, int *i, char *line)
{
    int len;

    len = ft_strlen(line);
    player->map_cpy[*i] = malloc(sizeof(char) * (len + 3));
    ft_memset(player->map_cpy[*i], ' ', len+2);
    player->map_cpy[*i][len + 2] = '\0';
    (*i)++;
    //FREE
}

void add_spaces_to_line(t_player *player, int *i, char *line)
{
    char *str;
    char *tmp;

    str = ft_strjoin(" ",line);
    tmp = str;
    str = ft_strjoin(str," ");
    ft_free(tmp);
    player->map_cpy[*i] = str;
    //i free here if there is a seg 
    (*i)++;
}

void map_cpy(char *line, t_player *player, int *i, int height)
{
    if(*i == 0)
    {
       line_of_spaces(player, i, line);
       add_spaces_to_line(player, i, line);
    }
    else if (*i == height)
    {
       add_spaces_to_line(player, i, line);
       line_of_spaces(player, i, line);
    }
    else
       add_spaces_to_line(player, i, line);
}
void display_list(t_list *list)
{
    char *line;

    while (list)
    {
        line = (char*)list->content;
       // printf("liine%s\n", line);
        list = list->next; 
    }
}
void displayArray(char **str)
{
    int i =0;
    int j;

    while(str[i])
    {
        j =0;
        printf("|");
        while(str[i][j])
        {
            printf("%c",str[i][j]);
            j++;
        }
        printf("|\n");
        i++;
    }
}
void fillArray(t_map *map, t_player *player)
{
    int i;
    int j;
    char *line;
    t_list *tmp;

    tmp = player->store_map;
    i = 0;
    j = 0;
    map->map = malloc(sizeof(char*) * (map->map_height + 1));
   // player->map_cpy = malloc(sizeof(char*) * (map->map_height + 3));
    while(tmp)
    {
        line = (char*)tmp->content;
        //printf("===%d\n",ft_strlen(line));
        map->map[i] = ft_strdup(line);
      //  map_cpy(line, player, &j, map->map_height);
       // j++;
       tmp = tmp->next;
        i++;
    }
    map->map[i] =  NULL;
    //displayArray(map->map);
   //exit(1);
   // player->map_cpy[j] =  NULL;
}