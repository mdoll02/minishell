/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:36:39 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 12:52:45 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
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

static char	*get_pattern_start(char *original, char *t)
{
	char	*patternstart;

	patternstart = t;
	while (patternstart > original && *(patternstart - 1) != ' ')
		patternstart--;

	return (patternstart);
}

static void	process_directory_entries(DIR *dir, char *pattern_start,
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

static void	update_original_string(char **original, const char *pattern_start,
					char *t, char *expanded)
{
	size_t	prefix_len;
	size_t	expanded_len;
	size_t	new_len;
	char	*new_str;

	prefix_len = pattern_start - *original;
	if (expanded)
		expanded_len = ft_strlen(expanded);
	else
		expanded_len = 0;
	new_len = prefix_len + expanded_len + ft_strlen(t + 1) + 1;
	new_str = malloc(new_len);
	ft_memcpy(new_str, *original, prefix_len);
	if (expanded)
	{
		ft_memcpy(new_str + prefix_len, expanded, expanded_len);
		free(expanded);
	}
	ft_strlcpy(new_str + prefix_len + expanded_len, t + 1, strlen(t + 1) + 1);
	free(*original);
	*original = new_str;
}

void	expand_wildcard(char **original, char *t)
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
}
