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

void	parse_env_var(char *env, char **key, char **value)
{
	*key = ft_strndup(env, ft_strchr(env, '=') - env);
	*value = ft_strchr(env, '=') + 1;
}
