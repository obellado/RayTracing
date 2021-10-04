/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:06:11 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 17:38:46 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_color(t_color clr)
{
	float		r;

	if (SEPIA)
	{
		r = (clr.r + clr.b + clr.g) / 3;
		clr.r = r * 1;
		clr.b = r * 0.9;
		clr.g = r * 1;
	}
	clr.r = (int)(clr.r * 255);
	clr.g = (int)(clr.g * 255);
	clr.b = (int)(clr.b * 255);
	return ((int)clr.r << 16 | (int)clr.g << 8 | (int)clr.b);
}

void		draw(t_rt *rt, t_pix *pix)
{
	t_list		*tmp;

	ft_set_pix(pix);
	pix->v = vect_mult(rt->c1->c->r, pix->x);
	pix->v = vect_sum(vect_mult(rt->c1->c->up, pix->y), pix->v);
	pix->v = vect_norm(vect_sum(rt->c1->c->l0, pix->v));
	tmp = rt->o1;
	while (tmp)
	{
		if (tmp->o->type == '0')
			inter_sphere(rt, tmp->o, pix);
		if (tmp->o->type == '1')
			inter_plane(rt, tmp->o, pix);
		if (tmp->o->type == '2')
			inter_sq(rt, tmp->o, pix);
		if (tmp->o->type == '3')
			inter_tr(rt, tmp->o, pix);
		if (tmp->o->type == '4')
			inter_cy(rt, tmp->o, pix);
		tmp = tmp->next;
	}
	if (pix->n > 0)
		ft_light(rt, pix);
}

void		ft_set_pix(t_pix *pix)
{
	pix->n = -1;
	pix->norm.x = 0;
	pix->norm.y = 0;
	pix->norm.z = 0;
	pix->r.x = 0;
	pix->r.y = 0;
	pix->r.z = 0;
	pix->t = 0;
	pix->ref = 0;
}
