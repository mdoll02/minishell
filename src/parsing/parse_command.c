/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/16 21:50:31 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

char	*parse_name(char *line)
{
	int		quotes;
	int		single_quotes;
	char	*name_end;

	quotes = 0;
	single_quotes = 0;
	name_end = line;
	while (*name_end && (*name_end != ' ' || quotes % 2 || single_quotes % 2))
	{
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

int	parse_command(char *line, t_cmd *cmd)
{
	int	i;
	int	start;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	i = (int)(parse_name(line + i) - line);
	if (i <= start)
		return (1);
	cmd->name = ft_substr(line, start, i); // TODO: remove quotes from substr
	cmd->args = ft_split(line, ' ');
	cmd->argc = ft_arraylen(cmd->args);
	return (0);
}
