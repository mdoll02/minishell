/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:14:00 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 12:37:21 by kschmidt         ###   ########.fr       */
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

# define CT_END 0
# define CT_PIPE 1
# define CT_REDIRECT_IN 2
# define CT_REDIRECT_OUT 3
# define CT_REDIRECT_OUTAPP 4
# define CT_REDIRECT_HEREDOC 5

static const struct {
	char	*name;
	int		type;
	int		len;
} s_c_type[] = {
	{"|", CT_PIPE, 1},
	{">", CT_REDIRECT_OUT, 1},
	{"<", CT_REDIRECT_IN, 1},
	{"<<", CT_REDIRECT_HEREDOC, 2},
	{">>", CT_REDIRECT_OUTAPP, 2},
	{"\0", CT_END, 1},
	{0, 0, 0}
};

typedef struct s_cmd
{
	char	*name;
	int		argc;
	char	**args;
	int		next_type;
}	t_cmd;

#endif //TYPES_H
