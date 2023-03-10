/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_next_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 06:52:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 12:55:38 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	is_cmd_end(int *next_type, char *str)
{
	int	i;

	i = 0;
	while (s_c_type[i].name)
	{
		if (!ft_memcmp(str, s_c_type[i].name, s_c_type[i].len))
			break ;
		i++;
	}
	if (s_c_type[i].name)
	{
		if (next_type)
			*next_type = s_c_type[i].type;
		return (1);
	}
	return (0);
}

char	*parse_next_arg(char *arg_start, int *offset, t_shell *shell)
{
	char	*arg_end;
	char	*arg;

	while (arg_start[*offset] && (arg_start[*offset] == ' '
			|| arg_start[*offset] == '\t'))
		(*offset)++;
	arg_end = get_arg_end(arg_start + *offset);
	if (!arg_end || arg_end == arg_start + *offset)
		return (0);
	arg = ft_substr(arg_start, *offset, arg_end - (arg_start + *offset));
	expand_arg(&arg, shell);
	*offset = (int)(arg_end - arg_start);
	return (arg);
}
