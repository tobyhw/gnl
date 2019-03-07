/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:35:16 by twalpert          #+#    #+#             */
/*   Updated: 2018/04/26 09:38:22 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define BUFF_SIZE 32

typedef struct	s_gnl
{
	struct s_glst	*next;
	short			fd;
	short			n;
	char			str[BUFF_SIZE];
}				t_gnl;

int				get_next_line(const int fd, char **out);

#endif
