/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/08 14:46:13 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_player *init_player(t_player *player)
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
    player->move_speed = 6;
    return (*player);
}

void init_map(t_player *player, t_map *map)
{
    player = init_player(player);
    map->player_pos = init_p(&map->player_pos);
    map->floor_color = 0;
    map->ceiling_color = 0;
    map->data= malloc(sizeof(t_data));
    map->args = malloc(sizeof(t_args*) * 7);
    map->textures = malloc(sizeof(t_data) * 4);
    affect_value(&(map->args[0]), "NO",NULL);
    affect_value(&(map->args[1]), "SO",NULL);
    affect_value(&(map->args[2]), "WE",NULL);
    affect_value(&(map->args[3]), "EA",NULL);
    affect_value(&(map->args[4]), "F",NULL);
    affect_value(&(map->args[5]), "C",NULL);
    map->args[6] = NULL;   
    map->map_height = 0;
    map-> max_width = 0;
}

void store_map_mesurer(t_map *map, char *line)
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
void get_configs(int fd, t_map *map)
{
    char *line;
    int count;
    
    line = get_line(fd);
    count = 0;
    while(line && count < 6)
    {
        if (ft_strcmp(line,""))
            check_identifier(line, map, &count);
        ft_free(line);
        line = get_line(fd);
    }
    ft_free(line);
    if (count < 6)
        print_error("there is a problem with identifier");
}

void   read_map(int fd, t_map *map, t_player *player)
{
    char *line;
    t_list *tmp ;
    int flag;
    
    line = get_line(fd);
    flag = 0;
    player->store_map = NULL;
    tmp = player->store_map;
    while(line)
    {
        if (ft_strcmp(line, ""))
            flag = 1;
        if (flag == 1)
        {
            check_player(player, line, map);
            store_map_mesurer(map, line);
            ft_lstadd_back(&(player->store_map), ft_lstnew(ft_strdup(line)));
        }
        free(line);
        line = get_line(fd);
    }
    if(player->count_player == 0)
        print_error("there is no player");
    if(!map->map_height)
        print_error("there is no map");
}

void parse(char *file_name, t_map *map)
{
    int         fd;
    t_player    player;

    init_map(&player, map);
    fd = open (file_name, O_RDONLY);
    get_configs(fd, map);
    read_map(fd, map, &player);
    fillArray(map, &player);
   // flood_fill(&player, map->player_pos.y + 1, map->player_pos.x + 1);
    ft_free_list(player.store_map);
 //   free_struct_args(map->args);
   // free_double_ptr(player.map_cpy);
}