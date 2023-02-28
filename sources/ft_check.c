/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:14:34 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 19:46:10 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") || \
		!ft_strcmp(str, "pwd") || !ft_strcmp(str, "export") || \
		!ft_strcmp(str, "unset") || !ft_strcmp(str, "env") || \
		!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	no_cmd(t_data *data, int flag)
{
	if (flag == 0)
	{
		if (!(data->node_head->next) || !(data->node_head->next->cmd) || \
		!(data->node_head->next->cmd[0]))
		{
			input_redirect(data);
			output_redirect(data);
			return (1);
		}
	}
	else if (flag == 1)
	{
		if (!(data->curr->cmd) || !(data->curr->cmd[0]))
		{
			input_redirect(data);
			output_redirect(data);
			return (1);
		}
	}
	return (0);
}

int	only_one_builtin(t_data *data)
{
	if (data->cmd_num == 1 && check_builtin(data->curr->cmd[0]))
	{
		make_exec(data, 1);
		return (1);
	}
	return (0);
}

void	run_waitpid(t_data *data, int pid, int i)
{
	int			sig;
	int			res;
	int			status;

	signal(2, SIG_IGN);
	signal(3, SIG_IGN);
	res = waitpid(-1, &status, 0);
	signal(2, action);
	signal(3, action);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT && i == 0)
		{
			printf("\n");
		}
		else if (sig == SIGQUIT && i >= 0)
		{
			return ;
		}
		if (res == pid)
			data->status = 128 + sig;
	}
	if (res == pid && WIFEXITED(status))
		data->status = WEXITSTATUS(status);
}

int	run_command(t_data *data)
{
	int			prev_fd;
	int			i;
	int			pid;

	i = -1;
	prev_fd = dup(0);
	if (only_one_builtin(data))
		return (0);
	while (++i < data->cmd_num - 1)
	{
		prev_fd = make_pipe(data, prev_fd);
		if (prev_fd == -1)
			return (1);
		data->curr = data->curr->next;
	}
	pid = exec_last(data, prev_fd);
	i = -1;
	while (++i < data->cmd_num)
		run_waitpid(data, pid, i);
	return (0);
}
