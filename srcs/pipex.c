/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:43:44 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 15:51:28 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*acces_cmd(t_gnl *gnl, char *cmd)
{
	int		i;
	int		status;
	char	*path;

	i = -1;
	status = 0;
	path = NULL;
	while (gnl->path[++i])
	{
		path = ft_strjoin_f(gnl->path[i], ft_strdup("/"), 2);
		path = ft_strjoin_f(path, cmd, 1);
		status = access(path, F_OK);
		if (!status)
			return (path);
		else
		{
			free(path);
			path = NULL;
		}
	}
	return (0);
}

//renvoie le chemin du programme binaire si il exitse, sinon NULL;
int	exec_cmd(char *path, char **envp, char **arg, t_gnl *gnl)
{
	int	statut;

	statut = execve(path, arg, envp);
	if (statut == -1)
	{
		ft_printf("error\nerror on execve\n");
		free_gnl(gnl);
		free(gnl);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	first_process(char **envp, t_gnl *gnl)
{
	gnl->pid = fork();
	if (gnl->pid == 0)
	{
		close(gnl->fd[0]);
		if (gnl->index == gnl->ac - 2)
			dup2(gnl->outfile, STDOUT_FILENO);
		else
			dup2(gnl->fd[1], STDOUT_FILENO);
		close(gnl->fd[1]);
		exec_cmd(acces_cmd(gnl, gnl->all_arg[gnl->index][0]),
			envp, gnl->all_arg[gnl->index], gnl);
	}
	else
	{
		wait(NULL);
		close(gnl->fd[1]);
		dup2(gnl->fd[0], STDIN_FILENO);
		close(gnl->fd[0]);
	}
	return (0);
}

int	init(int ac, char **av, char **envp, t_gnl *gnl)
{
	split_path(gnl, envp);
	gnl->ac = ac;
	gnl->index = 2;
	all_arg(av, ac, gnl);
	open_file(gnl, av);
	verif_cmd(gnl);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_gnl	*gnl;
	int		pid_status;

	if (ac != 5)
		exit_managing(1);
	pid_status = 2;
	gnl = malloc(sizeof(t_gnl));
	if (!gnl)
		exit_managing(3);
	init(ac, av, envp, gnl);
	while (gnl->index < ac - 1)
	{
		if (pipe(gnl->fd) == -1)
			exit_managing(2);
		if (gnl->index == 2)
			dup2(gnl->infile, STDIN_FILENO);
		first_process(envp, gnl);
		gnl->index++;
	}
	free_gnl(gnl);
	free(gnl);
	return (0);
}
