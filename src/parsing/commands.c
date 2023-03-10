/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:56:43 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 18:59:09 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "types.h"
#include "parsing.h"
#include "libft.h"

// use a while loop to count the number of commands
// in the while loop use get_arg_end to get the end of the command
static int	get_commands_len(char *line)
{
	int			len;
	const char	*arg_end;
	int			next_type;

	len = 0;
	arg_end = line;
	while (arg_end)
	{
		while (arg_end && !is_cmd_end(&next_type, (char *)arg_end))
		{
			while (*arg_end && (*arg_end == ' ' || *arg_end == '\t'))
				arg_end++;
			arg_end = get_arg_end((char *) arg_end);
		}
		if (!arg_end)
			return (0);
		len++;
		if (!*arg_end)
			break ;
		if (*(arg_end + 1) && (next_type == CT_REDIRECT_OUTAPP
				|| next_type == CT_REDIRECT_HEREDOC))
			arg_end++;
		arg_end++;
	}
	return (len);
}

t_cmd	*get_commands(t_shell *shell, char *line)
{
	t_cmd	*cmd;
	int		cmd_amount;
	int		i;

	cmd_amount = get_commands_len(line);
	cmd = ft_calloc(cmd_amount + 1, sizeof(t_cmd));
	cmd[cmd_amount] = (t_cmd){0};
	i = 0;
	line = parse_next_command(line, &cmd[i++], shell);
	while (line && *line)
		line = parse_next_command(line, &cmd[i++], shell);
	return (cmd);
}

void	free_commands(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].name)
	{
		free(cmd[i].name);
		ft_free_split(cmd[i].args);
		i++;
	}
	free(cmd);
}