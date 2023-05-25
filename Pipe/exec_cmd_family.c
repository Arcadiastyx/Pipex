/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_family.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:55:42 by inaranjo          #+#    #+#             */
/*   Updated: 2023/05/25 15:14:32 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd(char **paths, char *cmd)
{
    char *tmp;      // Chemin temporaire
    char *command;  // Chemin complet de la commande
    int i;     

    i = 0;
    while (paths[i]) // Tant que le chemin courant n'est pas nul
    {
        tmp = ft_strjoin(paths[i], "/");  // Concaténation du chemin du répertoire avec "/"
        command = ft_strjoin(tmp, cmd);   // Concaténation du chemin temporaire avec le nom de la commande
        free(tmp);                        // Libération de la mémoire allouée pour le chemin temporaire
        
        if (access(command, 0) == 0)  // Vérification de l'existence du fichier correspondant à "command"
            return (command);  // Retourne le chemin complet si le fichier est trouvé
        
        free(command);  // Libération de la mémoire allouée pour le chemin complet
        i++;   // Passage au chemin suivant
    }
    
    return (NULL);   // Retourne NULL si la commande n'est pas trouvée dans les chemins
}


/*
Ce code est utilisé pour exécuter la première commande dans un pipe.
Il effectue la redirection des descripteurs de fichiers et lance l'exécution de la commande + arg.*/
void exec_cmd_1(t_pipex pipex, int fd_in, char *argv[], char *envp[])
{
    dup2(pipex.fd[1], 1);  // Redirection de la sortie standard vers le descripteur d'écriture du pipe
    close(pipex.fd[0]);    // Fermeture du descripteur de lecture du pipe
    dup2(fd_in, 0);      // Redirection de l'entrée standard vers le descripteur de fichier d'entrée
    
    pipex.cmd_args = ft_split(argv[2], ' ');  // Découpage des arguments de commande
    pipex.cmd = get_cmd(pipex.access_paths_dir, pipex.cmd_args[0]); // Obtention du chemin complet de la commande
    
    if (!pipex.cmd)  // Si la commande n'est pas trouvée
    {
        free_cmd(&pipex);       // Libération de la mémoire allouée pour les arguments de commande
        perror("Command not found");  // Affichage d'un message d'erreur
        exit(EXIT_FAILURE);    // Sortie du programme avec un code d'échec
    }
    
    execve(pipex.cmd, pipex.cmd_args, envp);  // Exécution de la commande avec les arguments et l'environnement fournis
}

void	exec_cmd_2(t_pipex pipex, int fd_out, char *argv[], char *envp[])
{
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(fd_out, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.access_paths_dir, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_cmd(&pipex);
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}