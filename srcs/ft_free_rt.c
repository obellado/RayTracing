/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:19:09 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 21:31:59 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_free_o(t_rt *rt)
{
	t_list		*tmp;
	int			i;

	i = 2;
	tmp = rt->o1;
	while (rt->no >= 2)
	{
		tmp = rt->o1;
		while (i++ < rt->no)
			tmp = tmp->next;
		free(tmp->next->o);
		free(tmp->next);
		tmp->next = NULL;
		rt->no = rt->no - 1;
		i = 2;
	}
	if (rt->no == 1)
	{
		free(tmp->o);
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int			ft_free_l(t_rt *rt)
{
	t_llist		*tmp;
	int			i;

	i = 2;
	tmp = rt->l;
	while (rt->nl >= 2)
	{
		tmp = rt->l;
		while (i++ < rt->nl)
			tmp = tmp->next;
		free(tmp->next->c);
		free(tmp->next);
		tmp->next = NULL;
		rt->nl = rt->nl - 1;
		i = 2;
	}
	if (rt->nl == 1)
	{
		free(tmp->c);
		free(tmp);
		tmp = NULL;
		rt->nl = rt->nl - 1;
	}
	return (0);
}

int			ft_free_c(t_rt *rt)
{
	t_clist		*tmp;
	int			i;

	i = 2;
	rt->c1 = rt->c;
	tmp = rt->c1;
	while (rt->nc >= 2)
	{
		tmp = rt->c1;
		while (i++ < rt->nc)
			tmp = tmp->next;
		free(tmp->next->c);
		free(tmp->next);
		tmp->next = NULL;
		rt->nc = rt->nc - 1;
		i = 2;
	}
	if (rt->nc == 1)
	{
		free(tmp->c);
		free(tmp);
		tmp = NULL;
		rt->nc = rt->nc - 1;
	}
	return (0);
}

int			ft_free_rt(t_rt *rt)
{
	ft_free_o(rt);
	ft_free_l(rt);
	ft_free_c(rt);
	free(rt);
	return (0);
}

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*d;
	size_t			i;

	i = 0;
	d = (unsigned char*)b;
	while (len > i)
		d[i++] = (unsigned char)c;
	return (d);
}
