/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:46:00 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 12:51:14 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_arg_end(char *line)
{
	int		quotes;
	int		single_quotes;
	char	*name_end;

	quotes = 0;
	single_quotes = 0;
	name_end = line;
	while (*name_end && ((*name_end != ' ') || quotes % 2 || single_quotes % 2))
	{
		if (!single_quotes && !quotes && is_cmd_end(0, name_end))
			return (name_end);
		if (*name_end == '"' && !single_quotes)
			quotes++;
		if (*name_end == '\'' && !quotes)
			single_quotes++;
		name_end++;
	}
	if (quotes % 2 || single_quotes % 2)
		return (0);
	return (name_end);
}
