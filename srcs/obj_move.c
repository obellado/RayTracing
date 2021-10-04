/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 01:17:18 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 19:50:53 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			obj_move(t_rt *rt)
{
	t_list		*tmp;
	t_vect		v;

	if (!(rt->o1))
		return (0);
	tmp = rt->o1;
	v.x = rt->right * PACE;
	v.y = rt->up * PACE;
	v.z = -rt->back * PACE;
	while (rt->nto != rt->o1->o->n && rt->o1->next)
		rt->o1 = rt->o1->next;
	if (rt->o1->o->type == '0')
		rt->o1->o->xyz = vect_sum(rt->o1->o->xyz, v);
	else if (rt->o1->o->type == '3')
	{
		rt->o1->o->t1 = vect_sum(rt->o1->o->t1, v);
		rt->o1->o->t2 = vect_sum(rt->o1->o->t2, v);
		rt->o1->o->t3 = vect_sum(rt->o1->o->t3, v);
	}
	else
		rt->o1->o->xyz1 = vect_sum(rt->o1->o->xyz1, v);
	if (rt->o1->o->type == '2')
		ft_re_check_sq(rt->o1->o);
	rt->o1 = tmp;
	return (0);
}

int			light_move(t_rt *rt)
{
	t_llist		*tmp;
	t_vect		v;

	if (!(rt->l))
		return (0);
	tmp = rt->l;
	v.x = rt->right * PACE;
	v.y = rt->up * PACE;
	v.z = -rt->back * PACE;
	if (!(rt->l->c))
		return (0);
	while ((rt->nto - rt->no) > rt->l->c->n && rt->l->next)
		rt->l = rt->l->next;
	rt->l->c->xyz = vect_sum(rt->l->c->xyz, v);
	rt->l = tmp;
	return (0);
}

int			obj_rotate(t_rt *rt)
{
	t_list		*tmp;

	if (!(rt->o1))
		return (0);
	tmp = rt->o1;
	while (rt->nto != rt->o1->o->n && rt->o1->next)
		rt->o1 = rt->o1->next;
	if (rt->o1->o->type == '1' || rt->o1->o->type == '2' || \
	rt->o1->o->type == '4')
	{
		if (rt->rot_up != 0)
			rt->o1->o->xyz = vect_norm(rotate_y(rt->o1->o->xyz, \
			ROT_PACE_O * rt->rot_up));
		else if (rt->rot_r != 0)
			rt->o1->o->xyz = vect_norm(rotate_x(rt->o1->o->xyz, \
			ROT_PACE_O * rt->rot_r));
		else if (rt->rot_n != 0)
			rt->o1->o->xyz = vect_norm(rotate_z(rt->o1->o->xyz, \
			ROT_PACE_O * rt->rot_n));
		if (rt->o1->o->type == '2')
			ft_re_check_sq(rt->o1->o);
	}
	rt->o1 = tmp;
	return (0);
}
