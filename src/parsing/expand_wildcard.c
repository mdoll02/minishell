/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:36:39 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 21:10:23 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "libft.h"
#include "parsing.h"

static char	*get_wildcard_end(char *t)
{
	while (*t != '\0' && *t != ' ' && *t != '\t')
		t++;
	return (t);
}

static char	*create_new_string(char *original, const char *pattern_start,
					char *t, char *expanded)
{
	size_t	prefix_len;
	char	*wildcard_end;
	size_t	new_len;
	char	*new_str;
	size_t	expanded_len;

	expanded_len = 0;
	if (expanded)
		expanded_len = ft_strlen(expanded);
	prefix_len = pattern_start - original;
	wildcard_end = get_wildcard_end(t + 1);
	new_len = prefix_len + expanded_len + strlen(wildcard_end) + 1;
	new_str = malloc(new_len);
	ft_memcpy(new_str, original, prefix_len);
	if (expanded_len > 0)
		ft_memcpy(new_str + prefix_len, expanded, expanded_len);
	strcpy(new_str + prefix_len + expanded_len, wildcard_end);
	return (new_str);
}

static char	*update_original_string(char **original, const char *pattern_start,
				char *t, char *expanded)
{
	char	*new_str;
	char	*new_wildcard_end;

	new_str = create_new_string(*original, (char *)pattern_start, t, expanded);
	new_wildcard_end = new_str + (get_wildcard_end(t + 1) - *original)
		+ ft_strlen(expanded);
	if (expanded)
		free(expanded);
	free(*original);
	*original = new_str;
	return (new_wildcard_end);
}

char	*expand_wildcard(char **original, char *t)
{
	DIR		*dir;
	char	*pattern_start;
	char	*expanded;

	expanded = 0;
	pattern_start = get_pattern_start(*original, t);
	dir = opendir(".");
	if (dir)
	{
		process_directory_entries(dir, pattern_start, &expanded);
		closedir(dir);
		update_original_string(original, pattern_start, t, expanded);
	}
	else
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	return (*original);
}
