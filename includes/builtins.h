/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:34:03 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:53:44 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_shell *shell, t_cmd *cmd);
}	t_builtin;

int	echo_builtin(t_shell *shell, t_cmd *cmd);
int	exit_builtin(t_shell *shell, t_cmd *cmd);
int	cd_builtin(t_shell *shell, t_cmd *cmd);
int	ls_builtin(t_shell *shell, t_cmd *cmd);

const static t_builtin	g_builtins[] = {
{"exit", exit_builtin},
{"echo", echo_builtin},
{"cd", cd_builtin},
{"ls", ls_builtin},
{0}
};

#endif //BUILTINS_H
