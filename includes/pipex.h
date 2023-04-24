/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:43:54 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 15:28:33 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define END "\033[0m"
# define RED "\033[0;31m"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_gnl{
	int		fd[2];
	int		ac;
	int		index;
	char	***all_arg;
	int		infile;
	int		outfile;
	pid_t	pid;
	pid_t	pid2;
	char	**path;
	int		bool_hd;
	int		fd_hd;
}t_gnl;

int		first_process(char **envp, t_gnl *gnl);
void	create_infile(t_gnl *gnl, char *limiter);
void	free_gnl(t_gnl *gnl);
void	split_path(t_gnl *gnl, char **envp);
char	**split_arg_cmd(char *av);
void	all_arg(char **av, int ac, t_gnl *gnl);
char	*acces_cmd(t_gnl *gnl, char *cmd);
int		exec_cmd(char *path, char **envp, char **arg, t_gnl *gnl);
int		first_process(char **envp, t_gnl *gnl);
void	open_file(t_gnl *gnl, char **av);
void	initialisation(t_gnl *gnl, char **av, char **envp, int ac);
void	verif_cmd(t_gnl *gnl);
int		exit_managing(int error);
#endif