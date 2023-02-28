/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:16:33 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:33:30 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_cmd_list(t_parsing_node *parse, t_data *data)
{
	t_parsing_node	*p_now;
	t_cmd_node		*c_now;
	int				i;

	p_now = parse;
	i = 0;
	c_now = data->node_head;
	while (p_now && data->cmd_num != -1)
	{
		if (p_now->type == PIPE)
		{
			if (check_pipe_err(parse, p_now))
			{
				data->status = 258;
				data->cmd_num = -1;
				break ;
			}
			i++;
			c_now->next = new_cmd_node(&p_now, i, data);
			c_now = c_now->next;
		}
		p_now = p_now->next;
	}
	if (data->cmd_num != -1)
		data->cmd_num = i;
}

t_cmd_node	*new_cmd_node(t_parsing_node **parse, int i, t_data *data)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		exit (1);
	init_cmd_node(node);
	node->idx = i;
	node->cmd = set_cmd(*parse, data);
	node->infile_node = ft_malloc(sizeof(t_infile_node));
	node->outfile_node = ft_malloc(sizeof(t_outfile_node));
	set_red_lst(*parse, node, data);
	return (node);
}

char	**set_cmd(t_parsing_node *parsing, t_data *data)
{
	t_parsing_node	*now;
	char			**cmd;
	int				index;

	now = parsing->next;
	index = 0;
	cmd = malloc(sizeof(char *) * (get_cmd_num(parsing, data) + 1));
	if (!cmd)
		exit (1);
	while (now && now->type != PIPE)
	{
		if (now->type != WORD)
		{
			if (now->next == NULL || now->next->type != WORD)
				break ;
			now = now->next;
		}
		else if (now->str)
			cmd[index++] = now->str;
		now = now->next;
	}
	cmd[index] = NULL;
	return (cmd);
}

int	get_cmd_num(t_parsing_node *parsing, t_data *data)
{
	t_parsing_node	*now;
	int				i;

	i = 0;
	now = parsing->next;
	while (now && now->type != PIPE)
	{
		if (now->type == RED_A || now->type == RED_H
			|| now->type == RED_I || now->type == RED_O)
		{
			if (check_red_err(now))
			{
				data->status = 258;
				data->cmd_num = -1;
				return (0);
			}
			now = now->next;
		}
		i++;
		now = now->next;
	}
	return (i);
}

void	init_cmd_node(t_cmd_node *node)
{
	node->idx = 0;
	node->cmd = NULL;
	node->infile_node = NULL;
	node->outfile_node = NULL;
	node->next = NULL;
}
