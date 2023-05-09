/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:56:39 by yun               #+#    #+#             */
/*   Updated: 2020/10/11 13:11:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		verif_spawn_splite(t_param *ptr)
{
	if (ptr->p_spawn == 'E')
	{
		ptr->dirx = -1;
		ptr->diry = 0;
		ptr->planex = 0;
		ptr->planey = 0.68;
	}
	else if (ptr->p_spawn == 'W')
	{
		ptr->dirx = 1;
		ptr->diry = 0;
		ptr->planex = 0;
		ptr->planey = -0.68;
	}
	else
		return (-1);
	return (1);
}

int		verif_spawn(t_param *ptr)
{
	if (ptr->p_spawn == 'N')
	{
		ptr->dirx = 0;
		ptr->diry = -1;
		ptr->planex = -0.68;
		ptr->planey = 0;
	}
	else if (ptr->p_spawn == 'S')
	{
		ptr->dirx = 0;
		ptr->diry = 1;
		ptr->planex = 0.68;
		ptr->planey = 0;
	}
	else
		return (verif_spawn_splite(ptr));
	return (1);
}

int		return_spawn(t_param *ptr, int fl)
{
	if (fl < 1 || fl > 1)
		return (-1);
	else
		return (verif_spawn(ptr));
}

int		player_spawn(t_param *ptr)
{
	int i;
	int j;
	int fl;

	fl = 0;
	i = 0;
	while (i < ptr->nb_line)
	{
		j = 0;
		while (ptr->verif_map[i][j])
		{
			if (ptr->verif_map[i][j] != '0' && ptr->verif_map[i][j] != '1'
			&& ptr->verif_map[i][j] != ' ' && ptr->verif_map[i][j] != '2')
			{
				ptr->p_spawn = ptr->verif_map[i][j];
				ptr->posx = j + 0.5;
				ptr->posy = i + 0.5;
				fl++;
			}
			j++;
		}
		i++;
	}
	return (return_spawn(ptr, fl));
}
