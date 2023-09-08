/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:15:39 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/08 22:23:26 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    check_color_rang(char *key, char *value, t_map *map)
{
    int     i;
    int     len;
    char    **range;
   
    i = 0;
    range = NULL;
    len = ft_strlen(value);
    if (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"))
    {
        range = ft_split(value, ',');
        if (check_commas(value) != 2 || count_words(range) != 3)
                print_error("this is not ab RGB format"); 
        if (!ft_strcmp(key,"F"))
            store_color_value(&(map->floor_color), range[0], range[1], range[2]);
        else if (!ft_strcmp(key, "C"))
            store_color_value(&(map->ceiling_color), range[0], range[1], range[2]);
        free_double_ptr(range);
    }
}

void check_identifier(char *line, t_map *map, int *count)
{
    int     i;
    char    *key;
    char    *value;
    
    i = 0;
    *count = 0;
    separate_two_words(line, &key, &value);
    if (is_identifier(key) == 1 && key && value)
      {
        while (map->args[i] && map->args[i]->key)
        {
            if (!strcmp(key, map->args[i]->key))
            {
                map->args[i]->flag++;
                affect_value(&(map->args[i]), NULL, value);
                check_color_rang(key,value, map);
            }
            if (map->args[i]->flag == 1)
                (*count)++;
            if (map->args[i]->flag > 1)
                print_error("a path is duplicated");
            i++;
        }
    }
    else
       print_error("is error at identifiers");
    ft_free(key);
    ft_free(value);
}