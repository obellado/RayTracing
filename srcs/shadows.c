/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:50:17 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 19:49:08 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_shadow(t_rt *rt, t_pix *pix)
{
	t_list		*tmp;

	tmp = rt->o1;
	while (rt->o1 && pix->cross_light == 0)
	{
		if (rt->o1->o->type == '0')
			inter_sphere_l(rt->l->c, rt->o1->o, pix);
		else if (rt->o1->o->type == '1' && rt->o1->o->n != pix->n)
			inter_plane_l(rt->l->c, rt->o1->o, pix);
		else if (rt->o1->o->type == '2' && rt->o1->o->n != pix->n)
			inter_sq_l(rt->l->c, rt->o1->o, pix);
		else if (rt->o1->o->type == '3' && rt->o1->o->n != pix->n)
			inter_tr_l(rt->l->c, rt->o1->o, pix);
		else if (rt->o1->o->type == '4')
			inter_cy_l(rt->l->c, rt->o1->o, pix);
		rt->o1 = rt->o1->next;
	}
	rt->o1 = tmp;
	return (0);
}

void		ft_light(t_rt *rt, t_pix *pix)
{
	t_llist		*tmp;
	float		cos;

	tmp = rt->l;
	pix->color = color_mix(color_mult(pix->color, rt->a), \
	color_mult(rt->amb, rt->a));
	while (rt->l)
	{
		pix->v1 = vect_norm(vect_sub(pix->xyz, rt->l->c->xyz));
		pix->cross_light = 0;
		pix->l = vect_len(vect_sub(rt->l->c->xyz, pix->xyz));
		ft_shadow(rt, pix);
		if (vect_cos(pix->v, pix->norm) < 0)
			pix->norm = vect_inverse(pix->norm);
		cos = vect_cos(pix->norm, pix->v1);
		if (pix->cross_light == 0 && cos > 0)
			pix->color = color_sum(pix->color, color_mult(rt->l->c->color, \
			rt->l->c->li * cos));
		if (WAVE > 0)
			pix->color = color_mult(pix->color, 1 + sin(pix->t * WAVE));
		if (pix->cross_light == 0 && REFLECT && cos > 0)
			ft_reflect(cos, rt, pix);
		rt->l = rt->l->next;
	}
	rt->l = tmp;
}

void		ft_reflect(float cos, t_rt *rt, t_pix *pix)
{
	float		cos2;

	pix->r = vect_norm(vect_sub(vect_mult(pix->norm, 2 * \
	vect_skal(pix->norm, pix->v1)), pix->v1));
	cos2 = vect_cos(pix->r, pix->v);
	if (cos2 > 0)
		pix->color = color_sum(pix->color, color_mult(rt->l->c->color, \
		rt->l->c->li * pow(cos2, pix->ref) * cos));
}
