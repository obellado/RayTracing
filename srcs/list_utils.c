/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:56:26 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 17:50:20 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list		*ft_listnew(void *content)
{
	t_list		*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list->o = content;
	list->next = NULL;
	return (list);
}

void		ft_clistadd_back(t_clist **old, t_clist *nw)
{
	t_clist		*tmp;

	if (old != NULL)
	{
		if (*old == NULL)
			*old = nw;
		else
		{
			tmp = *old;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = nw;
		}
	}
}

t_clist		*ft_clistnew(void *content)
{
	t_clist		*list;

	if (!(list = (t_clist*)malloc(sizeof(t_clist))))
		return (NULL);
	list->c = content;
	list->next = NULL;
	return (list);
}

void		ft_llistadd_back(t_llist **old, t_llist *nw)
{
	t_llist		*tmp;

	if (old != NULL)
	{
		if (*old == NULL)
			*old = nw;
		else
		{
			tmp = *old;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = nw;
		}
	}
}

t_llist		*ft_llistnew(void *content)
{
	t_llist		*list;

	if (!(list = (t_llist*)malloc(sizeof(t_llist))))
		return (NULL);
	list->c = content;
	list->next = NULL;
	return (list);
}
