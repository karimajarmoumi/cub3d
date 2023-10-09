/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:03:47 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/14 16:11:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	len_words(char const *s, char c)
{
	int	i;
	int	len_words;
	int	flag;

	i = 0;
	flag = 0;
	len_words = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			len_words += flag;
			flag = 0;
			while (s[i] == c)
				i++;
		}
		else
		{
			flag = 1;
			i++;
		}
	}
	if (flag == 1)
		len_words++;
	return (len_words);
}

static char	*allocate_word(char const *s, char c, int *index)
{
	int	start;
	int	flag;

	start = 0;
	flag = 0;
	while (s[*index])
	{
		if (s[*index] == c)
		{
			if (flag == 1)
				break ;
			while (s[*index] == c)
				(*index)++;
			flag = 0;
		}
		else
		{
			if (!flag)
				start = *index;
			flag = 1;
			(*index)++;
		}
	}
	return (ft_substr(s, start, *index - start));
}

static void	free_memory(char **str, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len && str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	int		index;
	char	**split_string;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	len = len_words(s, c);
	split_string = (char **)malloc((len + 1) * sizeof(char *));
	if (!split_string)
		return (NULL);
	while (i < len)
	{
		split_string[i] = allocate_word(s, c, &index);
		if (split_string[i] == NULL)
		{
			free_memory(split_string, i);
			return ((split_string = NULL));
		}
		i++;
	}
	split_string[i] = NULL;
	return (split_string);
}
