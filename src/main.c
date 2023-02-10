#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int input_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;

		free(line);
	}
	return (0);
}

int	main(void)
{
	printf("Welcome to minishell by mabbas and kschmidt\n\n");
	input_loop();
	return (0);
}
