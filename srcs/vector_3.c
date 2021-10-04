/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:16:05 by obellado          #+#    #+#             */
/*   Updated: 2021/03/21 01:23:45 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		color_mult(t_color v1, float n)
{
	t_color		v;

	v.r = v1.r * n;
	v.g = v1.g * n;
	v.b = v1.b * n;
	v.o = v1.o;
	if (v.r > 1)
		v.r = 1;
	if (v.g > 1)
		v.g = 1;
	if (v.b > 1)
		v.b = 1;
	return (v);
}

t_color		color_sum(t_color v1, t_color v2)
{
	t_color		v;

	v.r = v1.r + v2.r;
	v.g = v1.g + v2.g;
	v.b = v1.b + v2.b;
	v.o = v1.o;
	if (v.r > 1)
		v.r = 1;
	if (v.g > 1)
		v.g = 1;
	if (v.b > 1)
		v.b = 1;
	return (v);
}

t_color		color_mix(t_color v1, t_color v2)
{
	t_color		v;

	v.r = sqrt(v1.r * v2.r);
	v.g = sqrt(v1.g * v2.g);
	v.b = sqrt(v1.b * v2.b);
	v.o = v1.o;
	return (v);
}

t_color		color_norm(t_color v)
{
	t_color		n;

	n.r = v.r / 255;
	n.g = v.g / 255;
	n.b = v.b / 255;
	return (n);
}

void		inter_sq_l(t_light *c, t_obj *sq, t_pix *pix)
{
	t_vect		p;
	double		d;
	double		l;

	d = vect_skal(sq->xyz, sq->xyz1) * (-1);
	l = (-d - vect_skal(sq->xyz, c->xyz)) / vect_skal(sq->xyz, pix->v1);
	if (l > 0.0)
	{
		p.x = c->xyz.x + (pix->v1.x * l);
		p.y = c->xyz.y + (pix->v1.y * l);
		p.z = c->xyz.z + (pix->v1.z * l);
		if (isinside_sq(&p, sq))
		{
			d = vect_len(vect_sub(p, pix->xyz));
			l = vect_len(vect_sub(p, c->xyz));
			if (d < pix->l && l < pix->l)
				pix->cross_light += 1;
		}
	}
}
