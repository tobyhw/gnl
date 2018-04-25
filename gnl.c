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
		if ((r = read(c->fd, i.buf, BUFF_SIZE)) && r > 0)
			if ((c->sv = (char*)malloc(r + c->s + 1)))
				if ((i.l = r + c->s) && !c->fd && r < BUFF_SIZE && r++ && i.l++)
					i.buf[r - 1] = i.buf[r - 2] == '\n' ? 0 : '\n';
	if (c->sv && r >= 0 && (!(c->sv[i.l] = (r == 0 ? '\n' : 0)) || c->s > 0))
		while (r-- && ((c->sv[r + c->s] = i.buf[r]) || !i.buf[r]))
			while (!r && (c->s-- || !(c->s = i.l) || 0))
				if ((c->sv[c->s] = i.tmp[c->s]) && !c->s)
					free(i.tmp);
	if (!((!i.buf || (r && !c->sv)) && !(r = 1)) && c->s && !c->sv[c->s - 1])
		c->s--;
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
