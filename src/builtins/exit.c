/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:36:49 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/15 17:59:35 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int	exit_builtin(t_shell *shell, const t_cmd *cmd)
{
	shell->exit = 1;
	return (ft_atoi(cmd->args[0]));
}
