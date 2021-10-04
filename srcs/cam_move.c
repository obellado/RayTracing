/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:21:49 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 19:18:19 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rel_sys(t_rt *rt)
{
	float	d;

	rt->c1->c->r = vect_cross(rt->c1->c->nor, rt->c1->c->up);
	rt->c1->c->r = vect_norm(rt->c1->c->r);
	rt->c1->c->up = vect_norm(vect_cross(rt->c1->c->r, rt->c1->c->nor));
	d = rt->rx / (2 * ((tan(rt->c1->c->fov * 0.0174533 / 2))));
	rt->c1->c->l0 = vect_sub((vect_sub(vect_mult(rt->c1->c->nor, d), \
	vect_mult(rt->c1->c->up, rt->ry / 2))), \
	vect_mult(rt->c1->c->r, (rt->rx / 2)));
}

int			cam_move(t_rt *rt)
{
	if (rt->back == -1)
		rt->c1->c->xyz = vect_sum(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->nor, PACE));
	if (rt->right == -1)
		rt->c1->c->xyz = vect_sub(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->r, PACE));
	if (rt->right == 1)
		rt->c1->c->xyz = vect_sum(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->r, PACE));
	if (rt->back == 1)
		rt->c1->c->xyz = vect_sub(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->nor, PACE));
	if (rt->up == -1)
		rt->c1->c->xyz = vect_sum(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->up, PACE));
	if (rt->up == 1)
		rt->c1->c->xyz = vect_sub(rt->c1->c->xyz, \
		vect_mult(rt->c1->c->up, PACE));
	if (rt->rot_up != 0)
		calc_rotate_up(rt);
	if (rt->rot_r != 0)
		calc_rotate_right(rt);
	if (rt->rot_n != 0)
		calc_rotate_norm(rt);
	return (0);
}

int			calc_rotate_up(t_rt *rt)
{
	t_vect		o;
	t_vect		n;
	t_vect		new;
	t_vect		v;

	o = rt->c1->c->up;
	n = rt->c1->c->nor;
	v.y = ROT_PACE * rt->rot_up * 0.0174533;
	v.z = cos(v.y);
	v.x = 1 - v.z;
	v.y = sin(v.y);
	new.x = (o.x * o.x * v.x + v.z) * n.x + \
	(o.x * o.y * v.x - o.z * v.y) * n.y + (o.x * o.z * v.x + o.y * v.y) * n.z;
	new.y = (o.x * o.y * v.x + o.z * v.y) * n.x + \
	(o.y * o.y * v.x + v.z) * n.y + (o.y * o.z * v.x - o.x * v.y) * n.z;
	new.z = (o.x * o.z * v.x - o.y * v.y) * n.x + \
	(o.y * o.z * v.x + o.x * v.y) * n.y + (o.z * o.z * v.x + v.z) * n.z;
	rt->c1->c->nor = vect_norm(new);
	rt->c1->c->r = vect_norm(vect_cross(rt->c1->c->nor, rt->c1->c->up));
	return (0);
}

int			calc_rotate_right(t_rt *rt)
{
	t_vect		o;
	t_vect		n;
	t_vect		new;
	t_vect		v;

	o = rt->c1->c->r;
	n = rt->c1->c->nor;
	v.y = ROT_PACE * rt->rot_r * 0.0174533;
	v.z = cos(v.y);
	v.x = 1 - v.z;
	v.y = sin(v.y);
	new.x = (o.x * o.x * v.x + v.z) * n.x + \
	(o.x * o.y * v.x - o.z * v.y) * n.y + (o.x * o.z * v.x + o.y * v.y) * n.z;
	new.y = (o.x * o.y * v.x + o.z * v.y) * n.x + \
	(o.y * o.y * v.x + v.z) * n.y + (o.y * o.z * v.x - o.x * v.y) * n.z;
	new.z = (o.x * o.z * v.x - o.y * v.y) * n.x + \
	(o.y * o.z * v.x + o.x * v.y) * n.y + (o.z * o.z * v.x + v.z) * n.z;
	rt->c1->c->nor = vect_norm(new);
	rt->c1->c->up = vect_norm(vect_cross(rt->c1->c->r, rt->c1->c->nor));
	return (0);
}

int			calc_rotate_norm(t_rt *rt)
{
	t_vect		o;
	t_vect		n;
	t_vect		new;
	t_vect		v;

	o = rt->c1->c->nor;
	n = rt->c1->c->up;
	v.y = ROT_PACE * rt->rot_n * 0.0174533;
	v.z = cos(v.y);
	v.x = 1 - v.z;
	v.y = sin(v.y);
	new.x = (o.x * o.x * v.x + v.z) * n.x + \
	(o.x * o.y * v.x - o.z * v.y) * n.y + (o.x * o.z * v.x + o.y * v.y) * n.z;
	new.y = (o.x * o.y * v.x + o.z * v.y) * n.x + \
	(o.y * o.y * v.x + v.z) * n.y + (o.y * o.z * v.x - o.x * v.y) * n.z;
	new.z = (o.x * o.z * v.x - o.y * v.y) * n.x + \
	(o.y * o.z * v.x + o.x * v.y) * n.y + (o.z * o.z * v.x + v.z) * n.z;
	rt->c1->c->up = vect_norm(new);
	rt->c1->c->r = vect_norm(vect_cross(rt->c1->c->nor, rt->c1->c->up));
	return (0);
}
