/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:13:14 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/28 19:17:47 by kschmidt         ###   ########.fr       */
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
	if (!dir)
	{
		ent = readdir(dir);
		while (!ent)
		{
			printf("%s ", ent->d_name);
			ent = readdir(dir);
		}
		printf("\b\n");
		closedir(dir);
	}
	else
		printf("Error: could not open directory\n");
}

int	ls_builtin(t_shell *shell, const t_cmd *cmd)
{
	char	*path;

	(void)shell;
	if (cmd->argc == 0)
		path = ".";
	else
		path = cmd->args[0];
	print_dir(path);
	return (0);
}
