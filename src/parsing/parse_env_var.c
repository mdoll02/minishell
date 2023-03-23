/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:35:29 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 04:38:11 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_env_var(char *env, char **key, char **value)
{
	char	*end;

	end = ft_strchr(env, '=');
	if (!end)
		return (1);
	*key = ft_strndup(env, end - env);
	*value = ft_strchr(env, '=') + 1;
	return (0);
}
