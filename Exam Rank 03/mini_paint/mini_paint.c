/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:23:02 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/21 17:13:00 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int	print_error(void)
{
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int	ft_close(FILE *file)
{
	fclose(file);
	return (1);
}

int	ft_free(char **map, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(map[i]);
	free(map);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int		i, j, arg_in_file, widht, height;
	float	x, y, res, radius;
	char	**map, back, symb, c;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) && 1);
	if (!(file = fopen(argv[1], "r")))
		return (print_error() && 1);
	if ((fscanf(file, "%d %d %c\n", &widht, &height, &back)) != 3)
		return (print_error() && ft_close(file));
	if (widht <= 0 || widht > 300 || height <= 0 || height > 300)
		return (print_error() && ft_close(file));

	map = malloc(sizeof(char *) * height);
	if (!(map))
		return (1 && ft_close(file));
	i = -1;
	while (++i < height)
	{
		map[i] = malloc(sizeof(char) * widht);
		if (!(map[i]))
			return (ft_free(map, i) && ft_close(file));
		j = -1;
		while (++j < widht)
			map[i][j] = back;
	}

	while ((arg_in_file = fscanf(file, "%c %f %f %f %c\n", &c, &x, &y, &radius, &symb)) == 5)
	{
		if ((c != 'c' && c != 'C') || radius <= 0)
			return (ft_free(map, height) && ft_close(file) && print_error());
		i = -1;
		while (++i < height)
		{
			j = -1;
			while (++j < widht)
			{
				res = sqrt(powf(i - y, 2) + powf(j - x, 2));
				if (res <= radius)
					if ((radius - res < 1 && c == 'c' ) || c == 'C')
						map[i][j] = symb;
			}
		}
	}

	if (arg_in_file > 0 && arg_in_file != 5)
		return (ft_free(map, height) && ft_close(file) && print_error());
	
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < widht)
			write(1, &map[i][j], 1);
		write(1, "\n", 1);
	}
	return (ft_free(map, height) && ft_close(file) && 0);
}
