/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free_family.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:09:11 by inaranjo          #+#    #+#             */
/*   Updated: 2023/05/25 15:28:40 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex, int fd_stdin, int fd_stdout)
{
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(fd_stdin);
	close(fd_stdout);
}


void	free_cmd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i] != 0)
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
}

void	free_access_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->access_paths_dir[i] != 0)
	{
		free(pipex->access_paths_dir[i]);
		i++;
	}
	free(pipex->access_paths_dir);
}

void	error_on_args(void)
{
	ft_printf("Need Cmds => ./pipex [File1] [Cmd1] [Cmd2] [File2]\n");
	exit (EXIT_FAILURE);
}