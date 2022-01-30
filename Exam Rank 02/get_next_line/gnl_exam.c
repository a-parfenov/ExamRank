/*
** Варианты написания gnl на экзамене
*/

#include <stdlib.h>
#include <fcntl.h>

int get_next_line(char **line)
{
	char buf;
	int i = 0;
	*line = (char *) malloc(100);
	if (*line == NULL)
		return (-1);
	while (read(0, &buf, 1) > 0 && buf != '\n' && buf)
		(*line)[i++] = buf;
	(*line)[i] = '\0';
	if (buf == '\n')
		return 1;
	else
		return 0;
}

/*
#include <fcntl.h>
#include <stdlib.h>

int get_next_line(char **line)
{
	int		i;
	char	buff;

	i = 0;
	if (line == NULL)
		return (-1);
	*line = malloc(sizeof(char) * 100);
	while (read(0, &buff, 1) > 0)
	{
		if (buff == '\n')
		{
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i] = buff;
		++i;
	}
	(*line)[i] = '\0';
	return (0);
}
*/

/*
** Для проверки:

#include <unistd.h>
#include <stdio.h>

int main()
{
	char *h;
	int i = 0;

	while(get_next_line(&h) && i++ != 3)
	{
		printf("%s\n", h);
		free(h);
	}
}
*/

/*
** Скрипт проверки на лики

for ((;;))
do
	clear
	leaks a.out | grep -A10 for
	sleep 1
done
*/