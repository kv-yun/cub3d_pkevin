/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:08:24 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 15:45:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../mlx/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_param
{
	int			error;
	int			fd;
	int			height;
	int			width;
	int			flag;
	char		floor[4];
	char		sky[4];
	char		*temp_map;
	char		**map;
	char		**verif_map;
	int			last_size;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*ss;
	void		*mlx;
	void		*win;
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	float		olddirx;
	float		planex;
	float		oldplanex;
	float		planey;
	float		camx;
	float		raydx;
	float		raydy;
	float		camerax;
	int			mx;
	int			my;
	float		sidedistx;
	float		sidedisty;
	float		ddistx;
	float		ddisty;
	float		pwdist;
	int			hit;
	int			stepx;
	int			stepy;
	int			side;
	int			w;
	int			a;
	int			s;
	int			d;
	int			e;
	int			left;
	int			right;
	int			nb_line;
	char		p_spawn;
	void		*img;
	void		*img_sprite;
	void		*img2;
	void		*img3;
	void		*img4;
	void		*img5;
	void		*img6;
	char		*draw;
	char		*draw_sprite;
	char		*draw2;
	char		*draw3;
	char		*draw4;
	char		*draw5;
	char		*draw6;
	int			drawstartx;
	int			drawstarty;
	int			drawendx;
	int			drawendy;
	float		wallx;
	float		texpos;
	int			c_choice;
	int			stop;
	int			w_height;
	int			texx;
	int			texy;
	int			pr;
	int			pn;
	int			pso;
	int			ps;
	int			pe;
	int			pw;
	int			pf;
	int			pc;
	int			pm;
	float		*zbuffer;
	float		*spritedistance;
	int			*spriteorder;
	int			nb_sprite;
	float		spx;
	float		spy;
	float		id;
	float		tfx;
	float		tfy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			stripe;
	int			bpp;
	int			sline;
	int			line;
	int			size;
	int			start;
	int			end;
	float		step;
}				t_param;

typedef struct	s_sprite
{
	float		x;
	float		y;
	char		*texture;
}				t_sprite;

int				ft_parsing(t_param *ptr);
int				get_next_line(int fd, char **line);
void			ft_resolution(char *line, t_param *ptr);
void			ft_color(t_param *ptr, char *line, int type);
int				ft_texture(t_param *ptr, char *line, int type);
int				ft_strlen(char *str);
int				ft_map(t_param *ptr, char **line);
int				ft_key_press(int key, t_param *ptr);
int				ft_key_unpress(int key, t_param *ptr);
int				ft_draw(t_param *ptr);
int				ft_player_draw(t_param *ptr, int x, int y);
int				ft_size_wall(t_param *ptr, int x);
int				ft_image_create(t_param *ptr);
int				ft_map_construct(t_param *ptr);
int				ft_verif_map(t_param *ptr);
int				ft_verif_texture(t_param *ptr);
int				ft_disp_error(t_param *ptr);
int				ft_raycasting(t_param *ptr, int x);
int				ft_sprite(t_param *ptr);
float			ft_abs(float nb);
int				ft_free_ptr(t_param *ptr);
int				ft_screen(t_param *ptr);
void			ft_leave(t_param *ptr);
int				ft_add_color(t_param *ptr);
int				ft_sprite_x(int locate, t_param *ptr);
int				ft_sprite_y(int locate, t_param *ptr);
void			ft_sprite_order(t_param *ptr);
int				ft_pixel_black(t_param *ptr);
int				ft_abs_int(int nb);
int				image_sky_floor(t_param *ptr, int y, int x, int c);
int				wall_texture_choice(t_param *ptr, int x, int y);
int				replace_zero(t_param *ptr);
int				verif_contour(t_param *ptr);
int				count_sprite(t_param *ptr);
int				ft_free_sprite(t_param *ptr);
int				player_spawn(t_param *ptr);
int				verif_segfault(t_param *ptr, int x, int y);
int				ray_distx(t_param *ptr, int x);
int				ray_disty(t_param *ptr, int x);
char			*leak_map(t_param *ptr, char *line);
int				leak_map_construct(t_param *ptr, int i);
int				exit_image(t_param *ptr);
int				exit_verif(t_param *ptr, int i);
int				free_texture(t_param *ptr);
int				ft_atoi(char *str);
int				resolution_next(t_param *ptr, char *line, int maxheight);
int				is_map(char *line, t_param *ptr);
int				ft_verif_parsing(t_param *ptr);
int				verif_double(t_param *ptr);
int				last_line(char *line);
int				verif_before_map(t_param *ptr);
int				close_prog(t_param *ptr);
int				verif_arg(char *str);
int				verif_last(t_param *ptr);
int				verif_color(char *str, t_param *ptr);
int				next_line(char **line, t_param *ptr);
void			free_gnl(t_param *ptr);
#endif
