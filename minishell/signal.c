/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:51:48 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/18 19:33:11 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bombosignal.h"

int			g_exit_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	default_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	prompt_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

void	restore_signals(void)
{
	prompt_sig();
}

/*
handle_sigint :
C’est la fonction à utiliser quand on est dans le prompt (quand readline attend une commande). Elle gère Ctrl+C en nettoyant la ligne et en redessinant le prompt proprement. Elle met aussi $? à 130 (comme dans bash).
À utiliser dans le main loop avec prompt_sig().

sig_handler :
Fonction vide — elle sert à ignorer les signaux.
À utiliser dans les processus enfants (juste avant execve) avec default_sig(). Ça évite que Ctrl+C ou Ctrl+\ interfèrent avec eux pendant leur exécution.

default_sig() :
Associe SIGINT et SIGQUIT à sig_handler.
À appeler dans le processus enfant, pour désactiver les signaux personnalisés.

prompt_sig() :
Associe les signaux à handle_sigint.
À appeler dans la boucle principale,
	pour que notre shell réagisse bien aux Ctrl+C/Ctrl+\ pendant que l’utilisateur tape une commande.*/