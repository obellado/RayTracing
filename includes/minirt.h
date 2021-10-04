/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:17:37 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:24:19 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>

# define BUFFER_SIZE 32
# define PACE 5
# define ROT_PACE 3
# define ROT_PACE_O 30
# define REFLECT 1
# define MULTI_THREAD 8
# define SEPIA 0
# define WAVE 0

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_color
{
	float				o;
	float				r;
	float				g;
	float				b;
}					t_color;

typedef struct		s_obj
{
	int				n;
	char			type;
	t_vect			xyz;
	t_vect			xyz1;
	t_vect			xyz2;
	t_vect			xyz3;
	t_vect			t1;
	t_vect			t2;
	t_vect			t3;
	t_vect			t4;
	float			r;
	float			h;
	int				cross_cy;
	int				refl;
	int				clr;
	t_color			color;
}					t_obj;

typedef struct		s_list
{
	t_obj			*o;
	struct s_list	*next;
}					t_list;

typedef struct		s_cam
{
	t_vect			xyz;
	t_vect			nor;
	t_vect			up;
	t_vect			r;
	t_vect			l0;
	float			fov;
}					t_cam;

typedef struct		s_clist
{
	t_cam			*c;
	struct s_clist	*next;
}					t_clist;

typedef	struct		s_light
{
	t_vect			xyz;
	float			li;
	int				clr;
	t_color			color;
	int				n;
}					t_light;

typedef struct		s_llist
{
	t_light			*c;
	struct s_llist	*next;
}					t_llist;

typedef struct		s_pix
{
	int				x;
	int				y;
	t_vect			xyz;
	t_vect			norm;
	int				n;
	t_vect			v;
	t_vect			v1;
	t_vect			r;
	float			t;
	float			l;
	int				ref;
	int				cross_light;
	int				inside;
	int				cy_inside;
	t_color			color;
	int				clr;
}					t_pix;

typedef	struct		s_rt
{
	void			*m_p;
	void			*w_p;
	char			*name;
	int				rx;
	int				ry;
	int				error;
	int				e_r;
	int				e_a;
	float			a;
	t_color			amb;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				nc;
	int				nl;
	int				no;
	int				nto;
	int				right;
	int				back;
	int				up;
	int				rot_up;
	int				rot_r;
	int				rot_n;
	long			i;
	int				flag;
	t_clist			*c1;
	t_clist			*c;
	t_llist			*l;
	t_list			*o1;
	t_vect			rot;
}					t_rt;

typedef	struct		s_thread
{
	int				i;
	t_rt			scene;
}					t_thread;

