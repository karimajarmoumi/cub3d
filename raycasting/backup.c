
#include "../cube.h"

// void display_frame(t_data *data, t_map *map, int i, int j)
// {
//     int y;
//     int x;
//     int wall_color;
//     int player_color;
//     int floor_color;
//     int sep_color;

//     wall_color = 0xA0A0A0;
//     player_color = 0x0000FF;
//     floor_color = 0xFFFFFF;
//     sep_color = 0x000000;
//     y = 0; 
//     while (y < FRAME_HEIGHT)
//     {
//         x = 0;
//         while (x < FRAME_WIDTH)
//         {
//             if (map->map[i][j] == WALL)
//                 my_mlx_pixel_put(data, x + (FRAME_WIDTH  *j), y + (i * FRAME_HEIGHT), wall_color);
//             else if (map->map[i][j] == EMPTY || map->map[i][j] == map->player_pos.player_symbol)
//             { 
//                 my_mlx_pixel_put(data, x + (FRAME_WIDTH *j), y + (i * FRAME_HEIGHT), floor_color);
//             }
//             if(y == 59 || x == 59)
//                 my_mlx_pixel_put(data, x + (FRAME_WIDTH  *j), y + (i * FRAME_HEIGHT), sep_color);
//             x++;
//         }
//         y++;
//     }
// }

// t_ray* ray_data(t_map map,int x, int y, float distance)
// {
//     t_ray *ray;
    
//     ray = malloc(sizeof(t_ray));
//     if(x >= 0)
//         ray->x = x;
//     if(y >= 0)
//         ray->y = y;
//     ray->distance =  sqrt((map.player_pos.x - x) * (map.player_pos.x - x) 
//         + (map.player_pos.y - y) * (map.player_pos.y - y));
//     ray->projection_wall = (FRAME_HEIGHT * ((map.max_width * 60 /2 ) / tan(FOV / 2)))/distance;
//     return ray;
// }

// void draw_rays(t_map *map, double start, double end)
// {
//     double x;
//     double y;
    
//     map->rays = NULL;
//     while (start < end)
//     {
//         x = map->player_pos.x;
//         y = map->player_pos.y;
//         while (1)
//         {
//             if ( map->map[(int)y / 60][(int)x / 60] == WALL )
//             {
//                 ft_lstadd_back(&map->rays, ft_lstnew(ray_data(*map, x, y)));
//                 break;
//             }
//            //my_mlx_pixel_put(&map->data, x , y, 0xff0000);
//             x += cos(start);
//             y += sin(start);
//         }
//         start += ANGLE_FOV / (map->max_width * 60);
//         }
// }


// void draw_ceiling_floor(t_map *map, int map_center)
// {
//     int i;
//     t_coord pos;

//     i = 0;
//     //ceilling
//     while (i < map_center)
//     {
//         pos.x = 0;
//         pos.y = i;
//         DDA(map, &pos, map->max_width *60, i, map->ceiling_color);
//         i++;
//     }
//     //floor
//     i = map_center;
//     while (i < map->map_height *60)
//     {
//         pos.x = 0;
//         pos.y = i;
//         DDA(map, &pos, map->max_width *60, i, map->floor_color);
//         i++;
//     }
// }


// int *wall_texture()
// {
//     int x;
//     int y;

//     int *wall_texture;
    
//     x = 0;
//     wall_texture = malloc(sizeof(int) * FRAME_HEIGHT * FRAME_WIDTH);
//     while (x < FRAME_WIDTH)
//     {
//         y = 0; 
//         while (y < FRAME_HEIGHT)
//         {
//             wall_texture[(y * FRAME_WIDTH) + x] = (x % 8) && (y % 8) ? 0xa2224e : 0x030103;
//             y++;
//         }
//         x++;
//     }
//     return (wall_texture);
// }

// void draw_wall_texture(t_map *map, t_coord pos_start, t_coord pos_end, int *wall_texture)
// {
//     int y;

//     y = pos_start.y;
//     while (y < pos_end.y)
//     {
//         my_mlx_pixel_put(map->data, pos_start.x, y, wall_texture[pos_start.x + y]);
//         y++;
//     }
// }

// void draw_3d_view(t_map *map)
// {
//     int     i;
//     int     map_center;
//     t_coord pos_start;
//     t_coord pos_end;
//     t_ray   *ray;
    
//     i = 0;
//     map_center = map->map_height * 60 / 2;
//     draw_ceiling_floor(map, map_center);
//     while(map->data && map->rays &&  i<= map->max_width*60)
//     {
//         ray = (t_ray*)map->rays->content;
//         pos_start.x = i;
//         pos_start.y = map_center - (ray->projection_wall / 2);
//         pos_end.x = pos_start.x;
//         pos_end.y = pos_start.y + ray->projection_wall;
//        // DDA(map, &pos_start, pos_start.x, pos_start.y + ray->projection_wall, 0xFFFFFF);
//         //draw_wall_texture(map, pos_start, pos_end, wall_texture());
//         // if ( i == 60)
//         //     break;
//         map->rays = map->rays->next;
//         i++;
//     }
// }

