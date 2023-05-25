/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:53:04 by inaranjo          #+#    #+#             */
/*   Updated: 2023/05/25 15:31:34 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_in;
	int		fd_out;

	if (argc == 5)
	{
		fd_in = init_fd_stdin(argv[1]);
		fd_out = init_fd_stdout(argv[argc - 1]);
		init_processus_family(fd_in, fd_out, argv, envp);
	}
	else
		error_on_args();
	return (0);
}