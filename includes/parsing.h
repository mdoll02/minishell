/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:31:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 21:09:08 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <dirent.h>
# include "types.h"

char	*parse_next_command(char *line, t_cmd *cmd, t_shell *shell);
int		is_cmd_end(int *next_type, char *str);
void	parse_env_var(char *env, char **key, char **value);

char	*parse_next_arg(char *arg_start, int *offset, t_shell *shell);
char	*get_arg_end(char *line);

void	process_directory_entries(DIR *dir, char *pattern_start,
			char **expanded);
char	*get_pattern_start(const char *original, char *t);
char	*expand_wildcard(char **original, char *t);
void	expand_arg(char **original, t_shell *shell);

t_cmd	*get_commands(t_shell *shell, char *line);
int		get_command_arr_len(t_cmd *cmd);
void	free_commands(t_cmd *cmd);

char	*get_exec_path(char *name, t_env *env);

#endif //PARSING_H
