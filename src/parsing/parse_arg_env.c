/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:35:30 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 20:56:26 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "environment.h"
#include "libft.h"
#include "parsing.h"

static char	*parse_env_key(char *t)
{
	char	*key;
	int		i;

	i = 0;
	while (t[i] && (ft_isalnum(t[i]) || t[i] == '_'))
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

void	expand_arg(char **original, t_shell *shell)
{
	char	*o;
	int		double_quote;
	int		single_quote;

	double_quote = 0;
	single_quote = 0;
	o = *original;
	while (*o)
	{
		if (*o == '$' && !single_quote)
		{
			if (*(o + 1) == '?')
				o = insert_last_status(original, o, shell->last_status);
			else
				o = insert_env_var(original, o, shell->env);
			o--;
		}
		else if (*o == '*' && !single_quote && !double_quote)
			o = expand_wildcard(original, o);
		else if ((*o == '"' && !single_quote) || (*o == '\'' && !double_quote))
		{
			if (*o == '"')
				double_quote = !double_quote;
			else if (*o == '\'')
				single_quote = !single_quote;
			ft_memmove(o, o + 1, ft_strlen(o + 1) + 1);
			o--;
		}
		o++;
	}
}
