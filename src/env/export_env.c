/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:39:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 17:40:55 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:38:38 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 17:38:38 by kschmidt         ###   ########.fr       */
/*                                                                            */
#include <malloc.h>
#include "libft.h"
#include "types.h"

/* ************************************************************************** */

char	**export_env(t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize((t_list *) env) + 1));
	if (!envp)
		return (0);
	while (env)
	{
		envp[i] = ft_strnjoin(3, env->name, "=", env->value);
		if (!envp[i])
		{
			free(envp);
			return (0);
		}
		env = env->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}
