/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:30:12 by twalpert          #+#    #+#             */
/*   Updated: 2018/04/30 12:16:02 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int	ft_readline(int fd, char **out)
{
	char	*tmp;
	char	buf;
	int		r;
	int		l;

	l = 0;
	!out ? l-- : !(*out = (char*)malloc(l + 1));
	!l && *out ? (*out)[0] = 0 : l--;
	while (out && *out && !(r = read(fd, &buf, 1) - 1) && buf !='\n' && ++l > 0)
	{
		tmp = (char*)malloc(l + 1);
		tmp ? tmp[l] = 0 : r--;
		while (r >= 0 && ((*out)[++r - 1] || (!(tmp[r - 1] = buf) && buf)))
			tmp[r - 1] = (*out)[r - 1];
		free(*out);
		*out = tmp;
	}
	r && r != -2 && *out ? r = 1 : free(*out);
	return (r == -2 || !(*out) ? -1 : l);
}
