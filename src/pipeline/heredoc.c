/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:48:55 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/18 16:37:58 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "pipeline.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"

bool	check_for_heredoc(t_cmd *cmd, int len)
{
	while (len--)
	{
		if (cmd->next_type == CT_REDIRECT_HEREDOC)
			return (true);
		cmd++;
	}
	return (false);
}

static bool	limiter_found(char *line, char *limiter)
{
	if (!line)
		return (false);
	if (ft_strcmp(line, limiter) == 0)
		return (true);
	return (false);
}

static int	create_heredoc_file(t_heredoc *doc)
{
	int	i;

	i = 0;
	doc->fd = open("/dev/random", O_RDONLY);
	if (doc->fd < 0)
		return (1);
	read(doc->fd, doc->name, 5);
	close(doc->fd);
	while (i < 5)
	{
		doc->name[i] = (char)(doc->name[i] % 26 + 'a');
		i++;
	}
	doc->name[i] = 0;
	doc->name = ft_strjoin(doc->name, ".heredoc");
	if (!doc->name)
		return (1);
	doc->fd = open(doc->name, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (doc->fd < 1)
	{
		perror ("open");
		return (1);
	}
	return (0);
}

int	here_doc(t_heredoc *doc, char *limiter, t_cmd *cmd)
{
	char		*line;

	(void)cmd;
	doc->name = malloc(sizeof(char) * 6);
	if (!doc->name)
		return (1);
	if (create_heredoc_file(doc) != 0)
		return (1);
	while (1)
	{
		line = readline("🤨 > ");
		if (limiter_found(line, limiter) == true)
			break ;
		write(doc->fd, line, ft_strlen(line));
		write(doc->fd, "\n", 1);
	}
	free(line);
	close (doc->fd);
	doc->fd = open(doc->name, O_RDONLY);
	if (doc->fd < 1)
	{
		perror ("open");
		return (1);
	}
	return (0);
}
