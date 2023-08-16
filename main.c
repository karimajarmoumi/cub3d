/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/16 10:54:45 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void display_map(t_map *map)
{
    int     x;
    int     i;
    int     j;
    void	*mlx;
    void    *mlx_win;

    i = 0;
    j = 0;
    x = X;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 600, "./cub3d!"); 
    map->mlx_img_1 = mlx_xpm_file_to_image(mlx, "./textures/1.xpm", &x, &x);
    if (map)
    {
        while (map->map[i])
        {
            while (map->map[i][j])
            {
                if (map->map[i][j] == WALL)
                {
                    printf("CC\n");
                    mlx_put_image_to_window(mlx, mlx_win, map->mlx_img_1, i * X, j * X);
                }
                j++;
            }
            i++;
        }
        mlx_loop(mlx);
    }
    
}


int main(int ac, char **av)
{
    t_map   map;
    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            readMap(av[1],&map);
            display_map(&map);
        }
        else
            print_error("wrong extension");
            
        printf("%d %dwwwwoooow\n",map.floor_color,map.ceiling_color);
    }
    else
        write(1,"Please enter a file name\n",25);
}
