/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:17:27 by obellado          #+#    #+#             */
/*   Updated: 2021/03/21 01:26:04 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_push(int key, t_rt *rt)
{
	if (key == 13)
		rt->back = -1;
	else if (key == 0)
		rt->right = -1;
	else if (key == 2)
		rt->right = 1;
	else if (key == 1)
		rt->back = 1;
	else if (key == 19)
		rt->up = 1;
	else if (key == 7)
		rt->up = -1;
	else if (key == 123)
		rt->rot_up = 1;
	else if (key == 124)
		rt->rot_up = -1;
	else if (key == 126)
		rt->rot_r = -1;
	else if (key == 125)
		rt->rot_r = 1;
	else if (key == 12)
		rt->rot_n = 1;
	else
		ft_push_2(key, rt);
	return (0);
}

int			ft_push_2(int key, t_rt *rt)
{
	if (key == 14)
		rt->rot_n = -1;
	else if (key == 119 && rt->c1->next && rt->nc > 1)
		rt->c1 = rt->c1->next;
	else if (key == 115 || (key = 119 && !(rt->c1->next) && rt->nc > 1))
		rt->c1 = rt->c;
	return (0);
}

int			ft_release(int key, t_rt *rt)
{
	if (key == 13)
		rt->back = 0;
	else if (key == 0)
		rt->right = 0;
	else if (key == 2)
		rt->right = 0;
	else if (key == 1)
		rt->back = 0;
	else if (key == 19)
		rt->up = 0;
	else if (key == 7)
		rt->up = 0;
	else if (key == 123)
		rt->rot_up = 0;
	else if (key == 124)
		rt->rot_up = 0;
	else if (key == 126)
		rt->rot_r = 0;
	else if (key == 125)
		rt->rot_r = 0;
	else if (key == 12)
		rt->rot_n = 0;
	else
		ft_release_2(key, rt);
	return (0);
}

int			ft_release_2(int key, t_rt *rt)
{
	if (key == 32)
		ft_redraw(rt);
	else if (key == 14)
		rt->rot_n = 0;
	else if (key == 15)
		parser_rotate(rt, rt->name);
	else if (key == 53)
		ft_exit(rt);
	else if (key == 121 && rt->nto < rt->no + rt->nl)
	{
		rt->nto += 1;
		printf("Для перемещения/вращения выбран объект # %d\n", rt->nto);
	}
	else if (key == 116 && rt->nto > 0)
	{
		rt->nto -= 1;
		printf("Для перемещения/вращения выбран объект # %d\n", rt->nto);
	}
	else if (key == 49)
	{
		rt->nto = 0;
		printf("Режим перемещения камеры\n");
	}
	return (0);
}

int			ft_redraw(t_rt *rt)
{
	ft_free_o(rt);
	ft_free_l(rt);
	ft_resetup_rt(rt);
	parser_u(rt, rt->name);
	if (rt->error == 0 && rt->nc == 0)
		rt->error = -5;
	if (rt->error != 0)
		return (ft_error_re(rt));
	return (0);
}
