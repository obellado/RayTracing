/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:30:57 by obellado          #+#    #+#             */
/*   Updated: 2021/03/21 00:23:49 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parser_u(t_rt *rt, char *name)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(name, O_RDONLY);
	if (fd <= 0)
		return (ft_error_exit(-4, rt));
	n = 0;
	while (get_next_line(fd, &line) && rt->error == 0)
	{
		parser_2_u(rt, line);
		n++;
		free(line);
	}
	parser_2_u(rt, line);
	n++;
	free(line);
	close(fd);
	return (0);
}

int			parser_2_u(t_rt *rt, char *line)
{
	if (rt->error != 0)
		return (0);
	else if (line[0] == 'A' && line[1] == ' ')
		parser_a(rt, &line[2]);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		parser_cy(rt, &line[3]);
	else if (line[0] == 'c' && line[1] == ' ')
		return (0);
	else if (line[0] == 'l' && line[1] == ' ')
		parser_light(rt, &line[2]);
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		parser_sp(rt, &line[3]);
	else if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		parser_sq(rt, &line[3]);
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		parser_pl(rt, &line[3]);
	else if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		parser_tr(rt, &line[3]);
	else if (ft_strlen(line) == 0 || line[0] == '#' || \
	(line[0] == 'R' && line[1] == ' '))
		return (0);
	else
		rt->error = -1;
	return (0);
}

void		ft_resetup_rt(t_rt *rt)
{
	rt->error = 0;
	rt->e_a = 0;
	rt->a = 0;
	rt->right = 0;
	rt->back = 0;
	rt->up = 0;
	rt->rot_up = 0;
	rt->rot_r = 0;
	rt->rot_n = 0;
	rt->amb.o = 0;
	rt->amb.r = 0;
	rt->amb.g = 0;
	rt->amb.b = 0;
	rt->nl = 0;
	rt->no = 0;
	rt->flag = 0;
	rt->l = NULL;
	rt->o1 = NULL;
}

void		ft_setup_rt(t_rt *rt)
{
	ft_resetup_rt(rt);
	rt->m_p = NULL;
	rt->w_p = NULL;
	rt->img = NULL;
	rt->addr = NULL;
	rt->rx = 0;
	rt->ry = 0;
	rt->e_r = 0;
	rt->nc = 0;
	rt->nto = 0;
	rt->c1 = NULL;
	rt->c = NULL;
	rt->l = NULL;
	rt->o1 = NULL;
}
