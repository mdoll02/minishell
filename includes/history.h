#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_history
{
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

void		history_add(t_history **history, const char *cmd);
void		history_print(t_history *history);
void		history_free(t_history *history);

#endif