/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:52:58 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 12:04:01 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "execution.h"
#include "types.h"
#include "libft.h"
#include "environment.h"
#include "utils.h"

static void	next_run(t_shell *shell)
{
	char		*line;
	const char	*shell_dir;
	char		prompt[1024];

	if (!shell->first_run)
	{
		if (shell->last_status)
			printf("KO ");
		else
			printf("OK ");
	}
	else
		shell->first_run = 0;
	shell_dir = get_shell_dir(shell);
	strcpy(prompt, "minishell [");
	strcat(prompt, shell_dir);
	strcat(prompt, "] $ ");
	free((char *)shell_dir);
	line = readline(prompt);
	if (!line)
		return ;
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
	while (!shell->exit)
		next_run(shell);
	rl_clear_history();
	clear_env(&shell->env);
	return (shell->last_status);
}

int	main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	return (minishell(environ));
}
