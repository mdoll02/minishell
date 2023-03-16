/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:48:55 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/16 11:48:55 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "execution.h"
#include "pipeline.h"
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "libft.h"

typedef struct s_heredoc
{
	char	name[5];
	int		fd;
}	t_heredoc;

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
	doc->fd = open("/dev/random", O_RDONLY);
	if (doc->fd < 0)
		return (1);
	read(doc->fd, doc->name, 5);
	close(doc->fd);
	doc->fd = open(doc->name, O_CREAT | O_EXCL | O_RDWR, 0644);
	return (0);
}

int	here_doc(char *limiter)
{
	t_heredoc	doc;
	char		*line;

	if (create_heredoc_file(&doc) < 0)
		return (1);
	line = NULL;
	while (limiter_found(line, limiter) == false)
	{
		readline(line);
	}
	close(doc.fd);
	unlink(doc.name);
	return (0);
}
