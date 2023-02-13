/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:09:05 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 04:21:16 by kschmidt         ###   ########.fr       */
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
