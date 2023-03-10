/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_next_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 06:52:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 11:43:05 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

char	*parse_next_arg(char *arg_start, int *offset, t_shell *shell)
{
	char	*arg_end;
	char	*arg;

	while (arg_start[*offset] && (arg_start[*offset] == ' '
			|| arg_start[*offset] == '\t'))
		(*offset)++;
	arg_end = get_arg_end(arg_start + *offset);
	if (!arg_end)
		return (0);
	arg = ft_substr(arg_start, *offset, arg_end - (arg_start + *offset));
	expand_arg(&arg, shell);
	*offset = (int)(arg_end - arg_start);
	return (arg);
}
