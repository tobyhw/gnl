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

#include "get_next_line.h"

int		line_out(t_gnl *elem, char **out, int end, int len)
{
	t_gnl		*find;
	t_gnl		*last;
	int			i;

	find = elem;
	while ((find = find->next))
		find->fd == elem->fd ? len += find->n : 0;
	if (!out || !(*out = malloc(len + end + 1)))
		return (-1);
	(*out)[len + end] = '\0';
	i = -1;
	while (++i < elem->n && (i >= end || ((*out)[len + i] = elem->str[i]) || 1))
		end + i + 1 < elem->n ? elem->str[i] = elem->str[end + i + 1] : 0;
	elem->n -= end + (elem->n > end);
	last = elem;
	while (last && (find = last->next))
		if (!(i = find->n) || find->fd == elem->fd)
		{
			while ((i-- || ((last->next = find->next) && 0)) && len--)
				(*out)[len] = find->str[i];
			free(find);
		}
		else
			last = last->next;
	return (1);
}

int		get_next_line(const int fd, char **out)
{
	static t_gnl	*save = NULL;
	t_gnl			*elem;
	int				flag;
	int				i;

	flag = BUFF_SIZE;
	while (flag >= 0 && ((elem = save) || !save))
	{
		while (!(i = 0) && elem && (elem->fd != fd || !elem->n))
			elem = elem->next;
		while (elem && i < elem->n && elem->str[i] != '\n')
			i++;
		if ((elem && i < elem->n) || flag < BUFF_SIZE)
			return (elem ? line_out(elem, out, i, 0) : 0);
		elem = malloc(sizeof(t_gnl));
		if (elem && (elem->n = read(fd, elem->str, BUFF_SIZE)) > 0)
		{
			elem->fd = fd;
			elem->next = save;
			save = elem;
		}
		if ((flag = elem ? elem->n : -1) <= 0 && elem)
			free(elem);
	}
	return (-1);
}
