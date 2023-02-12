/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:08:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/12 23:26:36 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "libft.h"

int	check_builtin(t_shell *shell, char *line, int *status)
{
	if (ft_memcmp(line, "exit", 5) == 0 || ft_memcmp(line, "exit ", 5) == 0)
	{
		shell->exit = 1;
		*status = 0;
	}
	else
		return (0);
	return (1);
}

int	execute(t_shell *shell, char *line)
{
	int	status;

	if (check_builtin(shell, line, &status))
		return (status);
	return (1);
}
