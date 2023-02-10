#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "history.h"
#include "libft.h"

int input_loop(void)
{
	char		*line;
	t_history	*history;

	history = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL || !ft_strncmp(line, "exit", 4))
			break ;
		history_add(&history, line);
		free(line);
	}
	history_print(history);
	history_free(history);
	return (0);
}

int	main(void)
{
	printf("Welcome to minishell by mabbas and kschmidt\n\n");
	input_loop();
	return (0);
}
