#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define LINE_LIMIT 500

int		main(int argc, char *argv[])
{
	char	*o;
	int		fd;
	int		r;
	int		i;

	while (write(1, "file: ", 6) && get_next_line(0, &o) > 0 && (i = LINE_LIMIT))
	{
		if (o[0] == '0' && !o[1] && puts("Reading standard input:"))
			fd = 0;
		else if ((fd = open(o, O_RDONLY)) < 0)
			printf("File not found.\n");
		free(o);
		while (i-- && (r = get_next_line(fd, &o)) > 0)
		{
			printf("%s\n",o);
			free(o);
		}
		if (!r)
			printf("--EOF--\n");
		if (r < 0)
			printf("Error\n");
		/*while((r = get_next_line(0, &o)) > 0 && !(o[0] == 'q' && o[1] == 0))
			free(o);*/
	}
	puts("");
	return (0);
}
