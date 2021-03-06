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

#include "gnl_v1.h"

int		readsave(t_glst *c, char **out, t_gnl i, int r)
{
	while (!(*out = NULL) && c->sv && ++i.l <= c->s)
		if (c->sv[i.l] == '\n' && ((*out) = (char*)malloc(i.l + 1)))
		{
			c->sv = (c->s > i.l ? (char*)malloc(c->s - i.l + 2) : NULL);
			if (++i.l && (c->s = -1) && (c->sv || ++c->s))
				while (i.tmp[++c->s + i.l] || (c->sv[c->s] = 0))
					c->sv[c->s] = i.tmp[c->s + i.l];
			while (i.l--)
				(*out)[i.l] = i.tmp[i.l] == '\n' ? 0 : i.tmp[i.l];
			free(i.tmp);
			return (1);
		}
	if ((i.buf = (char*)malloc(BUFF_SIZE + 1)))
		r = read(c->fd, i.buf, BUFF_SIZE);
	if (i.buf && ++r && (c->sv = (char*)malloc(r + c->s + 2)))
		i.l = r + c->s;
	if (r && !(i.buf[r - 1] = 0) && r <= !c->fd * BUFF_SIZE + !(!c->fd))
		i.buf[r - 1] = i.buf[r - 1 - (!c->fd && r > 1)] == '\n' ? 0 : '\n';
	if ((c->sv && i.buf && i.l-- && r) || !(r = 1))
		while (r-- && ((c->sv[r + c->s] = i.buf[r]) || !i.buf[r]))
			while (!r && ((c->s-- && i.tmp) || (!(c->s = i.l) && i.l)))
				c->sv[c->s] = i.tmp[c->s];
	free(i.tmp);
	free(i.buf);
	return (c->s ? r : !(r == -1));
}

int		get_next_line(const int fd, char **out)
{
	static t_glst	*f = NULL;
	t_glst			*c;
	t_gnl			i;

	c = f;
	i.l = -1;
	while ((!c && out) || (c && c->fd != fd && ((c = c->next) || !c)))
		if (!c && (c = (!out ? NULL : (t_glst*)malloc(sizeof(t_glst)))))
		{
			c->fd = (int)fd;
			c->next = f;
			c->sv = NULL;
			c->s = 0;
			f = c;
		}
	while (out && fd >= 0 && c && i.l == -1 && ((i.tmp = c->sv) || !c->sv))
		i.l = readsave(c, out, i, 0);
	!i.l && c->sv ? free(c->sv) : (i.tmp = NULL);
	if ((out && i.l == 1 && *out) || (!i.l && !(c->sv = NULL)))
		return (i.l);
	return (-1);
}
