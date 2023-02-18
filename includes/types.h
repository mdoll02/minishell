/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:14:00 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 08:27:01 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_env
{
	char			*name;
	struct s_env	*next;
	char			*value;
}	t_env;

typedef struct s_shell
{
	int		first_run;
	int		last_status;
	int		exit;
	int		envc;
	t_env	*env;
	int		secret_envc;
	t_env	*secret_env;
}	t_shell;

typedef struct s_cmd
{
	char	*name;
	int		argc;
	char	**args;
}	t_cmd;

#endif //TYPES_H
