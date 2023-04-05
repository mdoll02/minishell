/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:16:03 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/15 17:55:52 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "environment.h"

void	set_env(t_shell *shell, char *key, const char *value)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = malloc(sizeof(t_env));
	env->name = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = shell->env;
	shell->env = env;
	shell->envc++;
}

void	set_secret_env(t_shell *shell, char *key, const char *value)
{
	t_env	*env;

	env = shell->secret_env;
	while (env)
	{
		if (ft_strncmp(env->name, key, ft_strlen(key)) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = malloc(sizeof(t_env));
	env->name = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = shell->secret_env;
	shell->secret_env = env;
	shell->secret_envc++;
}
