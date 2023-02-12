/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:14:00 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:06:11 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		first_run;
	int		last_status;
	int		exit;
	int		envc;
	t_env	*env;
}	t_shell;

typedef struct s_cmd
{
	char	*name;
	int		argc;
	char	**args;
}	t_cmd;

#endif //TYPES_H
