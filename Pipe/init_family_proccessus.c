/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_family_proccessus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:01:29 by inaranjo          #+#    #+#             */
/*   Updated: 2023/05/25 16:15:21 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*recherche la variable "PATH" parmi les variables d'environnement 
et renvoie la valeur de cette variable (les chemins d'accès) en excluant le préfixe "PATH=".
Cela permet d'obtenir les chemins d'accès nécessaires pour la recherche des commandes dans le système.
: 
(PATH=)\n
return (envp[i] + 5);/Users/inaranjo/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/inaranjo/.brew/bin*/
char *check_path(char *envp[])
{
    int i = 0;

    // Parcourt les variables d'environnement jusqu'à trouver la variable "PATH"
    while (envp[i] && !ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])))
    {
        i++;
    }
    // Retourne la valeur de la variable "PATH" en excluant les 5 premiers caractères (pour ignorer "PATH=")
    return (envp[i] + 5);
}


/*orchestre l'exécution de deux commandes pipelined en créant des processus enfants, 
en établissant une communication entre eux via un tube, en exécutant les command*/
void init_processus_family(int fd_stdin, int fd_stdout, char *argv[], char *envp[])
{
    t_pipex pipex;

    // Vérification des chemins d'accès dans les variables d'environnement
    pipex.paths = check_path(envp);

    // Découpage des chemins d'accès en commandes individuelles
    pipex.access_paths_dir = ft_split(pipex.paths, ':');

    // Création du tube (pipe) pour la communication entre les processus
    //aler voir : https://www.youtube.com/watch?v=Mqb2dVRe0uo&t=275s
    if (pipe(pipex.fd) < 0)
    {
        perror("Error Pipe : imposible de cree un pipe");
        exit(EXIT_FAILURE);
    }

    // Création du premier processus enfant[pid_child_1]
    pipex.pid_child_1 = fork();
    if (pipex.pid_child_1 == 0)
    {
        // Exécution de la première commande dans le premier processus enfant
        exec_cmd_1(pipex, fd_stdin, argv, envp);
    }

    // Création du deuxième processus enfant[pid_child_2]
    pipex.pid_child_2 = fork();
    if (pipex.pid_child_2 == 0)
    {
        // Exécution de la deuxième commande dans le deuxième processus enfant
       exec_cmd_2(pipex, fd_stdout, argv, envp);
    }

    // Fermeture des descripteurs de fichiers inutilisés par les processus enfants
    close_pipes(&pipex, fd_stdin, fd_stdout);

    // Attente de la terminaison des processus enfants
    waitpid(pipex.pid_child_1, NULL, 0);
    waitpid(pipex.pid_child_2, NULL, 0);

    // Libération des ressources utilisées par la structure pipex
    // no need it any more 
    free_access_path(&pipex);
}
