/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:35:51 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:41:07 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"

void	load_env(t_shell *shell, char **envp)
{
	char		**env;
	char		*key;
	char		*value;

	env = envp;
	while (*env)
	{
		key = ft_strndup(*env, ft_strchr(*env, '=') - *env);
		value = ft_strchr(*env, '=') + 1;
		set_env(shell, key, value);
		free(key);
		env++;
	}
}
