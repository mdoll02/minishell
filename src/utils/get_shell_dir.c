/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:05:35 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 17:21:15 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"
#include "environment.h"
#include "libft.h"

char	*get_shell_dir(t_shell *shell)
{
	char		*shell_dir;
	const char	*home_dir;
	size_t		home_dir_len;

	shell_dir = getcwd(0, 0);
	home_dir = get_env_nc(shell->secret_env, "HOME");
	home_dir_len = ft_strlen(home_dir);
	if (ft_strncmp(shell_dir, home_dir, home_dir_len) == 0)
	{
		shell_dir[0] = '~';
		ft_memmove(shell_dir + 1, shell_dir + home_dir_len,
			ft_strlen(shell_dir + home_dir_len) + 1);
	}
	return (shell_dir);
}
