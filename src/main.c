/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:48:49 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/12 23:10:38 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "execution.h"

int	minishell(void)
{
	char	*line;
	int		status;

	status = 1;
	line = readline("minishell$ ");
	while (status)
	{
		status = execute(line);
		free(line);
		if (status)
			line = readline("KO minishell$ ");
		else
			line = readline("OK minishell$ ");
	}
	return (0);
}

int	main(void)
{
	minishell();
	return (0);
}
