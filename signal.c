/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 15:16:45 by lizhang       #+#    #+#                 */
/*   Updated: 2023/02/15 18:30:59 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void	p_int_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_redisplay();
		write(1, "  ", 2);
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		write(1, "\e[1A\n", 6);
		rl_redisplay();
	}
}

void	p_quit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\e[1D", 5);
		write(1, "\e[1D", 5);
	}
}

void	c_signal_reset(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		return ;
}

void	sighandler(int signum)
{
	if (signum == SIGUSR1)
		close(STDIN_FILENO);
}

void	sig_input(int signum)
{
	if (signum == SIGINT)
	{
		rl_redisplay();
		write(1, "    ", 4);
		rl_replace_line("", 0);
		write(1, "\e[1A\n>", 7);
		write(1, "    \n", 6);
		close(0);
	}
}
