/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:18:09 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	rgb_to_int(int red, int green, int blue)
{
	int	count;

	count = (red << 16) + (green << 8) + blue;
	return (count);
}

void	store_color_value(int *store_color, char *red, char *green, char *blue)
{
	int	num1;
	int	num2;
	int	num3;

	num1 = ft_atoi(red);
	num2 = ft_atoi(green);
	num3 = ft_atoi(blue);
	if (num1 < MIN_RANGE || num1 > MAX_RANGE || num2 < MIN_RANGE
		|| num2 > MAX_RANGE || num3 < MIN_RANGE || num3 > MAX_RANGE)
		print_error("error in range color");
	*store_color = rgb_to_int(num1, num2, num3);
}

void	affect_value(t_args **arg, char *key, char *value)
{
	if (key)
	{
		*arg = malloc(sizeof(t_args));
		(*arg)->key = ft_strdup(key);
		(*arg)->flag = 0;
	}
	else
	{
		if ((*arg)->flag > 1)
			print_error("a path is duplicated");
		(*arg)->value = ft_strdup(value);
	}
}

int	is_identifier(char *key_value)
{
	if (!ft_strcmp(key_value, "NO"))
		return (1);
	else if (!ft_strcmp(key_value, "SO"))
		return (1);
	else if (!ft_strcmp(key_value, "WE"))
		return (1);
	else if (!ft_strcmp(key_value, "EA"))
		return (1);
	else if (!ft_strcmp(key_value, "F"))
		return (1);
	else if (!ft_strcmp(key_value, "C"))
		return (1);
	return (0);
}
