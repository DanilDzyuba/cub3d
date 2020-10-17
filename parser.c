/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:30:03 by clauren           #+#    #+#             */
/*   Updated: 2020/10/12 20:26:25 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int		parse_map(t_game *g, int fd, t_list **map, char *line)
{
	char *l;

	ft_lstadd_back(map, ft_lstnew(ft_strdup(line)));
	free(line);
	while (get_next_line(fd, &l))
	{
		if (*l == '\0')
			error("Map contains empty lines", g);
		ft_lstadd_back(map, ft_lstnew(ft_strdup(l)));
		free(l);
	}
	ft_lstadd_back(map, ft_lstnew(ft_strdup(l)));
	free(l);
	return (1);
}

static	void	parse_rfc(unsigned char *c, t_game *g, char *line)
{
	if (*line == 'R')
	{
		if ((*c & C_R))
			error("Resolution double initialization", g);
		else if ((*c |= C_R) && get_resolution(line + 1, g))
			error("Check resolution", g);
	}
	else if (*line == 'F')
	{
		if ((*c & C_F))
			error("Floor color double initialization", g);
		else if ((*c |= C_F) && (g->f = get_color(line + 1)) == -1)
			error("Check floor color", g);
	}
	else if (*line == 'C')
	{
		if ((*c & C_C))
			error("Ceil color double initialization", g);
		else if ((*c |= C_C) && (g->c = get_color(line + 1)) == -1)
			error("Check ceil color", g);
	}
}

void			parse_lines(t_game *g, int fd, char **path, t_list **map)
{
	char			*line;
	int				spaces;
	unsigned char	c;

	c = C_EMPTY;
	while (get_next_line(fd, &line))
	{
		spaces = skip_spaces(&line);
		if (*line == '\0')
			;
		else if (*line == 'S' || *line == 'N' || *line == 'E' || *line == 'W')
		{
			if (get_texture_path(line, path, &c, spaces) == -1)
				error("Check textures's path", g);
		}
		else if (*line == 'R' || *line == 'F' || *line == 'C')
			parse_rfc(&c, g, line);
		else if ((c == C_FULL) && (parse_map(g, fd, map, line - spaces)))
			break ;
		else
			error("Check config file", g);
		free(line - spaces);
	}
}

void			save_screenshot(t_game *g)
{
	int i;
	int fd;
	int size;

	i = 0;
	fd = open(SCREENSHOT_NAME, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, "BM", 2);
	size = (g->res->x * g->res->y) * 4 + 54;
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	my_write(fd, 54, 4);
	my_write(fd, 40, 4);
	write(fd, &g->res->x, 4);
	my_write(fd, -g->res->y, 4);
	my_write(fd, 1, 2);
	write(fd, &g->image->bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	size = g->res->x * g->res->y * 4;
	write(fd, &size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	while (i < size)
		write(fd, &g->image->addr[i++], 1);
	close(fd);
	quit_game(g);
}

int				is_wall(t_game *g, float x, float y)
{
	if (g->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}
