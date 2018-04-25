#include "gnl.h"
# include <stdio.h>
# include <fcntl.h>

int		main(int argc, char *argv[])
{
	char	*o;
	int		fd;
	int		r;

	if (argc == 1)
		while((r = get_next_line(0, &o)) > 0)
			printf("%s\n",o);
	else
	{
		if (argc == 2)
			fd = open(argv[1],O_RDONLY);
		if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'f')
		{
			fd = atoi(argv[2]);
			while (fd < 0 && (r = get_next_line(-fd, NULL)) > 0)
				printf("%d\n",r);
		}
		while(fd >= -1 && (r = get_next_line(fd, &o)) > 0)
			printf("%s\n",o);
	}
	if (!r && 0)
		printf("--EOF--\n");
	if (r)
		printf("Error\n");
	return (0);
}
