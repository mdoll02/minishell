/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 06:50:38 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/17 08:15:26 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_arg_end(char *line)
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

void	remove_arg_quotes(char *str)
{
	int		i;
	int		j;
	int		quotes;
	int		single_quotes;

	i = 0;
	j = 0;
	quotes = 0;
	single_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' && !single_quotes)
			quotes = !quotes;
		if (str[i] == '\'' && !quotes)
			single_quotes = !single_quotes;
		if ((str[i] != '"' || single_quotes) && (str[i] != '\'' || quotes))
			str[j++] = str[i];
		i++;
	}
	str[j] = 0;
}
