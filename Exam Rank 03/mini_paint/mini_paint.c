/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:13:06 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/30 21:53:19 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int	ft_free(char **area, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(area[i++]);
	free(area);
	return (1);
}

int	ft_close(FILE *file)
{
	fclose(file);
	return (1);
}

int	ft_error_print(void)
{
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int		i, j, arg, width, height;
	float	x, y, res, radius;
	char	**area, back, symb, c;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) && 1);
	file = fopen(argv[1], "r");
	if (!(file))
		return (ft_error_print());
	if ((fscanf(file, "%d %d %c\n", &width, &height, &back)) != 3)
		return (ft_error_print() && ft_close(file));
	if (width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_error_print() && ft_close(file));

	area = malloc(sizeof(char *) * height);
	if (!(area))
		return (ft_close(file) && 1);
	i = -1;
	while (++i < height)
	{
		area[i] = malloc(sizeof(char) * width);
		if (!(area[i]))
			return (ft_free(area, i) && ft_close(file));
		j = 0;
		while (j < width)
			area[i][j++] = back;
	}

	arg = fscanf(file, "%c %f %f %f %c\n", &c, &x, &y, &radius, &symb);
	while (arg == 5)
	{
		if ((c != 'c' && c != 'C') || radius <= 0)
			return (ft_error_print() && ft_free(area, height) && ft_close(file));
		i = -1;
		while (++i < height)
		{
			j = -1;
			while (++j < width)
			{
				res = sqrt(powf(i - y, 2) + powf(j - x, 2));
				if (res <= radius)
					if ((radius - res < 1 && c == 'c') || c == 'C')
						area[i][j] = symb;
			}
		}
	}

	if (arg > 0 && arg != 5)
		return (ft_error_print() && ft_free(area, height) && ft_close(file));

	i = -1;
	while (++i < height)
	{
		j = 0;
		while (j < width)
			write(1, &area[i][j++], 1);
		write(1, "\n", 1);
	}
	return (ft_free(area, height) && fclose(file) && 0);
}
