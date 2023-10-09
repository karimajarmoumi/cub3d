/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:59:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_player	*init_player(t_player *player)
{
	player->flag_on = 0;
	player->count_player = 0;
	player->map_begin = 0;
	return (player);
}

t_position	init_p(t_position *player)
{
	player->x = -1;
	player->y = -1;
	player->player_rotation = 0;
	player->player_moves = 0;
	player->move_speed = 6;
	return (*player);
}

void	init_map(t_player *player, t_map *map)
{
	player = init_player(player);
	map->player_pos = init_p(&map->player_pos);
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->data = malloc(sizeof(t_data));
	map->args = malloc(sizeof(t_args *) * 7);
	map->textures = malloc(sizeof(t_data) * 4);
	affect_value(&(map->args[0]), "NO", NULL);
	affect_value(&(map->args[1]), "SO", NULL);
	affect_value(&(map->args[2]), "WE", NULL);
	affect_value(&(map->args[3]), "EA", NULL);
	affect_value(&(map->args[4]), "F", NULL);
	affect_value(&(map->args[5]), "C", NULL);
	map->args[6] = NULL;
	map->map_height = 0;
	map->max_width = 0;
}

void	get_configs(int fd, t_map *map)
{
	char	*line;
	int		count;

	line = get_line(fd);
	count = 0;
	while (line)
	{
		if (ft_strcmp(line, ""))
			check_identifier(line, map, &count);
		if (count >= 6)
			break ;
		ft_free(line);
		line = get_line(fd);
	}
	ft_free(line);
	if (count < 6)
		print_error("there is a problem with identifier");
}

void	parse(char *file_name, t_map *map)
{
	int			fd;
	t_player	player;

	init_map(&player, map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error("Can't open file");
	get_configs(fd, map);
	read_map(fd, map, &player);
	fill_map(map, &player);
	if (!check_map(map->map))
		print_error("MAP invalid");
	ft_free_list(player.store_map);
}
