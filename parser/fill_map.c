/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:05 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/13 20:47:33 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_map(t_map *map, t_player *player)
{
	char	*line;
	t_list	*tmp;
	int		i;

	tmp = player->store_map;
	i = 0;
	map->map = malloc(sizeof(char *) * (map->map_height + 1));
	while (tmp)
	{
		line = (char *)tmp->content;
		map->map[i] = ft_strdup(line);
		tmp = tmp->next;
		i++;
	}
	map->map[i] = NULL;
}
