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

#include "gnl_v4.h"

int		line_out(void **find, char **out, int end, int fd)
{
	void		*lst;
	int			i;
	int			len;

	len = 0;
	lst = find;
	while ((find = &NEXT) && *find)
		FD == fd ? len += COUNT : 0;
	if (!out || !(*out = malloc(len + end + 1)))
		return (-1);
	(*out)[len + end] = '\0';
	i = -1;
	find = lst;
	while (++i < COUNT && (i >= end || ((*out)[len + i] = STR[i]) || 1))
		end + i + 1 < COUNT ? STR[i] = STR[end + i + 1] : 0;
	if ((COUNT -= end + (COUNT > end)))
		find = &NEXT;
	while ((lst = *find))
		if (FD == fd && COUNT)
			while (COUNT)
				(*out)[--len] = STR[--COUNT];
		else if (FD == fd || !(find = &NEXT))
			if ((*find = NEXT) || 1)
				free(lst);
	return (1);
}

int		get_next_line(const int fd, char **out)
{
	static void		*save = NULL;
	void			**find;
	void			*new;
	int				flag;
	int				i;

	flag = BUFF_SIZE;
	while (flag >= !BUFF_SIZE && (find = &save))
	{
		while (!(i = 0) && *find && FD != fd)
			find = &NEXT;
		while (*find && i <	COUNT &&	STR[i] != '\n')
			i++;
		if ((*find && i <	COUNT) || flag != BUFF_SIZE)
			return (*find ? line_out(find, out, i, fd) : 0);
		new = malloc(BUFF_SIZE + 16);
		find = &new;
		if (new && (COUNT = read(fd, STR, BUFF_SIZE)) > 0
			&& (FD = fd) >= 0
			&& ((NEXT = save) || !save))
			save = new;
		if ((flag = new ? COUNT : -1) <= 0 && new)
			free(new);
	}
	return (-1);
}
