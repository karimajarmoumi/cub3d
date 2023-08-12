/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 18:31:26 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define WALL '1'
#define EMPTY '0'
#define SPACE ' '
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define PLAYER_S 'S'
#define PLAYER_N 'N'

typedef struct  s_player
{
    char player_symbol;
    int flag_on;
    int count_player;
    char **map_cpy;

}t_player;
typedef struct s_position
{
    int x;
    int y;
}t_position;
typdef struct s_args
{
    char *key;
    char *value;
    int flag;

}t_args;
typedef struct  s_map
{
    //height && width not fix
    int height;
    char **map;
    t_position player_pos;
    t_args **args;
} t_map;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int ft_strlen(const char *str);
bool check_extension(char *fileName);
void readMap(char *fileName,t_map *map);
void displayArray(char **str);
char *getLine(int fd);
 char *copyString(char *src,char *des);
void fillArray(t_map *map,t_player *player, char *fileName);
 void ft_free(char *str);
char	*ft_charjoin(char const *s1, char character);
void    print_error(char *msg_error);
void    check_player(t_player *player,char *line, t_map *map);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *b, int c, size_t len);

#endif
