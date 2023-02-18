/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_next_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 06:52:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 06:08:29 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

char	*parse_next_arg(char *arg_start, int *offset)
{
	char	*name_end;
	char	*arg;
	char	*tmp;

	while (arg_start[*offset] && (arg_start[*offset] == ' '
			|| arg_start[*offset] == '\t'))
		(*offset)++;
	name_end = get_arg_end(arg_start + *offset);
	if (!name_end)
		return (0);
	tmp = ft_substr(arg_start, *offset, name_end - (arg_start + *offset));
	arg = remove_arg_quotes(tmp);
	*offset = (int)(name_end - arg_start);
	return (arg);
}
