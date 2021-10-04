/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sp_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:45:41 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 19:31:56 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_diskrim(t_vect *k)
{
	double		t1;
	double		t2;

	k->z = (k->y * k->y) - (4 * k->x * k->z);
	if (k->z >= 0)
	{
		t1 = (-k->y - sqrt(k->z)) / (2 * k->x);
		t2 = (-k->y + sqrt(k->z)) / (2 * k->x);
		if (t1 > 0 || t2 > 0)
		{
			k->x = t2;
			k->y = t1;
			if (k->y < 0 || (k->y > k->x && k->x > 0))
			{
				k->z = k->y;
				k->y = k->x;
				k->x = k->z;
			}
			return (1);
		}
	}
	return (0);
}

void		inter_sphere(t_rt *rt, t_obj *sp, t_pix *pix)
{
	double		t1;
	t_vect		k;

	k.x = vect_skal(pix->v, pix->v);
	k.z = (vect_len(vect_sub(rt->c1->c->xyz, sp->xyz)) * \
	vect_len(vect_sub(rt->c1->c->xyz, sp->xyz)) - (sp->r * sp->r));
	k.y = vect_skal(vect_sub(rt->c1->c->xyz, sp->xyz), pix->v);
	k.y = k.y * 2;
	if ((ft_diskrim(&k)))
	{
		t1 = vect_len(pix->v) * k.y;
		if (pix->t == 0 || t1 < pix->t)
		{
			pix->t = t1;
			pix->n = sp->n;
			pix->ref = sp->refl;
			pix->xyz = vect_sum(rt->c1->c->xyz, vect_mult(pix->v, k.y));
			pix->norm = vect_norm(vect_sub(sp->xyz, pix->xyz));
			pix->color = sp->color;
			if (k.x <= 0)
				pix->inside = 1;
		}
	}
}

void		inter_sphere_l(t_light *l, t_obj *sp, t_pix *pix)
{
	double		t1;
	double		t2;
	t_vect		k;

	k.x = vect_skal(pix->v1, pix->v1);
	k.z = (vect_len(vect_sub(l->xyz, sp->xyz)) * \
	vect_len(vect_sub(l->xyz, sp->xyz)) - (sp->r * sp->r));
	k.y = vect_skal(vect_sub(l->xyz, sp->xyz), pix->v1);
	k.y = k.y * 2;
	if ((ft_diskrim(&k)))
	{
		t1 = vect_len(pix->v1) * k.x;
		t2 = vect_len(pix->v1) * k.y;
		if (pix->n == sp->n)
		{
			if (t1 > 0 && pix->l > t2 + 0.001 && pix->l < t1 + 0.001)
				pix->cross_light += 1;
		}
		else
		{
			if (t2 < pix->l)
				pix->cross_light += 1;
		}
	}
}

void		inter_plane(t_rt *rt, t_obj *pl, t_pix *pix)
{
	double		d;
	double		l;
	t_vect		p;

	ft_bzero(&p, sizeof(p));
	d = vect_skal(pl->xyz, pl->xyz1) * (-1);
	l = (-d - vect_skal(pl->xyz, rt->c1->c->xyz)) / vect_skal(pl->xyz, pix->v);
	if (l > 0 && l < 1000000)
	{
		p.x = rt->c1->c->xyz.x + (pix->v.x * l);
		p.y = rt->c1->c->xyz.y + (pix->v.y * l);
		p.z = rt->c1->c->xyz.z + (pix->v.z * l);
		l = vect_len(vect_sub(p, rt->c1->c->xyz));
		if (pix->t == 0 || l <= pix->t)
		{
			pix->t = l;
			pix->ref = pl->refl;
			pix->xyz = p;
			pix->norm = pl->xyz;
			pix->n = pl->n;
			pix->color = pl->color;
		}
	}
}

void		inter_plane_l(t_light *c, t_obj *pl, t_pix *pix)
{
	t_vect		p;
	float		d;
	float		lo;

	d = vect_skal(pl->xyz, pl->xyz1);
	lo = (d - vect_skal(pl->xyz, c->xyz)) / vect_skal(pl->xyz, pix->v1);
	if (lo > 0.0)
	{
		p.x = c->xyz.x + (pix->v1.x * lo);
		p.y = c->xyz.y + (pix->v1.y * lo);
		p.z = c->xyz.z + (pix->v1.z * lo);
		d = vect_len(vect_sub(p, pix->xyz));
		lo = vect_len(vect_sub(p, c->xyz));
		if (d <= pix->l && lo <= pix->l)
			pix->cross_light += 1;
	}
}
