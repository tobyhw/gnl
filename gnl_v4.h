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

# define BUFF_SIZE 48

# define FD (*(int**)find)[2]
# define COUNT (*(int**)find)[3]
# define NEXT (**(void***)find)
# define STR (&(*(char**)find)[16])

int				get_next_line(const int fd, char **out);

#endif
