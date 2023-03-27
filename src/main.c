/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:52:58 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/27 15:23:11 by kschmidt         ###   ########.fr       */
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

static char	*show_prompt(t_shell *shell)
{
	char		prompt[1024];
	const char	*shell_dir;

	*prompt = 0;
	if (shell->first_run)
	{
		printf("Welcome to minishell v0.7 by mdoll and kschmidt!\n");
		shell->first_run = 0;
	}
	else
	{
		if (shell->last_status)
			ft_strlcat(prompt, "KO ", 1024);
		else
			ft_strlcat(prompt, "OK ", 1024);
	}
	shell_dir = get_shell_dir(shell);
	ft_strlcat(prompt, "minishell [", 1024);
	ft_strlcat(prompt, shell_dir, 1024);
	ft_strlcat(prompt, "] $ ", 1024);
	free((char *)shell_dir);
	return (readline(prompt));
}

static void	next_run(t_shell *shell)
{
	char		*line;

	line = show_prompt(shell);
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
	t_shell	shell;

	bzero(&shell, sizeof(t_shell));
	shell.first_run = 1;
	load_env(&shell, environ);
	using_history();
	register_signals();
	while (!shell.exit)
		next_run(&shell);
	clear_history();
	clear_env(&shell.env);
	clear_env(&shell.secret_env);
	return (shell.last_status);
}

int	main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	return (minishell(environ));
}
