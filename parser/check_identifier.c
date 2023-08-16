/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/16 10:53:24 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char **split_identifier(char *line,char **key_value,int *identifier)
{
    key_value = ft_split(line, ' ');
    if(is_identifier(key_value[0]) == 1)
    {
        *identifier = 1;
       return key_value;
    }
    return NULL;
}

int is_identifier(char *key_value)
{
    if(!ft_strcmp(key_value,"NO"))
        return 1;
    else if(!ft_strcmp(key_value, "SO"))
        return 1;
    else if(!ft_strcmp(key_value, "WE"))
        return 1;
    else if(!ft_strcmp(key_value, "EA"))
        return 1;
    else if(!ft_strcmp(key_value, "F"))
        return 1;
    else if(!ft_strcmp(key_value, "C"))
        return 1;
    return 0;
}

void  affect_value(t_args **arg,char *key,char *value)
{
    if(key)
    {
        *arg = malloc(sizeof(t_args));
        (*arg)->key = ft_strdup(key);
        (*arg)->flag = 0;
    }
    else
        (*arg)->value = ft_strdup(value);
}

int rgb_to_int(int red, int green,int blue)
{
    int count;
    count = (red << 16) + (green << 8) + blue;
    return count;
}
void store_color_value(int *store_color, char *red, char *green, char *blue)
{
        int num1;
        int num2;
        int num3;
        
        num1 = ft_atoi(red);
        num2 = ft_atoi(green);
        num3 = ft_atoi(blue);
        *store_color = rgb_to_int(num1, num2, num3);
}
void check_color_rang(char **key_value, t_map *map)
{
    char **range;
    int num;
    int i;
    int len;
    
    len = ft_strlen(key_value[1]);
    i = 0;
    
    if(!ft_strcmp(key_value[0], "F")|| !ft_strcmp(key_value[0], "C"))
       {
            range = ft_split(key_value[1], ',');
            if(!ft_isdigit(key_value[1][len -1]) || count_words(range) != 3)
                    print_error("error in range color"); 
                while(range[i])
                {
                    if(i >= 3) 
                        print_error("these is not a RGB forme");
                    num = ft_atoi(range[i]);
                    if(num < MIN_RANGE ||  num > MAX_RANGE)
                        print_error("error in range color");
                    i++;
                }
                if(!ft_strcmp(key_value[0],"F"))
                    store_color_value(&(map->floor_color), range[0],range[1],range[2]);
                else if(!ft_strcmp(key_value[0], "C"))
                    store_color_value(&(map->ceiling_color), range[0],range[1],range[2]);
               
       }
}

void  check_identifier(char *line, t_map *map, int *count)
{
    char **key_value;
    int   i;
    int   is_identifier;

    i = 0;
    *count = 0;
    key_value = NULL;
    is_identifier = 0;
    key_value = split_identifier(line, key_value, &is_identifier);
    if (is_identifier == 1)
    {
        if(count_words(key_value) != 2)
              print_error("identifier doesn't work as expected");
            while(map->args[i] && map->args[i]->key)
            {
                if(!strcmp(key_value[0],map->args[i]->key))
                {
                    map->args[i]->flag++;
                    affect_value(&(map->args[0]), NULL, key_value[1]);
                    check_color_rang(key_value,map);
                  
                }
                if(map->args[i]->flag==1)
                    (*count)++;
                if(map->args[i]->flag > 1)
                    print_error("a path is duplicated");
                i++;
            }
    }
}