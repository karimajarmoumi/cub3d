/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:15:17 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/06 21:15:18 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float calculate_distance(float x1, float y1, float x2, float y2)
{
    float   distance;

    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return distance;
}
