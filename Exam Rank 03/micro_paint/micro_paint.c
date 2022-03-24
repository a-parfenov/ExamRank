/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:55:00 by aleslie           #+#    #+#             */
/*   Updated: 2022/03/24 23:24:30 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int ft_close(FILE *file)
{
	write(1, "Error: Operation file corrupted\n", 32);
	fclose (file);
	return 1;
}

int ft_check(int i, int j, float x, float y, float w, float h)
{
	if (i < y || i > y + h || j < x || j > x + w)
		return 0;
	if (i - y < 1 || y + h - i < 1 || j - x < 1 || x + w - j < 1)
		return 2;
	return 1;
}

int main (int argc, char **argv)
{
	FILE *file;
	char c, symb;
	float x, y, w, h;
	int i = -1, j, width, height, arg;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) && 1);
	if (!(file = fopen(argv[1], "r")))
		return(write(1, "Error: Operation file corrupted\n", 32) && 1);
	if (fscanf(file, "%d %d %c\n", &width, &height, &symb) != 3)
		return (ft_close(file));
	if (width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_close(file));

	char arr[height][width];
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			arr[i][j] = symb;
	}

	while ((arg = fscanf(file, "%c %f %f %f %f %c\n", &c, &x, &y, &w, &h, &symb)) == 6)
	{
		if ((c != 'r' && c != 'R') || (w <= 0 || h <= 0))
			return (ft_close(file));
		i = -1;
		while (++i < height)
		{
			j = -1;
			while (++j < width)
			{
				if ((ft_check(i, j, x, y, w, h) == 2 && c == 'r') || (ft_check(i, j, x, y, w, h) && c == 'R'))
						arr[i][j] = symb;
			}
		}
	}
	if (arg > 0 && arg != 6)
		return (ft_close(file));

	i = -1;
	while (++i < height) {
		j = -1;
		while (++j < width)
			write(1, &arr[i][j], 1);
		write(1, "\n", 1);
	}
	return (fclose(file) && 0);
}
