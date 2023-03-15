/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:34:03 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/14 01:21:47 by kx               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

typedef int		(*t_builtin_func)(t_shell *shell, const t_cmd *cmd);

typedef struct s_builtin
{
	char	*name;
	t_builtin_func func;
}	t_builtin;

int	echo_builtin(t_shell *shell, const t_cmd *cmd);
int	exit_builtin(t_shell *shell, const t_cmd *cmd);
int	cd_builtin(t_shell *shell, const t_cmd *cmd);
int	pwd_builtin(t_shell *shell, const t_cmd *cmd);
int	env_builtin(t_shell *shell, const t_cmd *cmd);
int	unset_builtin(t_shell *shell, const t_cmd *cmd);
int	export_builtin(t_shell *shell, const t_cmd *cmd);

static const t_builtin	g_builtins[] = {
{"exit", exit_builtin},
{"echo", echo_builtin},
{"cd", cd_builtin},
{"pwd", pwd_builtin},
{"env", env_builtin},
{"unset", unset_builtin},
{"export", export_builtin},
{0}
};

#endif //BUILTINS_H
