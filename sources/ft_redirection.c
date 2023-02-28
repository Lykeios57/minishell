/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:56:50 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:39:12 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_heredoc(t_data *data)
{
	t_infile_node	*curr;

	if (!data->heredoc_node)
		return ;
	curr = data->heredoc_node->hnext;
	while (curr)
	{
		unlink(curr->file);
		curr = curr->hnext;
	}
}

int	input_redirect(t_data *data)
{
	t_infile_node	*curr;
	int				input_fd;

	curr = data->curr->infile_node;
	while (curr)
	{
		if (curr->file)
		{
			input_fd = open(curr->file, O_RDONLY);
			if (input_fd >= 0)
			{
				dup2(input_fd, 0);
				close(input_fd);
			}
			else
				return (ft_errcm(data, NULL, curr->file, 1));
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_fdout(t_outfile_node *curr, int fd_out)
{
	fd_out = open(curr->file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	return (fd_out);
}

int	ft_fdoutapp(t_outfile_node *curr, int fd_out)
{
	fd_out = open(curr->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (fd_out);
}

int	output_redirect(t_data *data)
{
	t_outfile_node	*curr;
	int				fd_out;

	curr = data->curr->outfile_node;
	while (curr)
	{
		if (curr->file)
		{
			if (curr->type == 0)
				fd_out = ft_fdout(curr, fd_out);
			else
				fd_out = ft_fdoutapp(curr, fd_out);
			if (fd_out >= 0)
			{
				dup2(fd_out, 1);
				close(fd_out);
			}
			else
				return (ft_errcm(data, NULL, curr->file, 1));
		}
		curr = curr->next;
	}
	return (0);
}
