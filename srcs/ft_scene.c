/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:06:13 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:21:40 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_scene_new(t_rt *rt)
{
	pthread_t	threads[MULTI_THREAD];
	t_thread	t[MULTI_THREAD];
	int			rc;
	int			i;

	rel_sys(rt);
	i = 0;
	while (i < MULTI_THREAD)
	{
		ft_memcpy(&t[i].scene, rt, sizeof(t_rt));
		t[i].scene.i = i;
		rc = pthread_create(&threads[i], NULL, (void *)ft_draw, &t[i].scene);
		if (rc)
		{
			printf("Error\nunable to create thread, %d\n", rc);
			ft_exit(rt);
		}
		i += 1;
	}
	i = 0;
	while (i < MULTI_THREAD)
		pthread_join(threads[i++], NULL);
	if (MULTI_THREAD <= 0)
		ft_draw_nothread(rt);
	return (0);
}

void		*ft_draw(void *a)
{
	t_pix		pix;
	char		*dst;
	int			tid;
	t_rt		*rt;

	rt = (t_rt *)a;
	tid = rt->i;
	ft_bzero(&pix, sizeof(t_pix));
	pix.x = 0;
	pix.y = tid;
	while (pix.y < rt->ry)
	{
		while (pix.x < rt->rx)
		{
			ft_bzero(&pix.color, sizeof(t_color));
			draw(rt, &pix);
			dst = rt->addr + (pix.y * rt->line_length + pix.x * \
			(rt->bits_per_pixel / 8));
			*(unsigned int*)dst = ft_color(pix.color);
			pix.x = pix.x + 1;
		}
		pix.y = pix.y + MULTI_THREAD;
		pix.x = 0;
	}
	pthread_exit(NULL);
}

void		*ft_draw_nothread(t_rt *rt)
{
	t_pix		pix;
	char		*dst;

	ft_bzero(&pix, sizeof(t_pix));
	pix.x = 0;
	pix.y = 0;
	while (pix.y < rt->ry)
	{
		while (pix.x < rt->rx)
		{
			ft_bzero(&pix.color, sizeof(t_color));
			draw(rt, &pix);
			dst = rt->addr + (pix.y * rt->line_length + pix.x * \
			(rt->bits_per_pixel / 8));
			*(unsigned int*)dst = ft_color(pix.color);
			pix.x = pix.x + 1;
		}
		pix.y = pix.y + 1;
		pix.x = 0;
	}
	return (NULL);
}

int			ft_error_exit(int err, t_rt *rt)
{
	if (rt->error == 0)
		rt->error = err;
	return (-1);
}
