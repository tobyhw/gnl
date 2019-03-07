/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:32:13 by twalpert          #+#    #+#             */
/*   Updated: 2018/04/27 12:32:14 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int		line_out(t_gnl *save, char **out, short +flag, int fd)
{
	int		i;

	while (save && save->fd != fd)
		save = save->next;
	i = -1;
	while (save && ++i < save->n)
		if (save->str[i] == '\n' || (!*flag && i == save->n - 1))
			return ((*flag = 1));
}

int		get_next_line(const int fd, char **out)
{
	static	 t_gnl		*save = NULL;
	t_gnl				*elem;
	short				flag;

	flag = 1;
	while (!line_out(save, out, &flag, fd) && (elem = malloc(sizeof(t_gnl))))
		if ((elem->n = read(fd, elem->str, BUFF_SIZE)) > 0)
		{
			elem->fd = fd;
			elem->next = save;
			save = elem;
		}
		else if ((flag = elem->n))
			free(elem);
	return (flag);
}
