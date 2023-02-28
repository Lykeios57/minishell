/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:35:03 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:35:39 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_exec(t_data *data, int flag)
{
	if (input_redirect(data) || output_redirect(data))
	{
		if (flag == 1)
			return ;
		else
			exit(1);
	}
	if (check_builtin(data->curr->cmd[0]))
		exec_builtin(data);
	else
		exec_non_builtin(data);
	if (flag != 1)
		exit(data->status);
}

int	run_process(t_data *data, pid_t pid, int fd[2], int prev_fd)
{
	signal(2, action);
	signal(3, action);
	if (pid > 0)
	{
		close(fd[1]);
		close(prev_fd);
		prev_fd = dup(fd[0]);
		close(fd[0]);
	}
	if (pid == 0)
	{
		dup2(prev_fd, 0);
		dup2(fd[1], 1);
		close(prev_fd);
		close(fd[1]);
		close(fd[0]);
		make_exec(data, 0);
	}
	return (prev_fd);
}

int	make_pipe(t_data *data, int prev_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_error(data, "pipe", EXEC_ERROR, 1);
		return (-1);
	}
	signal(2, SIG_DFL);
	signal(2, SIG_DFL);
	pid = fork();
	if (pid < 0)
	{
		ft_error(data, "fork", EXEC_ERROR, 1);
		return (-1);
	}
	prev_fd = run_process(data, pid, fd, prev_fd);
	return (prev_fd);
}

pid_t	exec_last(t_data *data, int prev_fd)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(2, SIG_DFL);
	signal(2, SIG_DFL);
	pid = fork();
	if (pid < 0)
	{
		ft_error(data, "fork", EXEC_ERROR, 1);
		return (-1);
	}
	if (pid > 0)
		close(prev_fd);
	if (pid == 0)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
		make_exec(data, 0);
	}
	return (pid);
}
