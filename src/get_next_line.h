/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 00:09:19 by pkevin            #+#    #+#             */
/*   Updated: 2020/10/17 16:24:36 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 100

int		get_next_line(int fd, char **line);
char	*ft_new_save(char *last, char *buffer);
char	*ft_supp_line(char *last, int size);
int		ft_free(char **save, int ret);
int		ft_strlen(char *str);
int		ft_detect_n(char *str);
int		gnl_splite(char **line);
#endif
