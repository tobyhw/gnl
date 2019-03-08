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

int		line_out(t_gnl **find, char **out, int end, int fd)
{
	t_gnl		*lst;
	int			i;
	int			len;

	len = 0;
	lst = *find;
	while ((lst = lst->next))
		lst->fd == fd ? len += lst->n : 0;
	if (!out || !(*out = malloc(len + end + 1)))
		return (-1);
	(*out)[len + end] = '\0';
	i = -1;
	lst = *find;
	while (++i < lst->n && (i >= end || ((*out)[len + i] = lst->str[i]) || 1))
		end + i + 1 < lst->n ? lst->str[i] = lst->str[end + i + 1] : 0;
	if ((lst->n -= end + (lst->n > end)))
		find = &(*find)->next;
	else if ((*find = lst->next) || 1)
		free(lst);
	while ((lst = *find))
		if (lst->fd == fd || !(find = &(*find)->next))
			while (*find == lst && (((*out)[--len] = lst->str[--lst->n]) || 1))
				if (!lst->n && ((*find = lst->next) || 1))
					free(lst);
	return (1);
}

int		get_next_line(const int fd, char **out)
{
	static t_gnl	*save = NULL;
	t_gnl			**find;
	t_gnl			*new;
	int				flag;
	int				i;

	flag = BUFF_SIZE;
	while (flag >= !BUFF_SIZE && (find = &save))
	{
		while (*find && ((*find)->fd != fd || !(*find)->n))
			find = &(*find)->next;
		i = 0;
		while (*find && i < (*find)->n && (*find)->str[i] != '\n')
			i++;
		if ((*find && i < (*find)->n) || flag != BUFF_SIZE)
			return (*find ? line_out(find, out, i, fd) : 0);
		new = malloc(sizeof(t_gnl));
		if (new && (new->n = read(fd, new->str, BUFF_SIZE)) > 0
			&& (new->fd = fd) >= 0
			&& ((new->next = save) || !save))
			save = new;
		if ((flag = new ? new->n : -1) <= 0 && new)
			free(new);
	}
	return (-1);
}
