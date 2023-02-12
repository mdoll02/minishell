/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:48:49 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:29:47 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <readline/readline.h>
#include "execution.h"
#include "types.h"
#include "libft.h"
#include "environment.h"

static void	next_run(t_shell *shell)
{
	char	*line;

	if (shell->first_run)
	{
		shell->first_run = 0;
		line = readline("minishell$ ");
	}
	else if (shell->last_status)
		line = readline("KO minishell$ ");
	else
		line = readline("OK minishell$ ");
	shell->last_status = execute(shell, line);
	free(line);
}

static int	minishell(void)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (1);
	shell->first_run = 1;
	while (!shell->exit)
		next_run(shell);
	clear_env(&shell->env);
	return (0);
}

int	main(void)
{
	minishell();
	return (0);
}
