#include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

int		main(int argc, char *argv[])
{
	char	*o;
	int		fd;
	int		r;
	int		i;

	i = -1;
	if (argc == 1)
		while((r = get_next_line(0, &o)) > 0)
		{
			printf("%s\n",o);
			free(o);
		}
	else
	{
		if (argc == 2)
			fd = open(argv[1],O_RDONLY);
		if (argc == 3 && argv[1][0] == '-')
		{
			if (argv[1][1] == 'f')
			{
				fd = atoi(argv[2]);
				while (fd < 0 && (r = get_next_line(-fd, NULL)) > 0)
					printf("%d\n",r);
			}
			else if ((i = atoi(argv[1] + 1) + 1))
				fd = open(argv[2],O_RDONLY);
		}
		while(fd >= -1 && --i && (r = get_next_line(fd, &o)) > 0)
		{
			printf("%s\n",o);
			free(o);
		}
	}
	if (!r && 0)
		printf("--EOF--\n");
	if (r < 0)
		printf("Error\n");
	/*while((r = get_next_line(0, &o)) > 0 && !(o[0] == 'q' && o[1] == 0))
		free(o);*/
	return (0);
}
