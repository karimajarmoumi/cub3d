/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrender_by_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:58:13 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/11 19:29:04 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../cub3D.h"

size_t    get_max_line_len(char **map)
{
    size_t    max;
    int    i;

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

void    make_map_rectangle(char **map)
{
    size_t        max_len;
    int        i;
    char    *tmp;

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

bool    check_map(char **map)
{
    int    is_valid;
    int     i;
    int     j;

    make_map_rectangle(map);
    is_valid = 1;
    i = 0;
    while (map[i] && is_valid)
    {
        j = 0;
        while (map[i][j] && is_valid)
        {
            if (ft_strchr("NEWS0", map[i][j]))
            {
                is_valid = is_valid && i && j && map[i + 1] && map[i][j + 1];
                is_valid = is_valid && ft_strchr("NEWS10", map[i + 1][j]) && ft_strchr("NEWS10", map[i - 1][j]);
                is_valid = is_valid && ft_strchr("NEWS10", map[i][j + 1]) && ft_strchr("NEWS10", map[i][j - 1]);
            }
            else
                is_valid = !!ft_strchr("1 ", map[i][j]);
            j++;
        }
        i++;
    }
    return (is_valid);
}