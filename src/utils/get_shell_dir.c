/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:05:35 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 01:10:09 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "environment.h"
#include "libft.h"

char	*get_shell_dir(t_shell *shell)
{
	const char	*shell_dir;
	const char	*home_dir;
	size_t		home_dir_len;

	shell_dir = get_env_nc(shell->env, "PWD");
	home_dir = get_env_nc(shell->env, "HOME");
	home_dir_len = ft_strlen(home_dir);
	if (ft_strncmp(shell_dir, home_dir, home_dir_len) == 0)
		return (ft_strjoin("~", shell_dir + ft_strlen(home_dir)));
	return (get_env(shell->env, "PWD"));
}
