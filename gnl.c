#include "gnl.h"
#include <stdio.h>

int		readsave(t_glst *c, char **out, t_gnl i, int r)
{
	if (i.l >= 0 && c->sv[i.l] == '\n' && (*out = (char*)malloc(i.l + 1)))
	{
		c->sv = (c->s > i.l ? (char*)malloc(c->s - i.l) : NULL);
		if ((c->s = -1) && (c->sv || ++c->s))
			while (i.tmp[++c->s + i.l + 1] || (c->sv[c->s] = 0))
				c->sv[c->s] = i.tmp[c->s + i.l + 1];
		while (i.l >= 0 && ((i.tmp[i.l] == '\n' && ((*out)[i.l] = 0)) || i.l--))
			(*out)[i.l] = i.tmp[i.l];
		free(i.tmp);
		return (-1);
	}
	if ((i.buf = (char*)malloc(BUFF_SIZE)))
		r = read(c->fd, i.buf, BUFF_SIZE);
	if (++r && (c->sv = (char*)malloc(r + c->s)))
		i.l = r + c->s;
	if (i.buf && !(i.buf[r - 1] = 0) && r <= !c->fd * BUFF_SIZE + !(!c->fd))
		i.buf[r - 1] = i.buf[r - 1 - (!c->fd && r > 1)] == '\n' ? 0 : '\n';
	if (c->sv && i.buf && i.l-- && !((!i.buf || (r && !c->sv)) && (r = 1)))
		while (r-- && ((c->sv[r + c->s] = i.buf[r]) || !i.buf[r]))
			while (!r && (c->s-- || (!(c->s = i.l) && i.l)))
				if ((c->sv[c->s] = i.tmp[c->s]) && !c->s)
					free(i.tmp);
	r = c->s ? r : !(r == -1);
	free(i.buf);
	return (r);
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
	while (fd >= 0 && c && i.l == -1 && ((i.tmp = c->sv) || !c->sv))
	{
		while (!(*out = NULL) && c->sv && ++i.l < c->s && c->sv[i.l] != '\n')
			;
		i.l = readsave(c, out, i, 0);
		if ((i.l == -1 && *out) || (!i.l && !(c->sv = NULL)))
			return (-i.l);
	}
	return (-1);
}
