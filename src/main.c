/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:48:49 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 01:10:00 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <readline/readline.h>
#include "execution.h"
#include "types.h"
#include "libft.h"
#include "environment.h"
#include "utils.h"

static void	next_run(t_shell *shell)
{
	char		*line;
	const char	*shell_dir;

	if (!shell->first_run)
	{
		if (shell->last_status)
			printf("KO ");
		else
			printf("OK ");
	}
	shell_dir = get_shell_dir(shell);
	printf("minishell [%s]", shell_dir);
	free((char *)shell_dir);
	line = readline("$ ");
	shell->last_status = execute(shell, line);
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
	while (!shell->exit)
		next_run(shell);
	clear_env(&shell->env);
	return (0);
}

int	main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	minishell(environ);
	return (0);
}
