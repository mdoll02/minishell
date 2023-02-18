/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:35:30 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 06:22:37 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "environment.h"
#include "libft.h"

static char	*parse_env_key(char *t)
{
	char	*key;
	int		i;

	i = 0;
	while (t[i] && t[i] != ' ' && t[i] != '\t')
		i++;
	key = malloc(i + 1);
	ft_strlcpy(key, t, i + 1);
	return (key);
}

static char	*insert_env_var(char **original, char *t, t_env *env)
{
	char	*new;
	char	*env_value;
	size_t	token_len;
	char	*env_key;

	env_key = parse_env_key(t + 1);
	env_value = get_env(env, env_key);
	if (!env_value)
		env_value = ft_strdup("");
	token_len = ft_strlen(env_key) + 1;
	new = malloc(ft_strlen(*original) + ft_strlen(env_value) - token_len
			+ ft_strlen(t + token_len) + 1);
	ft_strlcpy(new, *original, t - *original + 1);
	ft_strlcat(new, env_value, ft_strlen(*original) + ft_strlen(env_value)
		- token_len + 1);
	ft_strlcat(new, t + token_len, ft_strlen(*original) + ft_strlen(env_value)
		- token_len + ft_strlen(t + token_len) + 1);
	t = new + (t - *original) + ft_strlen(env_value);
	free(*original);
	*original = new;
	free(env_key);
	free(env_value);
	return (t);
}

static char	*insert_last_status(char **original, char *t, int last_status)
{
	char	*new;
	char	*env_value;

	env_value = ft_itoa(last_status);
	if (!env_value)
		return (t);
	new = malloc(ft_strlen(*original) + ft_strlen(env_value) - 1
			+ ft_strlen(t + 1) + 1);
	ft_strlcpy(new, *original, t - *original + 1);
	ft_strlcat(new, env_value, ft_strlen(*original) + ft_strlen(env_value)
		- 1 + 1);
	ft_strlcat(new, t + 2, ft_strlen(*original) + ft_strlen(env_value)
		- 1 + ft_strlen(t + 1) + 1);
	t = new + (t - *original) + ft_strlen(env_value);
	free(*original);
	free(env_value);
	*original = new;
	return (t);
}

static void	replace_arg_env(char **original, t_shell *shell)
{
	char	*o;

	o = *original;
	while (*o && *(o + 1))
	{
		if (*o == '$')
		{
			if (*(o + 1) == '?')
				o = insert_last_status(original, o, shell->last_status);
			else
				o = insert_env_var(original, o, shell->env);
		}
		o++;
	}
}

void	parse_arg_env(char **args, t_shell *shell)
{
	char	**arg;

	arg = args;
	while (*arg)
	{
		replace_arg_env(arg, shell);
		arg++;
	}
}