void				ft_bzero(void *s, size_t n);
t_vect				vect_sum(t_vect v1, t_vect v2);
t_vect				vect_sub(t_vect v1, t_vect v2);
t_vect				vect_mult(t_vect v1, float n);
double				vect_len(t_vect v);
t_vect				vect_norm(t_vect v);
t_vect				vect_inverse(t_vect v);
t_vect				vect_cross(t_vect v1, t_vect v2);
double				vect_skal(t_vect v, t_vect w);
float				vect_cos(t_vect v1, t_vect v2);
int					parser(t_rt *rt, char *name);
int					parser_2(t_rt *rt, char *line);
void				inter_sphere(t_rt *rt, t_obj *sp, t_pix *pix);
void				rel_sys(t_rt *rt);
void				inter_plane(t_rt *rt, t_obj *obj, t_pix *pix);
int					isinside(t_vect	*p, t_obj *tr);
void				inter_tr(t_rt *rt, t_obj *tr, t_pix *pix);
void				inter_sq(t_rt *rt, t_obj *sq, t_pix *pix);
int					isinside_sq(t_vect *p, t_obj *sq);
void				inter_cy(t_rt *rt, t_obj *cy, t_pix *pix);
void				inter_cy_2(double t, t_rt *rt, t_obj *cy, t_pix *pix);
void				inter_cy_l_2(t_vect t, t_light *c, t_obj *cy, t_pix *pix);
void				inter_cy_l_3(t_vect t, t_light *c, t_obj *cy, t_pix *pix);
int					ft_color(t_color clr);
int					ft_close(int keycode, t_rt *rt);
void				my_mlx_pixel_put(t_rt *rt, int x, int y, int color);
int					ft_isdigit(int c);
int					get_next_line(int fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
int					gnl(int fd, char **line, char **tail);
char				*ft_check_tail_create_p(char *tail, char **line);
t_vect				parce_vect(char *line, t_rt *rt);
float				parce_float(char *line, t_rt *rt);
t_color				parce_color(char *line, t_rt *rt);
int					parser_sp(t_rt *rt, char *line);
int					parser_sp_2(t_rt *rt, char *line, t_obj *sp);
int					parser_r(t_rt *rt, char *line);
int					parser_cam(t_rt *rt, char *line);
int					parser_cy(t_rt *rt, char *line);
int					parser_cy_2(t_rt *rt, char *line, t_obj *sp);
int					parser_sq(t_rt *rt, char *line);
int					parser_sq_2(t_rt *rt, char *line, t_obj *sp);
int					parser_pl(t_rt *rt, char *line);
int					parser_pl_2(t_rt *rt, char *line, t_obj *sp);
int					parser_tr(t_rt *rt, char *line);
int					parser_tr_2(t_rt *rt, char *line, t_obj *sp);
int					parser_a(t_rt *rt, char *line);
int					parser_light(t_rt *rt, char *line);
void				ft_listadd_back(t_list **old, t_list *nw);
t_list				*ft_listnew(void *content);
void				ft_clistadd_back(t_clist **old, t_clist *nw);
t_clist				*ft_clistnew(void *content);
void				ft_llistadd_back(t_llist **old, t_llist *nw);
t_llist				*ft_llistnew(void *content);
void				draw(t_rt *rt, t_pix *pix);
t_color				color_mult(t_color v1, float n);
t_color				color_sum(t_color v1, t_color v2);
void				ft_light(t_rt *rt, t_pix *pix);
int					ft_shadow(t_rt *rt, t_pix *pix);
void				ft_reflect(float cos, t_rt *rt, t_pix *pix);
void				inter_sphere_l(t_light *l, t_obj *sp, t_pix *pix);
void				inter_tr_l(t_light *c, t_obj *tr, t_pix *pix);
void				inter_plane_l(t_light *li, t_obj *pl, t_pix *pix);
void				inter_sq_l(t_light *c, t_obj *sq, t_pix *pix);
void				inter_cy_l(t_light *l, t_obj *cy, t_pix *pix);
int					ft_change_c(t_rt *rt);
int					ft_scene_new(t_rt *rt);
void				header_bmp(int size, t_rt *rt, int fd);
int					ft_save_bmp(t_rt *rt, int fd, int p_size);
int					export_bmp(t_rt *rt);
void				ft_setup_rt(t_rt *rt);
void				ft_resetup_rt(t_rt *rt);
int					ft_free_o(t_rt *rt);
int					ft_free_c(t_rt *rt);
int					ft_free_l(t_rt *rt);
int					ft_free_rt(t_rt *rt);
int					ft_error(t_rt *rt);
int					ft_error_exit(int err, t_rt *rt);
int					ft_error_mlx(t_rt *rt, int n);
int					ft_check_cam(t_cam *c, t_rt *rt);
void				ft_set_pix(t_pix *pix);
int					ft_rotate_o(t_rt *rt, int n);
int					parser_roto(t_rt *rt, char *line);
int					parser_rotate(t_rt *rt, char *name);
int					ft_rotate_c(t_rt *rt, char *line);
t_vect				rotate_x(t_vect norm, float ax);
t_vect				rotate_y(t_vect norm, float ax);
t_vect				rotate_z(t_vect norm, float ax);
int					ft_ext(const char *s1, const char *s2);
int					ft_strcmp(const char *s1, const char *s2);
int					cam_move(t_rt *rt);
int					ft_push(int key, t_rt *rt);
int					ft_push_2(int key, t_rt *rt);
int					ft_release(int key, t_rt *rt);
int					ft_release_2(int key, t_rt *rt);
int					ft_exit(t_rt *rt);
int					calc_rotate_up(t_rt *rt);
int					calc_rotate_right(t_rt *rt);

void				*ft_draw(void *rt);
void				*ft_draw_nothread(t_rt *rt);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_check_obj_norm(t_rt *rt, t_obj *o);
int					ft_check_sq(t_obj *sq);
int					ft_check_inv_norm(t_rt *rt, t_obj *o);
int					ft_check_tr(t_obj *tr);
int					ft_do_screen(t_rt *rt);
int					ft_do_bmp(t_rt *rt);
t_color				color_norm(t_color v);
t_color				color_mix(t_color v1, t_color v2);
int					parser_u(t_rt *rt, char *name);
int					parser_2_u(t_rt *rt, char *line);
int					ft_error_re(t_rt *rt);
int					calc_rotate_norm(t_rt *rt);
int					ft_redraw(t_rt *rt);
int					ft_diskrim(t_vect *k);
void				inter_cy_l_2(t_vect t, t_light *c, t_obj *cy, t_pix *pix);
int					obj_move(t_rt *rt);
int					obj_rotate(t_rt *rt);
int					ft_re_check_sq(t_obj *sq);
int					light_move(t_rt *rt);
int					ft_error_exit_2(int err);
void				*ft_memset(void *b, int c, size_t len);

#endif
