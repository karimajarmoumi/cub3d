/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:27:38 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/13 20:37:36 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (j + 1));
	if (ptr == NULL)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	find_space_pos(char *str, int *key_end_pos)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == 9)
		{
			if (flag == 0)
			{
				*key_end_pos = i;
				flag = 1;
			}
		}
		else if (flag == 1)
			return (i - 1);
		i++;
	}
	*key_end_pos = i;
	return (i);
}

char	*skip_spaces(char *string)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(string) - 1;
	i = len;
	while (string[len])
	{
		if (string[len] == ' ' || string[len] == 9)
			len--;
		else
			break ;
	}
	if (len == i)
		return (ft_strdup(string));
	str = malloc(sizeof(char) * (len + 2));
	i = 0;
	while (len >= 0)
	{
		str[i] = string[i];
		i++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

void	separate_two_words(char *str, char **arg1, char **arg2)
{
	int	i;
	int	start_value;
	int	key_end;
	int	len;

	start_value = 0;
	i = 0;
	len = 0;
	start_value = find_space_pos(str, &key_end);
	*arg1 = malloc(sizeof(char) * (key_end + 1));
	if (str)
		len = ft_strlen(str);
	while (i < key_end)
	{
		arg1[0][i] = str[i];
		i++;
	}
	arg1[0][i] = '\0';
	if (i == len)
		*arg2 = NULL;
	else
	{
		*arg2 = skip_spaces(&str[start_value + 1]);
	}
}
