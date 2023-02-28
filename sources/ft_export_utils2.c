/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:44:48 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:28:56 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_envp_node(t_env *curr, t_env *next)
{
	char	*temp_var;
	char	*temp_val;
	int		temp_idx;

	temp_idx = curr->idx;
	curr->idx = next->idx;
	next->idx = temp_idx;
	temp_var = curr->var;
	curr->var = next->var;
	next->var = temp_var;
	temp_val = curr->val;
	curr->val = next->val;
	next->val = temp_val;
}

void	restore_envp_order(t_data *data)
{
	t_env		*curr;
	int			i;
	int			j;

	i = 0;
	curr = data->envi->next;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	while (i)
	{
		j = 0;
		curr = data->envi->next;
		while (curr->next && j < i)
		{
			if (curr->idx > curr->next->idx)
				swap_envp_node(curr, curr->next);
			curr = curr->next;
			j++;
		}
		i--;
	}
}

void	envp_ascending_order(t_data *data)
{
	t_env	*curr;
	int		i;
	int		j;

	i = 0;
	curr = data->envi->next;
	while (curr)
	{
		curr->idx = i;
		curr = curr->next;
		i++;
	}
	while (i)
	{
		j = 0;
		curr = data->envi->next;
		while (curr->next && j < i)
		{
			if (ft_strcmp(curr->var, curr->next->var) > 0)
				swap_envp_node(curr, curr->next);
			curr = curr->next;
			j++;
		}
		i--;
	}
}
