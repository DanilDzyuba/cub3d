/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 01:04:50 by clauren           #+#    #+#             */
/*   Updated: 2020/10/13 15:50:51 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char			**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = 0;
	if (!(map = ft_calloc(size + 1, sizeof(char *))))
		error("Malloc error", NULL);
	while (*head)
	{
		tmp = *head;
		map[i++] = (char *)(*head)->content;
		(*head) = (*head)->next;
		free(tmp);
	}
	map[i] = 0;
	return (map);
}

static int		check_border_h(char **map, int i, int j)
{
	int t;

	t = 0;
	while (map[i][j - t] != '1')
	{
		if ((!(map[i][j - t])) || map[i][j - t] == ' ')
			return (0);
		t++;
	}
	t = 0;
	while (map[i][j + t] != '1')
	{
		if ((!(map[i][j + t])) || map[i][j + t] == ' ')
			return (0);
		t++;
	}
	return (1);
}

static int		check_border_v(char **map, int i, int j)
{
	int map_h;
	int t;
	int err;

	err = 0;
	map_h = -1;
	while (map[++map_h])
		;
	t = 0;
	while (!err && i + t < map_h && map[i + t][j] != ' ')
		if (map[i + t++][j] == '1')
			err = 1;
	t = 0;
	while (err && i - t >= 0 && map[i - t][j] != ' ')
		if (map[i - t++][j] == '1')
			return (1);
	return (0);
}

static int		set_player(t_game *g, char p, int i, int j)
{
	if (!ft_strchr("NEWS", p))
		return (0);
	if (g->p->set)
		error("More than 1 player on the map", g);
	g->p->x = (float)j;
	g->p->y = (float)i;
	if (p == 'N' && (g->p->a = 270.0f) && (g->p->y += 0.51f + MOVE_SPEED))
		g->p->x += 0.51f + MOVE_SPEED;
	else if (p == 'S' && (g->p->a = 90.0f) && (g->p->y += 0.51f))
		g->p->x += 0.51f - MOVE_SPEED;
	else if (p == 'W' && (g->p->a = 180.0f) && (g->p->x += 0.51f))
		g->p->y += 0.51f - MOVE_SPEED;
	else if (p == 'E' && (g->p->a = 360.0f) && (g->p->x += 0.51f))
		g->p->y += 0.51f + MOVE_SPEED;
	return (1);
}

void			check_map(char **map, t_game *g)
{
	int i;
	int j;

	g->sp_num = 0;
	i = -1;
	g->p->set = 0;
	while (map[++i] && (j = -1))
	{
		while (map[i][++j])
		{
			if (!ft_strchr("102NEWS ", map[i][j]))
				error("Map contains forbidden symbols", g);
			if ((map[i][j] == '2' && g->sp_num++)
				|| ft_strchr("02NEWS", map[i][j]))
			{
				if (!check_border_h(map, i, j) || !check_border_v(map, i, j))
					error("Map are not locked up with borders", g);
			}
			g->p->set += set_player(g, map[i][j], i, j);
		}
	}
	if (!g->p->set)
		error("No player on map", g);
}
