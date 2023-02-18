/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:31:21 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 06:10:08 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

int		parse_command(char *line, t_cmd *cmd, t_shell *shell);
void	parse_env_var(char *env, char **key, char **value);

char	*parse_next_arg(char *arg_start, int *offset);
char	*get_arg_end(char *line);

char	*remove_arg_quotes(char *str);
void	parse_arg_env(char **args, t_shell *shell);

char	*get_exec_path(char *name, t_env *env);

#endif //PARSING_H
