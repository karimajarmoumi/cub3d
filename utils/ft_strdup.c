/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:27:38 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/08 12:14:07 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

int find_space_pos(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if(str[i] == ' ')
			return i;
		i++;
	}
	return i;
}


void separate_two_words(char *str,char **arg1,char **arg2)
{
	int i ;
	int start;
	int len;
	
	i = 0;
	start = find_space_pos(str);
	*arg1 = malloc(sizeof(char)*(start+1));
	if(str)
		len = ft_strlen(str);
	while(i <start)
	{
		arg1[0][i] = str[i];
		i++;
	}
	arg1[0][i] ='\0';
	if(i == len)
		*arg2 =NULL;
	else
		*arg2 = ft_strdup(&str[i + 1]);
}