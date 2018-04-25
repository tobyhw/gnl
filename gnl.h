#ifndef FT_GNL
# define FT_GNL
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# define BUFF_SIZE 8

typedef struct	s_glst
{
	struct s_glst	*next;
	int				fd;
	char			*sv;
	int				s;
}				t_glst;

typedef struct	s_gnl
{
	char	*buf;
	char	*tmp;
	int		l;
}				t_gnl;

int     		get_next_line(const int fd, char **out);

#endif
