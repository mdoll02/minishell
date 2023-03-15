/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:07:22 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 21:08:18 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "libft.h"

static int	simple_pattern_match(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == '?' || *pattern == *str)
		return (simple_pattern_match(pattern + 1, str + 1));
	if (*pattern == '*')
		return (simple_pattern_match(pattern + 1, str)
			|| simple_pattern_match(pattern, str + 1));
	return (0);
}

static void	append_expanded_string(char **expanded, const char *matched)
{
	size_t	expanded_len;
	size_t	matched_len;
	char	*new_expanded;

	if (*expanded)
		expanded_len = ft_strlen(*expanded);
	else
		expanded_len = 0;

	matched_len = ft_strlen(matched);
	new_expanded = malloc(expanded_len + matched_len + 2);

	if (expanded_len > 0)
	{
		ft_memcpy(new_expanded, *expanded, expanded_len);
		new_expanded[expanded_len] = ' ';
		expanded_len++;
	}

	ft_memcpy(new_expanded + expanded_len, matched, matched_len);
	new_expanded[expanded_len + matched_len] = '\0';

	free(*expanded);
	*expanded = new_expanded;
}

void	process_directory_entries(DIR *dir, char *pattern_start,
									char **expanded)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (simple_pattern_match(pattern_start, entry->d_name))
			append_expanded_string(expanded, entry->d_name);
		entry = readdir(dir);
	}
}

char	*get_pattern_start(const char *original, char *t)
{
	char	*pattern_start;

	pattern_start = t;
	while (pattern_start > original && *(pattern_start - 1) != ' ')
		pattern_start--;

	return (pattern_start);
}