/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:08:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/14 23:03:36 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "types.h"
# include "builtins.h"

int	exec_pipeline(t_shell *shell, t_cmd *cmd, int len, int *status);
int	execute_internal(t_shell *shell, t_cmd *cmd, int *status);
int	execute(t_shell *shell, char *line, int *status);

#endif //EXECUTION_H
