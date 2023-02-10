#include "history.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	history_add(t_history **history, const char *cmd)
{
	t_history	*new;

	if (!history)
		return ;
	new = malloc(sizeof(t_history));
	new->cmd = ft_strdup(cmd);
	new->next = 0;
	new->prev = *history;
	if (*history)
		(*history)->next = new;
	*history = new;
}

void	history_print(t_history *history)
{
	while (history)
	{
		printf("%s\n", history->cmd);
		history = history->prev;
	}
}

void	history_free(t_history *history)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history;
		history = history->prev;
		free(tmp->cmd);
		free(tmp);
	}
}
