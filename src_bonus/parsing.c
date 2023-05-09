/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 17:36:31 by yun               #+#    #+#             */
/*   Updated: 2020/10/18 11:53:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdupli(char *line, char *texture, t_param *ptr)
{
	char	*str;
	int		i;

	if (texture)
	{
		ptr->flag = -1;
		return (texture);
	}
	if (!(str = malloc((ft_strlen(line) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_dispatch(t_param *ptr, char *line, int type)
{
	if (type == 1 && (ptr->pn += 1) >= 1)
		ptr->no = ft_strdupli(line, ptr->no, ptr);
	else if (type == 5 && (ptr->ps += 1) >= 1)
		ptr->ss = ft_strdupli(line, ptr->ss, ptr);
	else if (type == 2 && (ptr->pso += 1) >= 1)
		ptr->so = ft_strdupli(line, ptr->so, ptr);
	else if (type == 3 && (ptr->pw += 1) >= 1)
		ptr->we = ft_strdupli(line, ptr->we, ptr);
	else if ((ptr->pe += 1) >= 1)
		ptr->ea = ft_strdupli(line, ptr->ea, ptr);
	return (1);
}

int		ft_texture(t_param *ptr, char *line, int type)
{
	line++;
	if (type == 1 && line[0] != 'O')
		return (-1);
	else if (type == 3 && line[0] != 'E')
		return (-1);
	else if (type == 4 && line[0] != 'A')
		return (-1);
	if (type == 2 && line[0] != 'O')
		type = 5;
	if (type != 5)
		line++;
	while (*line == ' ' && line)
		line++;
	return (ft_dispatch(ptr, line, type));
}

int		ft_analyse(char *line, t_param *ptr)
{
	if (line[0] == 'R' && ((ptr->pr += 1) >= 1))
		ft_resolution(line, ptr);
	else if (line[0] == 'N' && line[1] == 'O')
		ft_texture(ptr, line, 1);
	else if (line[0] == 'S' && (line[1] == 'O' || line[1] != '\0'))
		ft_texture(ptr, line, 2);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_texture(ptr, line, 3);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_texture(ptr, line, 4);
	else if (line[0] == 'F' && (ptr->pf += 1) >= 1)
		ft_color(ptr, line, 1);
	else if (line[0] == 'C' && (ptr->pc += 1) >= 1)
		ft_color(ptr, line, 2);
	else if (is_map(line, ptr) > 0 && (ptr->flag = 2) == 2)
	{
		ptr->pm = 1;
		ft_map(ptr, &line);
	}
	else if (line[0] != '\0')
	{
		ptr->error = 6;
		return (-1);
	}
	return (ptr->flag);
}

int		ft_parsing(t_param *ptr)
{
	int		size;
	char	*line;

	size = 0;
	line = NULL;
	if ((ptr->flag = 0) == 0 && ptr->fd < 0)
	{
		write(1, "Error\n.cub file not found\n", 26);
		exit(0);
	}
	while (ptr->flag != 2 && (size = get_next_line(ptr->fd, &line)) > 0)
	{
		ptr->flag = 0;
		ptr->flag = ft_analyse(line, ptr);
		if (ptr->flag == -1)
		{
			if (line)
				free(line);
			return (ft_disp_error(ptr));
		}
	}
	if ((ft_verif_texture(ptr)) && ptr->error != 2 && ft_verif_parsing(ptr) > 0)
		ptr->error = 1;
	return (ft_disp_error(ptr));
}
