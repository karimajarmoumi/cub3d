/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:51:24 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/09/07 21:55:34 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void init_texture(t_map *map, int id_t, char *path_image)
{
    map->textures[id_t].mlx = map->data->mlx;
    map->textures[id_t].win = map->data->win;
    map->textures[id_t].img = mlx_xpm_file_to_image(map->textures[id_t].mlx, path_image
    , &map->textures[id_t].width, &map->textures[id_t].height);
    map->textures[id_t].addr = mlx_get_data_addr(map->textures[id_t].img, &map->textures[id_t].bits_per_pixel, 
        &map->textures[id_t].line_length, &map->textures[id_t].endian);
    if (!map->textures[id_t].img || !map->textures[id_t].addr)
        print_error("** ERROR IN WALL TEXTURE");
}

void init_textures(t_map *map)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (map->args[i]->key[0] == 'N')
            init_texture(map, 0, map->args[i]->value);
        else  if (map->args[i]->key[0] == 'S')
            init_texture(map, 1, map->args[i]->value);
        else  if (map->args[i]->key[0] == 'E')
            init_texture(map, 2, map->args[i]->value);
        else
            init_texture(map, 3, map->args[i]->value);
        i++;   
    }
}