/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:34:03 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:11:12 by kschmidt         ###   ########.fr       */
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

#endif //BUILTINS_H
