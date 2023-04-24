/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:29:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 14:37:08 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_infile(t_gnl *gnl, char *limiter)
{
	char	*line;
	char	*str;

	str = ft_calloc(1, 1);
	limiter = ft_strjoin_f(limiter, ft_strdup("\n"), 3);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
			break ;
		str = ft_strjoin_f(str, line, 3);
	}
	free (line);
	gnl->fd_hd = open("fd_hd", O_RDWR | O_CREAT | O_APPEND, 00755);
	str = ft_strjoin_f(str, ft_strdup("\0"), 3);
	write (gnl->fd_hd, str, ft_strlen(str));
	free(str);
	free(limiter);
	close(gnl->fd_hd);
	return ;
}
