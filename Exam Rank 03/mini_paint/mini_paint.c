/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:23:02 by aleslie           #+#    #+#             */
/*   Updated: 2022/03/24 23:23:50 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <unistd.h>

int ft_close(FILE *file)
{
	write(1, "Error: Operation file corrupted\n", 32);
	fclose(file);
	return 1;
}

int main(int argc, char **argv)
{
	FILE *file;
	char c, symb;
	float x, y, radius, res;
	int i = -1, j, height, width, arg;

	if(argc != 2)
		return(write(1, "Error: argument\n", 16) && 1);
	if(!(file = fopen(argv[1], "r")))
		return(write(1, "Error: Operation file corrupted\n", 32) && 1);
	if(fscanf(file, "%d %d %c\n", &width, &height, &symb) != 3)
		return(ft_close(file));
	if(width <= 0 || width > 300 || height <= 0 || height > 300)
		return(ft_close(file));

	char arr[height][width];
	while(++i < height) {
		j = -1;
		while(++j < width)
			arr[i][j] = symb;
	}

	while((arg = fscanf(file, "%c %f %f %f %c\n", &c, &x, &y, &radius, &symb)) == 5)
	{
		if((c != 'c' && c != 'C') || radius <= 0)
			return(ft_close(file));
		i = -1;
		while(++i < height)
		{
			j = -1;
			while(++j < width)
			{
				res = sqrt(pow(i - y, 2) + pow(j - x, 2));
				if(res <= radius)
					if((radius - res < 1 && c == 'c') || c == 'C')
						arr[i][j] = symb;
			}
		}
	}

	if(arg > 0 && arg != 5)
		return(ft_close(file));
	i = -1;
	while(++i < height)
	{
		j = -1;
		while(++j < width)
			write(1, &arr[i][j], 1);
		write(1, "\n", 1);
	}
	return(fclose(file) && 0);
}
