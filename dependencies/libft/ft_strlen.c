/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:57:18 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:27:00 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*s2;

	if (!s || !*s)
		return (0);
	s2 = s + 1;
	while (*s2)
		s2++;
	return (s2 - s);
}
