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
