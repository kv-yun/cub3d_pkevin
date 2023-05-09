/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_splite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:44:28 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 12:48:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		wall_texture_next(t_param *ptr, int x, int y)
{
	if (ptr->c_choice == 2)
		ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw4[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
	else if (ptr->c_choice == 1)
	{
		ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw3[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw3[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw3[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
	}
	else if (ptr->c_choice == 0)
	{
		ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw5[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw5[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw5[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
	}
	ptr->draw[3 + 4 * x + (4 * ptr->width * y)] = 0;
	ptr->texy = (int)ptr->texpos;
	ptr->texpos += ptr->step;
	return (y + 1);
}

int		wall_texture_choice(t_param *ptr, int x, int y)
{
	if (ptr->texx < 0)
		ptr->texx += 64;
	if (ptr->texx >= 64)
		ptr->texx -= 64;
	if (ptr->texy < 0)
		ptr->texy = 0;
	if (ptr->texy >= 64)
		ptr->texy -= 64;
	if (ptr->c_choice == 3)
	{
		ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw2[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw2[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw2[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
	}
	else if (ptr->c_choice == 2)
	{
		ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw4[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
		ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
			ptr->draw4[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
	}
	return (wall_texture_next(ptr, x, y));
}

int		image_sky_floor(t_param *ptr, int y, int x, int c)
{
	if (c == 1)
		while (y < ptr->start)
		{
			ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
				ptr->sky[0];
			ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
				ptr->sky[1];
			ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
				ptr->sky[2];
			ptr->draw[3 + 4 * x + (4 * ptr->width * y)] = 0;
			y++;
		}
	else
		while (y < ptr->height)
		{
			ptr->draw[0 + 4 * x + (4 * ptr->width * y)] =
				ptr->floor[0];
			ptr->draw[1 + 4 * x + (4 * ptr->width * y)] =
				ptr->floor[1];
			ptr->draw[2 + 4 * x + (4 * ptr->width * y)] =
				ptr->floor[2];
			ptr->draw[3 + 4 * x + (4 * ptr->width * y)] = 0;
			y++;
		}
	return (y);
}

int		verif_color(char *str, t_param *ptr)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
	{
		ptr->error = 4;
		return (-1);
	}
	return (1);
}

int		next_line(char **line, t_param *ptr)
{
	while (*line[0] == ' ')
		line[0]++;
	while (*line[0] >= '0' && *line[0] <= '9')
		line[0]++;
	while (*line[0] == ' ')
		line[0]++;
	if (*line[0] != ',')
	{
		ptr->error = 4;
		return (-1);
	}
	else
		line[0]++;
	return (1);
}
