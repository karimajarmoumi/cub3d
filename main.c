/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/16 10:46:18 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int ac, char **av)
{
    t_map   map;
   
    if (ac == 2)
    {
        if (check_extension(av[1]) == true)
        {
            readMap(av[1],&map);
	       
        }
        else
            print_error("wrong extension");
            
        printf("%d %dwwwwoooow\n",map.floor_color,map.ceiling_color);
    }
    else
        write(1,"Please enter a file name\n",25);
}
