/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 15:48:40 by kjarmoum         ###   ########.fr       */
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


void map_cpy(char *line, t_player *player,int *i,int height)
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


void fillArray(t_map *map,t_player *player, char *fileName)
{
    char *line;
    int i;
    int fd;
    int j =0;

    fd = open (fileName,O_RDONLY);
    i = 0;
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
            map_cpy(line,player,&j,map->height);

           i++;
       }
   }
    map->map[i] =  NULL;
    player->map_cpy[j] =  NULL;

}


int main(int ac, char **av)
{
    if (ac == 2)
    {
        t_map map;
        if (check_extension(av[1]) == true)
            readMap(av[1],&map);
        else
            print_error("wrong extension");
        printf("woooow\n");
    }
    else
        write(1,"Please enter a file name\n",25);
}
