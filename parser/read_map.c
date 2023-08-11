/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/09 09:59:50 by kel-baam         ###   ########.fr       */
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

void readMap(char *fileName,t_map *map)
{
    char *line;
    int height;
    int fd;
    t_map *tmp_map;

    tmp_map = map;
    height = 0;
    line = ft_strdup("");
    fd = open (fileName,O_RDONLY);
    while(line)
    {
          ft_free(line);
          line = getLine(fd);
          height++;
    }

    ft_free(line);
    close(fd);
    tmp_map->height= height - 1;
    tmp_map->map = malloc(sizeof(char*)*( tmp_map->height + 1));
    fillArray(tmp_map->map ,fileName);
   check_errors(*tmp_map);
   //displayArray(map->map);
}
