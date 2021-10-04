/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sq_tr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:42:55 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 19:32:14 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			isinside(t_vect *p, t_obj *tr)
{
	t_vect		n;

	n.x = vect_skal(vect_cross(vect_sub(tr->t1, *p), \
	vect_sub(tr->t2, *p)), tr->xyz);
	n.y = vect_skal(vect_cross(vect_sub(tr->t2, *p), \
	vect_sub(tr->t3, *p)), tr->xyz);
	n.z = vect_skal(vect_cross(vect_sub(tr->t3, *p), \
	vect_sub(tr->t1, *p)), tr->xyz);
	if (n.x >= 0 && n.y >= 0 && n.z >= 0)
		return (1);
	else if (n.x <= 0 && n.y <= 0 && n.z <= 0)
		return (1);
	return (0);
}

void		inter_tr(t_rt *rt, t_obj *tr, t_pix *pix)
{
	t_vect		p;
	double		l;

	l = (tr->xyz.x * tr->t1.x + tr->xyz.y * tr->t1.y + \
	tr->xyz.z * tr->t1.z) * (-1);
	l = (-l - vect_skal(tr->xyz, rt->c1->c->xyz)) / vect_skal(tr->xyz, pix->v);
	if (l > 0.0)
	{
		p.x = rt->c1->c->xyz.x + (pix->v.x * l);
		p.y = rt->c1->c->xyz.y + (pix->v.y * l);
		p.z = rt->c1->c->xyz.z + (pix->v.z * l);
		if (isinside(&p, tr))
		{
			l = vect_len(vect_sub(p, rt->c1->c->xyz));
			if (pix->t == 0 || l < pix->t)
			{
				pix->t = l;
				pix->xyz = p;
				pix->n = tr->n;
				pix->ref = tr->refl;
				pix->norm = tr->xyz;
				pix->color = tr->color;
			}
		}
	}
}

void		inter_tr_l(t_light *c, t_obj *tr, t_pix *pix)
{
	t_vect		p;
	float		d;
	float		l;

	d = (tr->xyz.x * tr->t1.x + tr->xyz.y * tr->t1.y + \
	tr->xyz.z * tr->t1.z) * (-1);
	l = (-d - vect_skal(tr->xyz, c->xyz)) / vect_skal(tr->xyz, pix->v1);
	if (l > 0)
	{
		p.x = c->xyz.x + (pix->v1.x * l);
		p.y = c->xyz.y + (pix->v1.y * l);
		p.z = c->xyz.z + (pix->v1.z * l);
		if (isinside(&p, tr))
		{
			l = vect_len(vect_sub(p, pix->xyz));
			d = vect_len(vect_sub(p, c->xyz));
			if (l < pix->l && d < pix->l)
				pix->cross_light += 1;
		}
	}
}

int			isinside_sq(t_vect *p, t_obj *sq)
{
	t_vect		n;
	double		t;

	n.x = vect_skal(vect_cross(vect_sub(sq->t1, *p), \
	vect_sub(sq->t2, *p)), sq->xyz);
	n.y = vect_skal(vect_cross(vect_sub(sq->t2, *p), \
	vect_sub(sq->t3, *p)), sq->xyz);
	n.z = vect_skal(vect_cross(vect_sub(sq->t3, *p), \
	vect_sub(sq->t4, *p)), sq->xyz);
	t = vect_skal(vect_cross(vect_sub(sq->t4, *p), \
	vect_sub(sq->t1, *p)), sq->xyz);
	if (n.x >= 0 && n.y >= 0 && n.z >= 0 && t >= 0)
		return (1);
	else if (n.x <= 0 && n.y <= 0 && n.z <= 0 && t <= 0)
		return (1);
	return (0);
}

void		inter_sq(t_rt *rt, t_obj *sq, t_pix *pix)
{
	t_vect		p;
	double		d;
	double		l;

	d = vect_skal(sq->xyz, sq->xyz1) * (-1);
	l = (-d - vect_skal(sq->xyz, rt->c1->c->xyz)) / vect_skal(sq->xyz, pix->v);
	if (l > 0.0)
	{
		p.x = rt->c1->c->xyz.x + (pix->v.x * l);
		p.y = rt->c1->c->xyz.y + (pix->v.y * l);
		p.z = rt->c1->c->xyz.z + (pix->v.z * l);
		if (isinside_sq(&p, sq))
		{
			l = vect_len(vect_sub(p, rt->c1->c->xyz));
			if (pix->t == 0 || l < pix->t)
			{
				pix->t = l;
				pix->xyz = p;
				pix->n = sq->n;
				pix->ref = sq->refl;
				pix->norm = sq->xyz;
				pix->color = sq->color;
			}
		}
	}
}
