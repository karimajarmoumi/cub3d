/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../cube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 15:45:34 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <mlx.h>
#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#define WALL '1'
#define EMPTY '0'
#define SPACE ' '
#define X 60
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define PLAYER_S 'S'
#define PLAYER_N 'N'
#define MIN_RANGE 0
#define MAX_RANGE 255
#define LEFT  97
#define RIGHT 100
#define UP 119
#define DOWN 115
#define RIGHT_ROTATE  65363
#define LEFT_ROTATE  65361
#define ESC  65307
#define PI 3.14
#define FRAME_WIDTH  60
#define FRAME_HEIGHT 60
#define NORD_ANGLE  270 * (PI/180)
#define EAST_ANGLE 0 * (PI/180)
#define SOUTH_ANGLE 90 * (PI/180)
#define WEST_ANGLE 180 * (PI/180)
#define ANGLE_FOV PI/3
#define HALF_FOV  ANGLE_FOV/2

typedef struct t_list
{
	void			*content;
	struct t_list	*next;

}					t_list;
typedef struct s_ray
{
    float x;
    float y;
    float distance;
}t_ray;
typedef struct s_mlx_data
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}t_data;

typedef struct  s_player
{
    
    int     flag_on;
    int     count_player;
    char    **map_cpy;
    int      map_begin;
}t_player;

typedef struct s_position
{
    float x;
    float y;
    char  player_symbol;
    int turn_x;
    int turn_y;
    float rotation_angle;
    float rotation_speed;
    int move_speed;
    int half_fov;
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
    int         max_width;
    int         floor_color;
    int         ceiling_color;
    char        **map;
    t_args      **args;
    t_position  player_pos;
	t_data     *data;
    t_list     *rays;

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
char    **split_identifier(char *line,char **key_value,int *identifier);
int     is_identifier(char *key_value);
void    affect_value(t_args **arg,char *key,char *value);
void    check_identifier(char *line, t_map *map,int *count);
void    check_color_rang(char **key_value, t_map *map);
void    DDA(t_map *map,t_data *data, int target_x, int target_y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    init_data_mlx(t_map *map);
void    draw_map(t_map *map, t_data *data);
int	    close_win(t_map *data);
int	    key_pressed(int code,t_map *map);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);
#endif
