/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:14:00 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/12 23:18:01 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_shell
{
	int	first_run;
	int	last_status;
	int	exit;
}	t_shell;

typedef struct s_cmd
{
	char	*name;
	char	**args;
}	t_cmd;

#endif //TYPES_H
