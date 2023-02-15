/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:35:51 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/15 17:50:20 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "parsing.h"

void	load_env(t_shell *shell, char **envp)
{
	char		**env;
	char		*key;
	char		*value;

	env = envp;
	shell->envc = 0;
	shell->secret_envc = 0;
	while (*env)
	{
		parse_env_var(*env, &key, &value);
		set_env(shell, key, value);
		set_secret_env(shell, key, value);
		free(key);
		env++;
	}
}
