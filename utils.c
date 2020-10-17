/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:36:24 by clauren           #+#    #+#             */
/*   Updated: 2020/10/16 19:45:02 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	my_write(int fd, int x, int n)
{
	write(fd, &x, n);
}

void	change_deg(t_game *g, int change)
{
	g->p->a += change;
	if (g->p->a > 360)
		g->p->a -= 360;
	if (g->p->a < 0)
		g->p->a += 360;
}

int		quit_game(t_game *g)
{
	if (g)
		;
	exit(0);
	return (1);
}

void	get_map_size(t_game *g)
{
	int len;
	int i;

	i = 0;
	g->res->map_x = 0;
	g->res->map_y = 0;
	while (g->map[i])
	{
		len = ft_strlen(g->map[i]);
		if (len > g->res->map_x)
			g->res->map_x = len;
		g->res->map_y++;
		i++;
	}
	if (g->res->map_x)
		g->res->map_s = FT_MIN(g->res->y / g->res->map_y / 3,
						g->res->x / g->res->map_x / 3);
}

void	error(char *msg, t_game *g)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	if (g)
		quit_game(g);
	else
		exit(0);
}
