/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:54:11 by clauren           #+#    #+#             */
/*   Updated: 2020/07/15 01:37:33 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_GET_NEXT_LINE_H
# define GET_NEXT_LINE_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

int		get_next_line(int fd, char **line);

#endif
