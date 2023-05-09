/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:25:36 by pkevin            #+#    #+#             */
/*   Updated: 2020/10/16 11:56:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_arrondi_moins(float nb)
{
	int ret;

	if (nb - 0.5 > (int)(nb))
		ret = (int)(nb) - 1;
	else
		ret = (int)(nb);
	return (ret);
}

int		ft_abs2(float nb)
{
	if ((int)nb + 1 > nb)
		return ((int)nb);
	else
		return ((int)nb + 1);
}

int		add_color_splite(t_param *ptr, int y, int x)
{
	ptr->wallx -= ft_arrondi_moins(ptr->wallx);
	ptr->texx = 0;
	ptr->texx = (int)(ptr->wallx * 64);
	if (ptr->side == 0 && ptr->raydx > 0)
		ptr->texx = 63 - ptr->texx;
	if (ptr->side == 1 && ptr->raydy < 0)
		ptr->texx = 63 - ptr->texx;
	if (ptr->start < 0)
		ptr->start = 0;
	ptr->step = 1.0 * 64 / ptr->w_height;
	ptr->texpos = (ptr->start - (ptr->height / 2) +
		(ptr->w_height / 2)) * ptr->step;
	ptr->texy = 0;
	while (y < ptr->end)
		y = wall_texture_choice(ptr, x, y);
	image_sky_floor(ptr, y, x, 0);
	return (1);
}

int		ft_add_color(t_param *ptr)
{
	int		x;
	int		y;

	ptr->wallx = 0;
	x = 0;
	while (x < ptr->width)
	{
		ptr->w_height = ft_raycasting(ptr, x);
		if (ptr->w_height < 0)
			ptr->w_height = 0;
		ptr->start = ((ptr->w_height * -1) / 2) + (ptr->height / 2);
		if (ptr->start < 0)
			ptr->start = 0;
		y = image_sky_floor(ptr, 0, x, 1);
		ptr->end = ptr->w_height / 2 + ptr->height / 2;
		if (ptr->end >= ptr->height)
			ptr->end = ptr->height - 1;
		if (ptr->side == 0)
			ptr->wallx = ptr->posy + ptr->pwdist * ptr->raydy;
		else
			ptr->wallx = ptr->posx + ptr->pwdist * ptr->raydx;
		add_color_splite(ptr, y, x);
		x++;
	}
	return (1);
}

int		ft_image_create(t_param *ptr)
{
	int	endian;

	ptr->sline = 4 * ptr->width;
	endian = 0;
	if (!(ptr->zbuffer = malloc(ptr->width * sizeof(float))))
		return (-1);
	ptr->img = mlx_new_image(ptr->mlx, ptr->width, ptr->height);
	ptr->draw = mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->sline, &endian);
	ft_add_color(ptr);
	if (ptr->nb_sprite > 0)
		ft_sprite(ptr);
	free(ptr->zbuffer);
	ptr->zbuffer = NULL;
	mlx_clear_window(ptr->mlx, ptr->win);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
	mlx_destroy_image(ptr->mlx, ptr->img);
	ptr->img = NULL;
	return (1);
}
