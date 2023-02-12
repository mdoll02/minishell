/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/12 23:51:37 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	parse_command(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd->name = ft_substr(line, 0, i);
	cmd->args = ft_split(line, ' ');
	cmd->argc = ft_arraylen(cmd->args);
	return (0);
}
