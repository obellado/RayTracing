/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:22:52 by obellado          #+#    #+#             */
/*   Updated: 2021/03/19 19:28:15 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parser(t_rt *rt, char *name)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(name, O_RDONLY);
	n = 0;
	if (fd < 0)
		return (ft_error_exit(-4, rt));
	while (get_next_line(fd, &line) && rt->error == 0)
	{
		parser_2(rt, line);
		n++;
		free(line);
	}
	parser_2(rt, line);
	n++;
	free(line);
	close(fd);
	return (0);
}

int			parser_2(t_rt *rt, char *line)
{
	if (rt->error != 0)
		return (0);
	else if (line[0] == 'R' && line[1] == ' ')
		parser_r(rt, &line[2]);
	else if (line[0] == 'A' && line[1] == ' ')
		parser_a(rt, &line[2]);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		parser_cy(rt, &line[3]);
	else if (line[0] == 'c' && line[1] == ' ')
		parser_cam(rt, &line[2]);
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
	else if (ft_strlen(line) == 0 || line[0] == '#')
		return (0);
	else
		rt->error = -1;
	return (0);
}

int			parser_r(t_rt *rt, char *line)
{
	int		sizex;
	int		sizey;

	if (rt->e_r > 0)
		return (ft_error_exit(-1, rt));
	while (*line == ' ' || *line == '\t')
		line++;
	while (ft_isdigit(*line))
		rt->rx = rt->rx * 10 + *line++ - 48;
	while (*line == ' ' || *line == '\t')
		line++;
	while (ft_isdigit(*line))
		rt->ry = rt->ry * 10 + *line++ - 48;
	if (rt->rx <= 0 || rt->ry <= 0)
		return (ft_error_exit(-1, rt));
	mlx_get_screen_size(rt->m_p, &sizex, &sizey);
	if (sizex < rt->rx)
		rt->rx = sizex;
	if (sizey < rt->ry)
		rt->ry = sizey;
	rt->e_r += 1;
	return (0);
}

int			parser_cam(t_rt *rt, char *line)
{
	t_cam		*sp;

	if (!(sp = (t_cam*)malloc(sizeof(t_cam))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_cam));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->nor = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->fov = parce_float(line, rt);
	ft_check_cam(sp, rt);
	ft_clistadd_back(&rt->c1, ft_clistnew(sp));
	rt->nc += 1;
	return (0);
}

int			parser_a(t_rt *rt, char *line)
{
	if (rt->e_a > 0)
		return (ft_error_exit(-1, rt));
	while (*line == ' ' || *line == '\t')
		line++;
	rt->a = parce_float(line, rt);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	rt->amb = parce_color(line, rt);
	rt->e_a += 1;
	return (0);
}
