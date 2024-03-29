/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:32:44 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 08:58:47 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "environment.h"
#include "libft.h"

static char	*find_executable_in_path(char *name, const char *path)
{
	const char	*p;
	const char	*end;
	char		*exec_path;
	char		*tmp;

	p = path;
	while (*p)
	{
		end = ft_strchr(p, ':');
		if (!end)
			end = p + ft_strlen(p);
		if (end - p > 0)
		{
			tmp = ft_substr(p, 0, end - p);
			exec_path = ft_strnjoin(3, tmp, "/", name);
			free(tmp);
			if (exec_path && access(exec_path, X_OK) == 0)
				return (exec_path);
			free(exec_path);
		}
		p++;
	}
	return (0);
}

char	*get_exec_path(char *name, t_env *env)
{
	const char	*path;
	struct stat	filestat;

	if (ft_strchr(name, '/') != 0 || name[0] == '.')
	{
		if (access(name, X_OK) == 0
			&& stat(name, &filestat) == 0 && !S_ISDIR(filestat.st_mode))
			return (ft_strdup(name));
		return (0);
	}
	path = get_env_nc(env, "PATH");
	if (!path)
		return (0);
	return (find_executable_in_path(name, path));
}
