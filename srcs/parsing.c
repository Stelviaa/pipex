/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:49:06 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 14:25:31 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_path(t_gnl *gnl, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!ft_strnstr(envp[i], "PATH=", 6))
		i ++;
	while (envp[j])
		j ++;
	if (j && j == i)
	{
		gnl->path = ft_split("/Users/sforesti/.brew/bin:/Users/sforesti/.rbenv/ \
            shims:/Users/sforesti/.rbenv/shims:/usr/local/bin:/usr/bin:/bin: \
            /usr/sbin: /sbin:/usr/local/munki:/Users/sforesti/.brew/bin: \
			/Users/sforesti/.rbenv/shims:/Users/sforesti/.rbenv/bin", ":");
		return ;
	}
	gnl->path = ft_split(envp[i], "PATH=:");
}

char	**split_arg_cmd(char *av)
{
	char	**ret;

	ret = ft_split(av, " ");
	return (ret);
}

void	all_arg(char **av, int ac, t_gnl *gnl)
{
	int		i;

	i = -1;
	gnl->all_arg = malloc(sizeof(char **) * ac);
	if (!gnl->all_arg)
		exit_managing(3);
	while (++i < ac)
	{
		gnl->all_arg[i] = split_arg_cmd(av[i]);
	}
	gnl->all_arg[i++] = NULL;
}

void	open_file(t_gnl *gnl, char **av)
{
	gnl->infile = open(av[1], O_RDONLY);
	if (gnl->infile == -1)
	{
		ft_printf("no such file or directory: %s", av[1]);
		exit (0);
	}
	gnl->outfile = open(av[gnl->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (gnl->outfile == -1)
	{
		ft_printf("no such file or directory: %s", av[gnl->ac - 1]);
		exit (0);
	}
}
