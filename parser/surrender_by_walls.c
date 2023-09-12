/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrender_by_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:58:13 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/12 22:00:29 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t	get_max_line_len(char **map)
{
	size_t	max;
	int		i;

	max = 0;
	i = 0;
	while (map[i])
	{
		if (strlen(map[i]) > max)
			max = strlen(map[i]);
		i++;
	}
	return (max);
}

void	make_map_rectangle(char **map)
{
	size_t	max_len;
	int		i;
	char	*tmp;

	max_len = get_max_line_len(map);
	i = 0;
	while (map[i])
	{
		while (strlen(map[i]) < max_len)
		{
			tmp = map[i];
			map[i] = ft_strjoin(map[i], " ");
			free(tmp);
		}
		i++;
	}
}

int	function(char **map, int i, int j, int *v_map)
{
	if (ft_strchr("NEWS0", map[i][j]))
	{
		*v_map = (*v_map && i && j && map[i + 1] && map[i][j + 1]);
		*v_map = (*v_map && ft_strchr("NEWS10", map[i + 1][j])
				&& ft_strchr("NEWS10", map[i - 1][j]));
		*v_map = (*v_map && ft_strchr("NEWS10", map[i][j + 1])
				&& ft_strchr("NEWS10", map[i][j - 1]));
	}
	else
		*v_map = !!ft_strchr("1 ", map[i][j]);
	return (*v_map);
}

bool	check_map(char **map)
{
	int	v_map;
	int	i;
	int	j;

	make_map_rectangle(map);
	v_map = 1;
	i = 0;
	while (map[i] && v_map)
	{
		j = 0;
		while (map[i][j] && v_map)
		{
			v_map = function(map, i, j, &v_map);
			j++;
		}
		i++;
	}
	return (v_map);
}
