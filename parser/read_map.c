/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:35:57 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/12 21:40:37 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	store_map_mesurer(t_map *map, char *line)
{
	int	current_width;

	map->map_height++;
	if (line)
	{
		current_width = ft_strlen(line);
		if (map->max_width < current_width)
			map->max_width = current_width;
	}
}

void	read_map(int fd, t_map *map, t_player *player)
{
	char	*line;
	t_list	*tmp;
	int		flag;

	line = get_line(fd);
	flag = 0;
	player->store_map = NULL;
	tmp = player->store_map;
	while (line)
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
	if (player->count_player == 0)
		print_error("there is no player");
	if (!map->map_height)
		print_error("there is no map");
}
