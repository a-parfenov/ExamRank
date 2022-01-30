/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:18:41 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/30 22:00:25 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_close(FILE *file)
{
	fclose(file);
	return (1);
}

int	ft_check(int i, int j, float x, float y, float w, float h)
{
	if (i < y || i > y + h || j < x || j > x + w)
		return (0);
	if (i - y < 1 || y + h - i < 1 || j - x < 1 || x + w - j < 1)
		return (2);
	return (1);
}

int	ft_free(char **area, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(area[i]);
	free(area);
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
	float	x, y, w, h;
	char	**area, c, back, symb;
	int		i, j, width, height, arg;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) && 1);
	file = fopen(argv[1], "r");
	if (!(file))
		return (ft_error_print() && 1);
	if ((fscanf(file, "%d %d %c\n", &width, &height, &back)) != 3)
		return (ft_error_print() && ft_close(file));
	if (width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_error_print() && ft_close(file));
	area = malloc(sizeof(char *) * height);
	if (!(area))
		return (ft_close(file));
	i = -1;
	while (++i < height)
	{
		area[i] = malloc(sizeof(char) * width);
		if (!(area[i]))
			return (ft_free(area, i) && ft_close(file));
		j = -1;
		while (++j < width)
			area[i][j] = back;
	}
	arg = fscanf(file, "%c %f %f %f %f %c\n", &c, &x, &y, &w, &h, &symb);
	while (arg == 6)
	{
		if ((c != 'r' && c != 'R') || (w <= 0 || h <= 0))
			return (ft_error_print() && ft_free(area, height) && ft_close(file));
		i = -1;
		while (++i < height)
		{
			j = -1;
			while (++j < width)
			{
				if ((ft_check(i, j, x, y, w, h) == 2 && c == 'r')
					|| (ft_check(i, j, x, y, w, h) && c == 'R'))
						area[i][j] = symb;
			}
		}
	}
	if (arg > 0 && arg != 6)
		return (ft_error_print() && ft_free(area, height) && ft_close(file));
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			write(1, &area[i][j], 1);
		write(1, "\n", 1);
	}
	return (ft_free(area, height) && ft_close(file) && 0);
}
