/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/14 20:32:31 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void first_line(t_player *player, int *i, char *line)
{
    int len;

    len = ft_strlen(line);
    player->map_cpy[*i] = malloc(sizeof(char) * (len + 3));
    ft_memset(player->map_cpy[*i], ' ', len+2);
    player->map_cpy[*i][len + 2] = '\0';
    (*i)++;
}
void body_map(t_player *player, int *i, char *line)
{
    char *str;
    char *tmp;

    str = ft_strjoin(" ",line);
    tmp = str;
    str = ft_strjoin(str," ");
    ft_free(tmp);
    player->map_cpy[*i] = str;
    (*i)++;
}
void map_cpy(char *line, t_player *player, int *i, int height)
{
    if(*i == 0)
    {
       first_line(player, i, line);
       body_map(player, i, line);
    }
    else if (*i == height)
    {
       body_map(player, i, line);
       first_line(player, i, line);
    }
    else
       body_map(player, i, line);
}
int is_line_ofMap(char *line)
{
    char    *map_caracters;

    map_caracters = "10NSEW";
    if (ft_strchr_str(line, map_caracters))
        return (0);
    return (1);
}
void fillArray(t_map *map, t_player *player, char *fileName)
{
    char *line;
    int i;
    int fd;
    int j;

    i = 0;
    j = 0;
    fd = open (fileName,O_RDONLY);
    line = ft_strdup("");
    map->map = malloc(sizeof(char*) * (map->height + 1));
    player->map_cpy = malloc(sizeof(char*) * (map->height + 3));
    while(line)
    {
       ft_free(line);
       line = getLine(fd);
       if(line)
       {
            map->map[i] = ft_strdup(line);
            // if (is_line_ofMap(line) && ft_strlen(line))
            // {
                //printf(" len %d |%d %s|\n", ft_strlen(line), is_line_ofMap(line), line);
                map_cpy(line, player, &j, map->height);
                // exit(1);
            // }
            i++;
       }
    }
    map->map[i] =  NULL;
    player->map_cpy[j] =  NULL;
}
int main(int ac, char **av)
{
    t_map   map;
    
    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
            readMap(av[1],&map);
        else
            print_error("wrong extension");
            
        printf("wwwwoooow\n");
    }
    else
        write(1,"Please enter a file name\n",25);
}
