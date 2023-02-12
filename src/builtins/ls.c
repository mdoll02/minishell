/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:12:12 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:57:48 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include <dirent.h>

static void	print_dir(char *path)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(path);
	if (dir != NULL)
	{
		ent = readdir(dir);
		while (ent != NULL)
		{
			printf("%s ", ent->d_name);
			ent = readdir(dir);
		}
		printf("\b\n");
		closedir(dir);
	}
	else
	{
		printf("Error: could not open directory\n");
	}
}

int	ls_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	(void)shell;
	if (cmd->argc == 1)
		path = ".";
	else
		path = cmd->args[1];
	print_dir(path);
	return (0);
}
