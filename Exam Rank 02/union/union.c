#include <unistd.h>

int	charinset(char c, char *abc)
{
	int i;

	i = 0;
	while (abc[i])
	{
		if (c == abc[i])
			return 0;
		++i;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char abc[26];
	int i = 0;
	int j = 0;
	int k = 0;
	while (argv[1][i])
	{
		if (charinset(argv[1][i], abc))
		{
			abc[k] = argv[1][i];
			++k;
		}
		++i;
	}
	while (argv[2][j])
	{
		if (charinset(argv[2][j], abc))
		{
			abc[k] = argv[2][j];
			++k;
		}
		++j;
	}
	write(1, abc, k);
	write(1, "\n", 1);
	return 0;
}
