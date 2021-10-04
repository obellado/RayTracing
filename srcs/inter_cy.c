/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:21:50 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 18:39:26 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		inter_cy(t_rt *rt, t_obj *cy, t_pix *pix)
{
	t_vect		k;
	t_vect		n;

	k.x = vect_len(vect_sub(pix->v, vect_mult(cy->xyz, vect_skal(pix->v, \
	cy->xyz)))) * vect_len(vect_sub(pix->v, vect_mult(cy->xyz, \
	vect_skal(pix->v, cy->xyz))));
	n = vect_sub(rt->c1->c->xyz, cy->xyz1);
	k.y = 2 * vect_skal(vect_sub(pix->v, vect_mult(cy->xyz, vect_skal(pix->v, \
	cy->xyz))), vect_sub(n, vect_mult(cy->xyz, vect_skal(n, cy->xyz))));
	k.z = vect_len(vect_sub(n, vect_mult(cy->xyz, vect_skal(n, cy->xyz)))) * \
	vect_len(vect_sub(n, vect_mult(cy->xyz, vect_skal(n, cy->xyz)))) - \
	cy->r * cy->r;
	if ((ft_diskrim(&k)))
	{
		inter_cy_2(k.x, rt, cy, pix);
		inter_cy_2(k.y, rt, cy, pix);
	}
}

void		inter_cy_2(double t, t_rt *rt, t_obj *cy, t_pix *pix)
{
	t_vect		n;

	n = vect_sum(rt->c1->c->xyz, vect_mult(pix->v, t));
	t = vect_len(pix->v) * t;
	if (t > 0 && vect_skal(cy->xyz, vect_sub(n, cy->xyz1)) > 0 && \
	vect_skal(cy->xyz, vect_sub(n, vect_sum(cy->xyz1, \
	vect_mult(cy->xyz, cy->h)))) < 0)
	{
		if (pix->t == 0 || t < pix->t)
		{
			pix->t = t;
			pix->n = cy->n;
			pix->ref = cy->refl;
			pix->xyz = n;
			pix->norm = vect_sub(vect_sub(pix->xyz, cy->xyz1), \
			vect_mult(cy->xyz, vect_skal(cy->xyz, \
			vect_sub(pix->xyz, cy->xyz1))));
			pix->color = cy->color;
		}
	}
}

void		inter_cy_l(t_light *c, t_obj *cy, t_pix *pix)
{
	t_vect		k;
	t_vect		n;

	k.x = vect_len(vect_sub(pix->v1, vect_mult(cy->xyz, vect_skal(pix->v1, \
	cy->xyz)))) * vect_len(vect_sub(pix->v1, vect_mult(cy->xyz, \
	vect_skal(pix->v1, cy->xyz))));
	n = vect_sub(c->xyz, cy->xyz1);
	k.y = 2 * vect_skal(vect_sub(pix->v1, vect_mult(cy->xyz, \
	vect_skal(pix->v1, cy->xyz))), vect_sub(n, vect_mult(cy->xyz, \
	vect_skal(n, cy->xyz))));
	k.z = vect_len(vect_sub(n, vect_mult(cy->xyz, vect_skal(n, cy->xyz)))) * \
	vect_len(vect_sub(n, vect_mult(cy->xyz, vect_skal(n, cy->xyz)))) - \
	cy->r * cy->r;
	if ((ft_diskrim(&k)))
	{
		if (cy->n == pix->n)
			inter_cy_l_3(k, c, cy, pix);
		else
			inter_cy_l_2(k, c, cy, pix);
	}
}

void		inter_cy_l_2(t_vect t, t_light *c, t_obj *cy, t_pix *pix)
{
	t_vect		k;
	t_vect		n;

	k = vect_sum(c->xyz, vect_mult(pix->v1, vect_len(pix->v1) * t.x));
	n = vect_sum(c->xyz, vect_mult(pix->v1, vect_len(pix->v1) * t.y));
	if (t.x > 0 && vect_skal(cy->xyz, vect_sub(k, cy->xyz1)) > 0 && \
	vect_skal(cy->xyz, vect_sub(k, vect_sum(cy->xyz1, vect_mult(cy->xyz, \
	cy->h)))) < 0 && vect_len(pix->v1) * t.x < pix->l)
		pix->cross_light += 1;
	else if (t.y > 0 && \
	vect_skal(cy->xyz, vect_sub(n, cy->xyz1)) > 0 && \
	vect_skal(cy->xyz, vect_sub(n, vect_sum(cy->xyz1, vect_mult(cy->xyz, \
	cy->h)))) < 0 && vect_len(pix->v1) * t.y < pix->l)
		pix->cross_light += 1;
}

void		inter_cy_l_3(t_vect k, t_light *c, t_obj *cy, t_pix *pix)
{
	t_vect		t;
	t_vect		n;

	t = vect_sum(c->xyz, vect_mult(pix->v1, vect_len(pix->v1) * k.x));
	n = vect_sum(c->xyz, vect_mult(pix->v1, vect_len(pix->v1) * k.y));
	if (vect_skal(cy->xyz, vect_sub(t, cy->xyz1)) > 0 && \
	vect_skal(cy->xyz, vect_sub(t, vect_sum(cy->xyz1, vect_mult(cy->xyz, \
	cy->h)))) < 0 && pix->l < vect_len(pix->v1) * k.x + 0.01 && \
	pix->l > vect_len(pix->v1) * k.x - 0.01)
	{
		if (vect_skal(cy->xyz, vect_sub(n, cy->xyz1)) > 0 && \
		vect_skal(cy->xyz, vect_sub(n, vect_sum(cy->xyz1, \
		vect_mult(cy->xyz, cy->h)))) < 0)
			pix->cross_light += 1;
	}
}
