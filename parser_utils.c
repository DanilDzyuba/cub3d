/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:45:45 by clauren           #+#    #+#             */
/*   Updated: 2020/10/12 20:24:54 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		skip_spaces(char **str)
{
	int i;

	i = 0;
	while (**str == ' ')
	{
		i++;
		(*str)++;
	}
	return (i);
}

char	*move_to_next_number(char *line)
{
	skip_spaces(&line);
	while (ft_isdigit(*line))
		line++;
	return (line);
}

int		get_resolution(char *str, t_game *g)
{
	if ((g->res->x = ft_atoi(str)) <= 0)
		return (-1);
	str = move_to_next_number(str);
	if ((g->res->y = ft_atoi(str)) <= 0)
		return (-1);
	if (g->res->x > W_MAX_W)
		g->res->x = W_MAX_W;
	if (g->res->y > W_MAX_H)
		g->res->y = W_MAX_H;
	str = move_to_next_number(str);
	if ((skip_spaces(&str) > -1) && *str)
		return (-1);
	return (0);
}

int		get_color(char *line)
{
	int result;
	int i;
	int t;

	result = 0;
	i = 1;
	while (i++ && *line)
	{
		skip_spaces(&line);
		if (!ft_isdigit(*line))
			return (-1);
		if ((t = ft_atoi(line)) > 255)
			return (-1);
		result += t;
		if (i < 4)
			result <<= 8;
		line = move_to_next_number(line);
		if ((skip_spaces(&line) > -1) && *line != ',')
			break ;
		line++;
	}
	if (i != 4 || ((skip_spaces(&line) > -1) && *line))
		return (-1);
	return (result);
}

int		get_texture_path(char *line, char **p, unsigned char *c, int sp)
{
	if (!ft_strncmp(line, "NO", 2) && (line += 2)
	&& (sp += skip_spaces(&line)) && !p[0] && (*c |= C_NO))
		p[0] = ft_substr(line, 0, ft_strlen(line));
	else if (!ft_strncmp(line, "SO", 2) && (line += 2)
	&& (sp += skip_spaces(&line)) && !p[1] && (*c |= C_SO))
		p[1] = ft_substr(line, 0, ft_strlen(line));
	else if (!ft_strncmp(line, "WE", 2) && (line += 2)
	&& (sp += skip_spaces(&line)) && !p[2] && (*c |= C_WE))
		p[2] = ft_substr(line, 0, ft_strlen(line));
	else if (!ft_strncmp(line, "EA", 2) && (line += 2)
	&& (sp += skip_spaces(&line)) && !p[3] && (*c |= C_EA))
		p[3] = ft_substr(line, 0, ft_strlen(line));
	else if (!ft_strncmp(line, "S ", 2) && (line += 1)
	&& (sp += skip_spaces(&line)) && !p[4] && (*c |= C_S))
		p[4] = ft_substr(line, 0, ft_strlen(line));
	else
		return (-1);
	return (0);
}
