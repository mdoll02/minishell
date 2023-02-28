/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:04:02 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/28 19:19:43 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "types.h"
#include "libft.h"

int	env_builtin(t_shell *shell, const t_cmd *cmd)
{
	t_env	*env;

	if (cmd->argc)
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		return (1);
	}
	env = shell->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
