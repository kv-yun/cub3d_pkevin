/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:49:04 by yun               #+#    #+#             */
/*   Updated: 2020/09/29 13:11:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_param *ptr, t_sprite *sprite, int i)
{
	ptr->spx = sprite[ptr->spriteorder[i]].x - ptr->posx + 0.5;
	ptr->spy = sprite[ptr->spriteorder[i]].y - ptr->posy + 0.5;
	ptr->id = 1.0 / (ptr->planex * ptr->diry - ptr->dirx * ptr->planey);
	ptr->tfx = ptr->id * (ptr->diry * ptr->spx - ptr->dirx * ptr->spy);
	ptr->tfy = ptr->id * (ptr->planey * -1 * ptr->spx + ptr->planex * ptr->spy);
	ptr->spritescreenx = (int)(((ptr->width / 2) * (1 + ptr->tfx / ptr->tfy)));
	ptr->spriteheight = ft_abs_int((int)(ptr->height / (ptr->tfy)));
	ptr->drawstarty = (ptr->spriteheight * -1) / 2 + ptr->height / 2;
	if (ptr->drawstarty < 0)
		ptr->drawstarty = 0;
	ptr->drawendy = ptr->spriteheight / 2 + ptr->height / 2;
	if (ptr->drawendy >= ptr->height)
		ptr->drawendy = ptr->height - 1;
	ptr->spritewidth = ft_abs_int((int)(ptr->height / ptr->tfy));
	ptr->drawstartx = (ptr->spritewidth * -1) / 2 + ptr->spritescreenx;
	if (ptr->drawstartx < 0)
		ptr->drawstartx = 0;
	ptr->drawendx = ptr->spritewidth / 2 + ptr->spritescreenx;
	if (ptr->drawendx >= ptr->width)
		ptr->drawendx = ptr->width - 1;
	ptr->stripe = ptr->drawstartx;
}

int		sprite_splite(t_param *ptr)
{
	int y;
	int d;

	y = ptr->drawstarty;
	while (y < (ptr->drawendy))
	{
		d = (y) * 256 - ptr->height * 128 + ptr->spriteheight * 128;
		ptr->texy = ((d * 32) / ptr->spriteheight) / 128;
		if ((ft_pixel_black(ptr)) == 0)
		{
			ptr->draw[0 + 4 * ptr->stripe + (4 * ptr->width * y)] =
				ptr->draw6[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
			ptr->draw[1 + 4 * ptr->stripe + (4 * ptr->width * y)] =
				ptr->draw6[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
			ptr->draw[2 + 4 * ptr->stripe + (4 * ptr->width * y)] =
				ptr->draw6[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)];
			ptr->draw[3 + 4 * ptr->stripe + (4 * ptr->width * y)] = 0;
		}
		y++;
	}
	return (1);
}

int		boucle_sprite(t_param *ptr, t_sprite *sprite)
{
	int i;

	ft_sprite_order(ptr);
	i = 0;
	while (i < ptr->nb_sprite)
	{
		init_sprite(ptr, sprite, i);
		while (ptr->stripe < ptr->drawendx)
		{
			ptr->texx =
			(int)(256 * (ptr->stripe - ((ptr->spritewidth * -1) / 2 +
				ptr->spritescreenx)) * 64 / ptr->spritewidth) / 256;
			if (ptr->tfy > 0 && ptr->stripe > 0
			&& ptr->stripe < ptr->width && ptr->tfy < ptr->zbuffer[ptr->stripe])
				sprite_splite(ptr);
			ptr->stripe++;
		}
		i++;
	}
	return (0);
}

int		malloc_sprite(t_param *ptr, t_sprite **sprite)
{
	if (ptr->nb_sprite > 0
	&& (!(ptr->spriteorder = malloc(ptr->nb_sprite * sizeof(int)))))
		return (-1);
	if (ptr->nb_sprite > 0
	&& (!(ptr->spritedistance = malloc(ptr->nb_sprite * sizeof(float)))))
		return (-1);
	if (!(*sprite = malloc(ptr->nb_sprite * sizeof(t_sprite))))
		return (-1);
	return (1);
}

int		ft_sprite(t_param *ptr)
{
	int			i;
	t_sprite	*sprite;

	if (malloc_sprite(ptr, &sprite) < 0)
		return (-1);
	i = 0;
	while (i < ptr->nb_sprite)
	{
		ptr->spriteorder[i] = i;
		ptr->spritedistance[i] = (((ptr->posx - (ft_sprite_x)(i, ptr))
		* (ptr->posx - (ft_sprite_x(i, ptr)))) +
		((ptr->posy - ft_sprite_y(i, ptr))
		* (ptr->posy - ft_sprite_y(i, ptr))));
		sprite[i].x = ft_sprite_x(i, ptr);
		sprite[i].y = ft_sprite_y(i, ptr);
		sprite[i].texture = ptr->img6;
		i++;
	}
	boucle_sprite(ptr, sprite);
	if (sprite)
		free(sprite);
	return (ft_free_sprite(ptr));
}
