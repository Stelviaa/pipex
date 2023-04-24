/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:18:00 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 13:08:05 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_gnl(t_gnl *gnl)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (gnl->path[++i])
		free(gnl->path[i]);
	free(gnl->path);
	i = -1;
	while (gnl->all_arg[++i])
	{
		while (gnl->all_arg[i][++j])
			free(gnl->all_arg[i][j]);
		j = -1;
	}
	while (i--)
		free(gnl->all_arg[i]);
	free(gnl->all_arg);
}
