/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:38:40 by clauren           #+#    #+#             */
/*   Updated: 2020/10/16 14:11:16 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../minilibx/mlx.h"
# include "keys.h"

# define FOV 45.0f
# define MOVE_SPEED 0.25f
# define ROTATE_SPEED 6
# define PRECISION 0.0001f
# define W_MAX_W 2048
# define W_MAX_H 1152
# define SCREENSHOT_NAME "./cub3d.bmp"
# define PROGRAM_NAME "cub3D"

# define C_EMPTY 0b00000000
# define C_R 0b00000001
# define C_F 0b00000010
# define C_C 0b00000100
# define C_S 0b10000000
# define C_SO 0b01000000
# define C_NO 0b00100000
# define C_WE 0b00010000
# define C_EA 0b00001000
# define C_FULL 0b11111111

# define FT_MIN(a,b) (((a)<(b))?(a):(b))
# define FT_TO_RAD(deg) (deg * 3.1415926535f / 180.0f)
# define FT_TO_DEG(rad) (rad * 180.0f / 3.1415926535f)

typedef	struct	s_sprite
{
	float		dist;
	int			x;
	int			y;
	int			size;
	int			h_off;
	int			v_off;
	int			d_rays;
}				t_sprite;

typedef struct	s_ray
{
	float		xx;
	float		yy;
	float		xo;
	float		yo;
	float		len;
	int			wall;
}				t_ray;

typedef struct	s_line
{
	float		start;
	float		end;
	float		len;
}				t_line;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef	struct	s_player
{
	float		x;
	float		y;
	float		a;
	int			set;
}				t_player;

typedef struct	s_resolution
{
	int			x;
	int			y;
	int			map_x;
	int			map_y;
	int			map_s;
}				t_res;

typedef struct	s_texture
{
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_res		*res;
	t_player	*p;
	t_img		*image;
	char		**map;
	t_texture	**texts;
	t_sprite	*sprites;
	int			sp_num;
	int			f;
	int			c;
}				t_game;

void			my_pixel_put(t_img *img, int x, int y, int color);
void			draw_square(t_game *g, int size, int x, int y);
int				quit_game(t_game *g);
void			change_deg(t_game *g, int change);
void			get_map_size(t_game *g);
int				get_texture_color(t_texture *text, int x, int y);
int				skip_spaces(char **str);
int				get_resolution(char *str, t_game *g);
int				get_texture_path(char *line, char **p, unsigned char *c,
						int sp);
int				get_color(char *line);
void			error(char *msg, t_game *g);
void			draw_lines(t_game *g);
int				is_wall(t_game *g, float x, float y);
void			find_text_x(t_game *g, t_ray *ray);
void			draw_texture(t_game *g, t_ray *ray, t_line *line, int x);
void			draw_floorsky(t_game *g, t_line *line, int i);
void			find_sprites(char **map, t_game *g);
void			draw_sprites(t_game *g, float *zbuff);
void			load_texture(char **path, t_game *g);
void			check_map(char **map, t_game *g);
char			**make_map(t_list **head, int size);
int				draw_map(t_game *g);
void			parse_lines(t_game *g, int fd, char **path, t_list **map);
void			my_write(int fd, int x, int n);
void			draw_coord(t_game *g, int mini);
void			save_screenshot(t_game *g);
#endif
