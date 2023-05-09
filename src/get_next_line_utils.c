/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:40:46 by pkevin            #+#    #+#             */
/*   Updated: 2019/11/18 15:14:30 by pkevin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_detect_n(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_new_save(char *save, char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	if (!(temp = malloc(sizeof(char)
	* (ft_strlen(save) + ft_strlen(buffer) + 1))))
		return (NULL);
	i = 0;
	while (save && save[i])
	{
		temp[i] = save[i];
		i++;
	}
	j = 0;
	while (buffer[j] != '\0' && buffer)
	{
		temp[i] = buffer[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	if (save)
		free(save);
	save = NULL;
	return (temp);
}

int		ft_free(char **save, int ret)
{
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
	return (ret);
}

char	*ft_supp_line(char *last, int size)
{
	char	*temp;
	int		j;

	if (!(temp = malloc((1 + (ft_strlen(last) - size)) * sizeof(char))))
		return (NULL);
	j = 0;
	while (last[size + j] && last)
	{
		temp[j] = last[size + j];
		j++;
	}
	temp[j] = '\0';
	if (last)
		free(last);
	last = NULL;
	return (temp);
}
