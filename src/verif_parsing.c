/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 12:48:55 by yun               #+#    #+#             */
/*   Updated: 2020/10/17 16:14:17 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_map(char *line, t_param *ptr)
{
	int i;
	int ct;

	i = 0;
	ct = 0;
	if (line[0] == '\0')
		return (-1);
	while (line[i])
	{
		if (verif_before_map(ptr) > 0 && line[i] != ' '
		&& line[i] != '1' && line[i] != '2'
		&& line[i] != '0' && line[i] != 'N' && line[i] != 'E'
		&& line[i] != 'W' && line[i] != 'S')
			return (-1);
		else if (verif_before_map(ptr) < 0 && line[i] != '1'
		&& line[i] != '2' && line[i] != ' '
		&& line[i] != '0')
			return (-1);
		if (verif_before_map(ptr) < 0 && line[i] == ' ')
			ct++;
		i++;
	}
	if (ct == i && ft_verif_parsing(ptr) < 0)
		return (-1);
	return (1);
}

int		verif_before_map(t_param *ptr)
{
	if (ptr->pr == 1 && ptr->ps == 1 && ptr->pn == 1 && ptr->pso == 1
	&& ptr->pe == 1 && ptr->pw == 1 && ptr->pf == 1 && ptr->pc == 1)
		return (1);
	return (-1);
}

int		verif_double(t_param *ptr)
{
	if (ptr->pr > 1 || ptr->ps > 1 || ptr->pn > 1 || ptr->pso > 1
	|| ptr->pe > 1 || ptr->pw > 1 || ptr->pf > 1 || ptr->pc > 1)
	{
		ptr->flag = 1;
		return (-1);
	}
	return (1);
}

void	free_gnl(t_param *ptr)
{
	char	*line;
	int		size;
	int		i;

	i = 0;
	size = 0;
	line = NULL;
	while ((size = get_next_line(ptr->fd, &line)) > 0)
		i++;
	if (line)
		free(line);
	line = NULL;
}
