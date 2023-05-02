/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:54:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/30 17:08:52 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_path(t_gnl *gnl, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!envp[0])
	{
		ft_printf ("%serror%s\nnot env\n", RED, END);
		exit (EXIT_FAILURE);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i ++;
	while (envp[j])
		j ++;
	if (ft_strncmp(envp[i - 1], "PATH=", 5) && j && j == i)
	{
		ft_printf("%serror%s\nnot PATH\n", RED, END);
		exit (EXIT_FAILURE);
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
	gnl->all_arg = malloc(sizeof(char **) * ac + 1);
	while (++i < ac)
		gnl->all_arg[i] = split_arg_cmd(av[i]);
	gnl->all_arg[i++] = NULL;
}

void	open_file(t_gnl *gnl, char **av)
{
	if (ft_strcmp(av[1], "here_doc"))
		gnl->infile = open(av[1], O_RDONLY);
	if (ft_strcmp(av[1], "here_doc") && gnl->infile == -1)
	{
		ft_printf("no such file or directory: %s\n", av[1]);
		exit (0);
	}
	if (!ft_strcmp(av[1], "here_doc"))
		gnl->outfile = open(av[gnl->ac - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		gnl->outfile = open(av[gnl->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (gnl->outfile == -1)
	{
		ft_printf("no such file or directory: %s\n", av[gnl->ac - 1]);
		exit (0);
	}
}
