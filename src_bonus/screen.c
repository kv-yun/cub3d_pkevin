/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:32:29 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 11:50:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	order_pixel(t_param *ptr, int line_cnt, int *e, int f)
{
	char	save;
	int		i;

	i = 3;
	while (i >= 0)
	{
		save = ptr->draw[*e + (line_cnt * ptr->sline)];
		ptr->draw[*e + (line_cnt * ptr->sline)] =
			ptr->draw[f - i + (line_cnt * ptr->sline - 1)];
		ptr->draw[f - i + (line_cnt * ptr->sline - 1)] =
			save;
		i--;
		*e = *e + 1;
	}
}

int		add_data_bmp(t_param *ptr)
{
	int i;

	i = ptr->width * ptr->height - 1;
	while (i >= 0)
	{
		write(ptr->fd, &ptr->draw[i * ptr->bpp / 8], 4);
		i--;
	}
	return (1);
}

int		data_create(t_param *ptr)
{
	int		line_cnt;
	int		e;
	int		f;

	line_cnt = 0;
	while (line_cnt < ptr->height)
	{
		e = 0;
		f = ptr->sline;
		while (e < f && e != f)
		{
			order_pixel(ptr, line_cnt, &e, f);
			f -= 4;
		}
		line_cnt++;
	}
	return (1);
}

int		header_bmp(t_param *ptr)
{
	int h_size;
	int plane_nbr;
	int i;

	h_size = 40;
	plane_nbr = 1;
	write(ptr->fd, &h_size, 4);
	write(ptr->fd, &ptr->width, 4);
	write(ptr->fd, &ptr->height, 4);
	write(ptr->fd, &plane_nbr, 2);
	write(ptr->fd, &ptr->bpp, 2);
	i = 0;
	while (i < 28)
	{
		write(ptr->fd, "\0", 1);
		i++;
	}
	data_create(ptr);
	add_data_bmp(ptr);
	return (1);
}

int		ft_screen(t_param *ptr)
{
	int f_size;
	int fst_pix;
	int endian;

	endian = 0;
	ptr->sline = 4 * ptr->width;
	if (!(ptr->zbuffer = malloc(ptr->width * sizeof(float))))
		return (-1);
	close(ptr->fd);
	if ((ptr->fd = open("screen.bmp", O_CREAT | O_RDWR, 0777)) == -1)
		return (-1);
	ptr->img = mlx_new_image(ptr->mlx, ptr->width, ptr->height);
	ptr->draw = mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->sline, &endian);
	ft_add_color(ptr);
	ft_sprite(ptr);
	f_size = 14 + 40 + 4 + (ptr->width * ptr->height) * 4;
	fst_pix = 14 + 40 + 4;
	write(ptr->fd, "BM", 2);
	write(ptr->fd, &f_size, 4);
	write(ptr->fd, "\0\0\0\0", 4);
	write(ptr->fd, &fst_pix, 4);
	header_bmp(ptr);
	close(ptr->fd);
	close_prog(ptr);
	return (1);
}
