/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:49:52 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/02 11:49:53 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int is_up(float angle)
{
    if(angle >= M_PI)
        return 1;
    return -1;
}
int is_right(float angle)
{
    if(angle > 3 * M_PI / 2 || angle  < M_PI / 2)
        return 1;
    return -1;
}


t_ray* ray_data (t_map map,float x, float y, float distance)
{
    t_ray *ray =NULL;
    ray = malloc(sizeof(t_ray));
    ray->x = x;
    ray->y = y;
    ray->projection_wall = (FRAME_HEIGHT * ((map.max_width*FRAME_WIDTH /2) / tan(FOV / 2)))/distance;
    return ray;
}


void display_list(t_list *list)
{      
    t_ray *ray;      
    while (list)
    {
        printf("ghjkl\n");
        ray = (t_ray*)list->content;
        printf("distance%f \n",ray->projection_wall);
        list=list->next; 
    }
}
