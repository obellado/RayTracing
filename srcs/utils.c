/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:09:36 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 19:00:40 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_listadd_back(t_list **old, t_list *nw)
{
	t_list		*tmp;

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

void		ft_bzero(void *s, size_t n)
{
	unsigned char *p;

	p = s;
	while (n != 0)
	{
		*p++ = '\0';
		n--;
	}
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (!dst && !src)
		return (dst);
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	while (n != 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		d;

	i = 0;
	d = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			d = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (d);
		}
		i++;
	}
	return (0);
}

int			ft_ext(const char *s1, const char *s2)
{
	int			i;
	int			n;

	i = ft_strlen(s2) - 1;
	n = ft_strlen(s1) - 1;
	if (n > i)
	{
		while (i >= 0)
		{
			if (s1[n--] != s2[i--])
				return (1);
		}
		return (0);
	}
	return (1);
}
