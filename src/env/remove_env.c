/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:09:05 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/15 17:48:30 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "environment.h"

void	remove_env(t_shell *shell, const char *key)
{
	t_env	*env;
	t_env	*last;

	env = shell->env;
	last = 0;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			if (last)
				last->next = env->next;
			else
				shell->env = env->next;
			free(env->name);
			free(env->value);
			free(env);
			shell->envc--;
			return ;
		}
		last = env;
		env = env->next;
	}
}

void	remove_secret_env(t_shell *shell, const char *key)
{
	t_env	*env;
	t_env	*last;

	env = shell->secret_env;
	last = 0;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			if (last)
				last->next = env->next;
			else
				shell->secret_env = env->next;
			free(env->name);
			free(env->value);
			free(env);
			shell->secret_envc--;
			return ;
		}
		last = env;
		env = env->next;
	}
}
