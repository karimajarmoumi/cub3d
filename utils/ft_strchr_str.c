/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:26:00 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/13 17:33:51 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	ft_strchr_str(char *str, char *c)
{
	int	i;

	i = 0;
	if (str && c)
	{
		while (c[i])
		{
			if (ft_strchr(str, c[i]))
				return (1);
			i++;
		}
	}
	return (0);
}