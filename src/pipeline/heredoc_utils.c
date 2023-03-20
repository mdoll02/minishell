/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:26:25 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/20 10:26:25 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include <unistd.h>
#include <stdlib.h>

void	clear_heredoc(t_heredoc *doc)
{
	if (doc->name != NULL)
	{
		close(doc->fd);
		unlink(doc->name);
		free(doc->name);
	}
}

int	init_heredoc(t_cmd	**cmd, t_heredoc	*doc, t_fd_pipeline	*pl, \
					int *len)
{
	while ((*cmd)->next_type != CT_REDIRECT_HEREDOC)
	{
		(*cmd)++;
		len--;
	}
	(*cmd)++;
	if (here_doc(doc, (*cmd)->name, *cmd) != 0)
	{
		clear_heredoc(doc);
		return (1);
	}
	(*cmd)--;
	if ((*cmd)->name == NULL)
	{
		(*cmd)++;
		(*cmd)++;
		len -= 2;
	}
	else
		len--;
	pl->input_fd = doc->fd;
	return (0);
}
