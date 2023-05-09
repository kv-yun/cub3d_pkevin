/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 06:07:25 by pkevin            #+#    #+#             */
/*   Updated: 2020/10/17 16:22:18 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

char	*ft_free2(char **save)
{
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
	return (NULL);
}

int		ft_s(char *save)
{
	int i;

	if (save == NULL)
		return (0);
	i = 0;
	while (save && save[i] != '\n' && save[i] != '\0')
		i++;
	i++;
	return (i);
}

char	*ft_add_save(int fd, char *save)
{
	char	*temp;
	int		size;
	char	*buffer;

	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (ft_free2(&save));
	if (!(temp = malloc(((ft_strlen(save)) + 1) * sizeof(char))))
		return (ft_free2(&save));
	size = -1;
	while ((size = size + 1) >= 0 && save && save[size])
		temp[size] = save[size];
	temp[size] = '\0';
	size = read(fd, buffer, BUFFER_SIZE);
	if (size >= 0 && ((buffer[size] = '\0') == '\0'))
		temp = ft_new_save(temp, buffer);
	while (!(ft_detect_n(temp))
	&& ((size = read(fd, buffer, BUFFER_SIZE)) > 0)
	&& ((buffer[size] = '\0') == '\0'))
		temp = ft_new_save(temp, buffer);
	if (size < 0)
		return (ft_free2(&save));
	ft_free2(&save);
	ft_free2(&buffer);
	return (temp);
}

int		ft_detect_eof(char *save)
{
	int size;

	size = ft_strlen(save);
	if (ft_detect_n(save) == 1)
		return (0);
	else
		return (1);
}

int		get_next_line(int fd, char **line)
{
	int			size;
	static char	*s = NULL;
	int			j;
	int			f;

	if ((f = 0) == 0 && (fd < 0 || gnl_splite(line) < 0))
		return (-1);
	if ((size = 0) == 0 && (!(ft_detect_n(s)) || s == NULL))
	{
		s = ft_add_save(fd, s);
		if ((s != NULL && (ft_strlen(s) == 0 || ft_detect_eof(s))))
			f = 1;
	}
	if ((j = -1) == -1 && (f == 0 || (s[ft_s(s) - 1] == '\0' && ft_s(s) > 0)))
	{
		if (s == NULL || !(*line = malloc((ft_s(s) + 1) * sizeof(char))))
			return (ft_free(&s, -1));
		while ((j = j + 1) < ft_s(s) - 1)
			(*line)[j] = s[j];
		(*line)[j] = '\0';
		if (f == 1)
			return (ft_free(&s, 0));
		s = ft_supp_line(s, ft_s(s));
	}
	return (1);
}
