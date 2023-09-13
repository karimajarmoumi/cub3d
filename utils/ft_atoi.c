/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:47:32 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/13 19:43:05 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_sign(char c, int *i, int *sign)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	check_sign(str[i], &i, &sign);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		if (result >= 9223372036854775807 && sign == 1)
			return (-1);
	}
	if (str[i])
		print_error("error in range color");
	return (result * sign);
}
