/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:04 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/04 15:40:59 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void displayArray(char **str)
{
    int i =0;
    int j;

    while(str[i])
    {
        j =0;
        printf("|");
        while(str[i][j])
        {
            printf("%c",str[i][j]);
            j++;
        }
        printf("|\n");
        i++;
    }
}
 char *copyString(char *src,char *des)
{
    int i =0;
    char *tmp;
    tmp = des;
    while(src[i])
    {
        tmp[i]=src[i];
        i++;
    }
    tmp[i]='\0';
    return tmp;
}
void ft_free(char *str)
{
    if(str)
        free(str);
}

void print_error(char *msg_error)
{
    int len;
    len =ft_strlen(msg_error);
    write(2,msg_error,len);
    write(2,"\n",1);
    exit(1);
}

int  count_words(char **str)
{
    int i;
    
    i = 0;
    while(str && str[i])
        i++; 
    return i;   
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
				free(ptr[i]);
				ptr[i] = NULL;
				i++;
			}
			free(ptr);
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
                //printf("%d %s hhhere\n",i,ptr[i]->key);
              //  printf("%s\n",ptr[i]->value);
				//free(ptr[i]->key);
				//free(ptr[i]->value);
                //free(ptr[i]);
				//ptr[i] = NULL;
				i++;
			}
			//free(ptr);
		}
	}
}