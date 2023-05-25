/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:57:16 by jlaiti            #+#    #+#             */
/*   Updated: 2023/05/25 15:29:07 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>

typedef struct s_pipex
{
	// reserve de l-espace memoire pour le chemin abs PATH
	/*PATH=/Users/inaranjo/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/inaranjo/.brew/bin
	*/char	*paths;

//reserve de l espace pour les acces path directory via la decoupe du ft_split ":"
/*
+-----------------------------+
|      "/usr/bin"             |
+-----------------------------+
|   "/usr/local/bin"          |
+-----------------------------+
|      "/usr/sbin"            |
+-----------------------------+
*/char	**access_paths_dir;
	
/*reserve de l espace memoire pour les "cles tuyau" qui vont nous permettre 
de lire ou ecrire le descripteur de fichier(fd): 
int fd[2] créer un canal de communication entre deux processus.
fd[0] pour la lecture et fd[1] pour l'écriture.
 "*/int		fd[2];
	
/* reserve de l espace pour la commande  + commande argtel que ls -a(ex)*/	
	char	*cmd;
	char	**cmd_args;
	
    /*reserve de l espace pour cree un enfant via la fonction fork() 
	pour gerer la premiere excution de commande
	et la 2eme execution de commande*/
	pid_t	pid_child_1;
	pid_t	pid_child_2;


}		t_pipex;

/*utils pipex*/
void	close_pipes(t_pipex *pipex, int fd_stdin, int fd_stdout);
void	free_cmd(t_pipex *pipex);
void	free_access_path(t_pipex *pipex);
void	error_on_args(void);


/*initialise les file descriptor 0=lecture et 1=ecriture */
int init_fd_stdin(char *argv);
int init_fd_stdout(char *argv);


/*initialise la famille en cherchant la command et execute la*/
char *check_path(char *envp[]);
void init_processus_family(int fd_stdin, int fd_stdout, char *argv[], char *envp[]);


/* set up les commandes a trouver dans la PATH*/
char *get_cmd(char **paths, char *cmd);
void exec_cmd_1(t_pipex pipex, int fd_in, char *argv[], char *envp[]);
void	exec_cmd_2(t_pipex pipex, int fd_out, char *argv[], char *envp[]);



#endif
