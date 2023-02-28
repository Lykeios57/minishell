/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:48:55 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:29:30 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	outfile_node_clear(t_outfile_node	*nodes)
{
	t_outfile_node	*tmp;

	if (nodes == 0)
		return ;
	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		ft_free(tmp);
	}
}

void	infile_node_clear(t_infile_node	*nodes)
{
	t_infile_node	*tmp;

	if (nodes == 0)
		return ;
	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		if (tmp->is_heredoc)
			ft_free(tmp->file);
		ft_free(tmp);
	}
}

void	cmd_node_clear(t_cmd_node *nodes)
{
	t_cmd_node	*tmp;

	if (nodes == 0)
		return ;
	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		infile_node_clear(tmp->infile_node);
		outfile_node_clear(tmp->outfile_node);
		ft_free(tmp->cmd);
		ft_free(tmp);
	}
}

void	parse_node_clear(t_parsing_node	*nodes)
{
	t_parsing_node	*tmp;

	if (nodes == 0)
		return ;
	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		ft_free(tmp->str);
		ft_free(tmp);
	}
}

void	ft_free_data(t_data *data)
{
	cmd_node_clear(data->node_head);
	parse_node_clear(data->parse);
	ft_free(data->heredoc_node);
	ft_free(data);
}
