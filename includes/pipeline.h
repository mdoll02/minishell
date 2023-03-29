/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:13:30 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 12:14:01 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdbool.h>
# include "types.h"

typedef struct s_fd_pipeline
{
	int	input_fd;
	int	output_fd;
	int	pipe_fd[2];
}	t_fd_pipeline;

typedef struct s_heredoc
{
	char	name[19];
	int		fd;
}	t_heredoc;

int			handle_pipe_case(t_shell *shell, t_cmd *cmd, int *status, \
								t_fd_pipeline *pl);
int			redirect_input(t_cmd **cmd);
int			redirect_output(t_cmd *cmd);
int			here_doc(t_heredoc *doc, char *limiter, t_cmd *cmd);
bool		check_for_heredoc(t_cmd *cmd, int len);
void		clear_heredoc(t_heredoc *doc);
int			init_heredoc(t_cmd	**cmd, t_heredoc	*doc, t_fd_pipeline	*pl, \
								int *len);

#endif
