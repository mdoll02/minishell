/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:52:58 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/16 13:44:54 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "signalhandlers.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "execution.h"
#include "types.h"
#include "libft.h"
#include "environment.h"
#include "utils.h"

static void	handle_first_run(t_shell *shell)
{
	if (shell->first_run)
	{
		printf("Welcome to minishell v0.7 by mdoll and kschmidt!\n");
		shell->first_run = 0;
		return ;
	}
	if (shell->last_status)
		printf("KO ");
	else
		printf("OK ");
}

static void	next_run(t_shell *shell)
{
	char		*line;
	const char	*shell_dir;
	char		prompt[1024];

	handle_first_run(shell);
	shell_dir = get_shell_dir(shell);
	ft_strlcpy(prompt, "minishell [", 1024);
	ft_strlcat(prompt, shell_dir, 1024);
	ft_strlcat(prompt, "] $ ", 1024);
	free((char *)shell_dir);
	line = readline(prompt);
	if (!line)
	{
		shell->exit = 1;
		return ;
	}
	if (*line)
		add_history(line);
	execute(shell, line, &shell->last_status);
	free(line);
}

static int	minishell(char **environ)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (1);
	shell->first_run = 1;
	load_env(shell, environ);
	using_history();
	register_signals();
	while (!shell->exit)
		next_run(shell);
	clear_history();
	clear_env(&shell->env);
	return (shell->last_status);
}

int	main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	return (minishell(environ));
}
