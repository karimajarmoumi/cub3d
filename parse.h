/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 11:34:48 by kjarmoum         ###   ########.fr       */
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
#define MIN_RANGE 0
#define MAX_RANGE 255

typedef struct  s_player
{
    char    player_symbol;
    int     flag_on;
    int     count_player;
    char    **map_cpy;
    int      map_begin;
}t_player;

typedef struct s_position
{
    int x;
    int y;
}t_position;

typedef struct s_args
{
    char    *key;
    char    *value;
    int     flag;
}t_args;

typedef struct  s_map
{
    int         map_height;
    int         total_height;
    char        **map;
    t_args      **args;
    t_position  player_pos;
    
} t_map;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int     t_strlen(const char *str);
bool    check_extension(char *fileName);
void    readMap(char *fileName,t_map *map);
void    displayArray(char **str);
char    *getLine(int fd);
char    *copyString(char *src,char *des);
void    fillArray(t_map *map,t_player *player, char *fileName);
void    ft_free(char *str);
char    *ft_charjoin(char const *s1, char character);
void    print_error(char *msg_error);
void    check_player(t_player *player,char *line, t_map *map);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
void    *ft_memset(void *b, int c, size_t len);
void    flood_fill(t_player *player, int pos_y, int pos_x);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_isalpha(int c);
int     ft_strlen(const char *str);
int     ft_strchr_str(char *str, char *c);
char    *ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
int	    ft_strcmp(char *s1, char *s2);
int     ft_atoi(const char *str);
int     count_words(char **str);
int		ft_isdigit(int c);
int     is_line_ofMap(char *line);


#endif
