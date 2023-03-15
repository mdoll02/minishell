/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:10:39 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/15 12:15:09 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALHANDLERS_H
# define SIGNALHANDLERS_H

void	handle_sigint(int sig);
void	handle_sigquit(int sig);

void	register_signals(void);

#endif //SIGNALHANDLERS_H
