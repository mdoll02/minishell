/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:12:17 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 18:10:33 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include "signalhandlers.h"

void	register_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_forced_update_display();
}

void	handle_sigquit(int sig)
{
	int	be_funny;

	be_funny = 0;
	((((((((void)(((int)((((long)(((char)be_funny)))))) + sig))))))));
}
