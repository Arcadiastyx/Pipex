/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:54:42 by inaranjo          #+#    #+#             */
/*   Updated: 2023/05/25 15:19:09 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Fonction pour initialiser le descripteur de fichier en lecture
int init_fd_stdin(char *argv)
{
    int init;

    // Vérifier si le fichier existe si non error
    if (access(argv, F_OK) == 0)
        init = open(argv, O_RDONLY); // Ouvrir le fichier en lecture seule
    else
    {
        perror(argv); 
        return (EXIT_FAILURE); 
    }
    return (init); // Renvoyer le descripteur de fichier initialisé
}

// Fonction pour initialiser le descripteur de fichier en écriture
int init_fd_stdout(char *argv)
{
    int init;

    init = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    // Ouvrir le fichier en créant s'il n'existe pas, en écriture seule et en tronquant le fichier à zéro
    // Les permissions sont définies à 0644 (lecture et écriture pour l'utilisateur, lecture seule pour les autres)

    if (init == -1)
    {
        perror(argv); 
        return (EXIT_FAILURE); 
    }
    return (init); // Renvoyer le descripteur de fichier initialisé
}
