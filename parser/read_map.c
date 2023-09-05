/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/05 17:56:40 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_player* init_player(t_player *player)
{
    player->flag_on = 0;
    player->count_player = 0;
    player->map_begin = 0;
    return (player);
}

t_position init_p(t_position *player)
{
    player->x = -1;
    player->y = -1;
    player->turn_x = 0;
    player->turn_y = 0;
    player->move_speed = 5;
    return (*player);
}

void init_map(t_player *player, t_map *map)
{
    player = init_player(player);
    map->player_pos = init_p(&map->player_pos);
    map->floor_color = 0;
    map->ceiling_color = 0;
    map->data= malloc(sizeof(t_data));
    map->args = malloc(sizeof(t_args*)*7);
    map->textures = malloc(sizeof(t_data) * 4);
    affect_value(&(map->args[0]),"NO",NULL);
    affect_value(&(map->args[1]),"SO",NULL);
    affect_value(&(map->args[2]),"WE",NULL);
    affect_value(&(map->args[3]),"EA",NULL);
    affect_value(&(map->args[4]),"F",NULL);
    affect_value(&(map->args[5]),"C",NULL);
    map->args[6] = NULL;   
    map->map_height = 0;
    map-> max_width = 0;
    map-> total_height = 0;
}

void store_map_mesurer(t_map *map,char *line)
{
    int current_width; 
    
    map->map_height++;
    if(line)
    {
        current_width = ft_strlen(line);
        if(map->max_width < current_width)
            map->max_width = current_width;
    }
}

void readMap(char *fileName, t_map *map)
{
    int         fd;
    int         count;
    char        *line;
    t_player    player;

    count = 0;
    init_map(&player, map);
    line = ft_strdup("");
    fd = open (fileName, O_RDONLY);
    while (line)
    {
        ft_free(line);
        line = getLine(fd);
        if(line && ft_strcmp(line,"") && !player.map_begin && count == 6)
            player.map_begin = 1;
        if(line && count < 6)
            check_identifier(line, map, &count);
        else if(count == 6 && player.map_begin == 1)
        {
            check_player(&player, line, map);
            store_map_mesurer(map,line);
        }   
        map->total_height++;
    }
    ft_free(line);
    if (count < 6)
        print_error("there is a problem with identifier");
    map->map_height--;
    if(!map->map_height)
        print_error("there is no map");
    fillArray(map, &player,fileName);
   // flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
    free_struct_args(map->args);
    free_double_ptr(player.map_cpy);
}
