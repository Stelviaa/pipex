/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managing_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:55:25 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 15:58:39 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	verif_cmd(t_gnl *gnl)
{
	int		index;
	char	*str;

	index = 2;
	index += gnl->bool_hd;
	str = acces_cmd(gnl, gnl->all_arg[index][0]);
	while (index < gnl->ac - 1)
	{
		if (str == NULL)
		{
			ft_printf("%serror%s\n%s: command not found\n",
				RED, END, gnl->all_arg[index][0]);
			free_gnl(gnl);
			free(str);
			exit(EXIT_FAILURE);
		}
		index ++;
		free(str);
		str = acces_cmd(gnl, gnl->all_arg[index][0]);
	}
	free(str);
}

int	exit_managing(int error)
{
	if (error == 1)
	{
		ft_printf("error\nbad number of arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (error == 2)
	{
		ft_printf("error\nfunction pipe return error\n");
		exit(EXIT_FAILURE);
	}
	else if (error == 3)
	{
		ft_printf("error\nmalloc error\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
