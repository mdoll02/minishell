/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:33:47 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 04:40:02 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtins.h"
#include "parsing.h"
#include "environment.h"

int	export_builtin(t_shell *shell, const t_cmd *cmd)
{
	char	*name;
	char	*value;

	if (!cmd->args[0])
		return (env_builtin(shell, cmd));
	if (parse_env_var(cmd->args[0], &name, &value))
		return (0);
	set_env(shell, name, value);
	free(name);
	return (0);
}
