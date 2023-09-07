/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:15:02 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/07 22:23:38 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void ft_free(char *str)
{
    if(str)
        free(str);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		if (*ptr)
		{
			while (ptr[i])
			{
				//printf("lll%s\n",ptr[i]);
				free(ptr[i]);
				ptr[i] = NULL;
				i++;
			}
			free(ptr);
			ptr = NULL;
		}
	}
}



void	free_struct_args(t_args **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		if (*ptr)
		{
			while (ptr[i])
			{
				ft_free(ptr[i]->key);
				ptr[i]->key =NULL;
				free(ptr[i]->value);
				ptr[i]->value =NULL;
                free(ptr[i]);
				ptr[i] = NULL;
				i++;
			}
			free(ptr);
		}
	}
}

void free_rays(t_list **list)
{
    t_list *tmp_list =NULL;
    t_ray *tmp_ray;
    t_list *next;
    tmp_list = *list;
    
    while(tmp_list)
    {
        tmp_ray=(t_ray*)((tmp_list)->content);
        if(tmp_ray)
        {
            free(tmp_ray);
            tmp_ray =NULL;
        }
        next = (tmp_list)->next;
        if(tmp_list)
        {
            free(tmp_list);
            tmp_list =NULL;
        }
        tmp_list = next;
    }
}

void ft_free_list(t_list *list)
{
	char *line;
	t_list *next;
	while(list)
	{ 
		line = (char*)list->content;
		ft_free(line);
		next = list->next;
		free(list);
		list = next;
	}
}

