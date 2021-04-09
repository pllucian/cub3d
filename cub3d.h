/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:57:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:42:30 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define MAP_NONE		0b00000000
# define MAP_ALL		0b11111111
# define MAP_R			0b00000001
# define MAP_F			0b00000010
# define MAP_C			0b00000100
# define MAP_NO			0b00001000
# define MAP_SO			0b00010000
# define MAP_WE			0b00100000
# define MAP_EA			0b01000000
# define MAP_S			0b10000000

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

# define MOVE_SPEED		0.32
# define ROTATE_SPEED	0.08

typedef struct	s_sprite
{
	double		pos_y;
	double		pos_x;
	double		spr_dist;
}				t_sprite;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	double		draw_start;
	double		draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_width;
	int			tex_height;
	double		step;
	double		tex_pos;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			sprite_tex_x;
	int			sprite_tex_y;
}				t_player;

typedef struct	s_map
{
	int			res_x;
	int			res_y;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*sp_path;
	int			f_color;
	int			c_color;
	int			check;
	t_list		*map_lst;
	char		**map;
	int			x_max;
	int			y_max;
}				t_map;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_pp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_data
{
	t_map		map;
	t_player	player;
	int			spr_sum;
	t_sprite	**sprites;
	void		*mlx;
	void		*win;
	int			screen_x;
	int			screen_y;
	int			save;
	t_img		map_img;
	t_img		no_img;
	t_img		so_img;
	t_img		we_img;
	t_img		ea_img;
	t_img		sp_img;
}				t_data;

void			exit_error(t_data *data, int error, const char *messege);
void			free_data(t_data *data);
void			parse_file(char *file, t_data *data);

int				get_resolution(char **elements, t_data *data);
int				get_colors_f_c(char **elements, t_data *data);
int				get_textures_paths(char *line, char **elements, t_data *data);
int				get_sp_path(char *line, char **elements, t_data *data);

void			get_map(t_data *data);
void			check_map(t_data *data);

void			init_player(t_data *data, int	x, int y);
void			init_sprites(t_data *data);

int				get_next_line(int fd, char **line);
int				ft_str_isdigit(char *str);
size_t			ft_arraylen(char **array);
void			ft_freearray(void **array);

void			raycast(t_data *data);
int				render(t_data *data);
void			render_wall_line(t_data *data, int x);
void			get_wall_height(t_data *data, t_player *plr, t_map *map);
void			draw_wall_line(t_data *data, t_player *plr, int x);

void			render_sprites(t_data *data, double **buffer);
void			render_sprite_line(t_data *data, \
									t_player *plr, double **buffer, int i);

int				exit_free(t_data *data);
int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
void			move_player(t_map *map, t_player *plr);

void			move_forward(t_map *map, t_player *plr);
void			move_backward(t_map *map, t_player *plr);
void			move_left(t_map *map, t_player *plr);
void			move_right(t_map *map, t_player *plr);
void			rotate(t_player *plr);

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_img *img, int x, int y);

void			save_to_bmp(t_data *data);

#endif
