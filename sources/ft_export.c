/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:01:34 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:26:30 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*make_envp_node(char *var, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	new->val = ft_strdup(val);
	new->next = NULL;
	return (new);
}

void	add_env(t_data *data, char *var, char *val)
{
	t_env	*curr;
	t_env	*pre;

	curr = data->envi->next;
	pre = data->envi;
	while (curr)
	{
		if (!ft_strcmp(curr->var, var))
		{
			if (!val)
				return ;
			if (val)
				free(curr->val);
			curr->val = ft_strdup(val);
			return ;
		}
		curr = curr->next;
		pre = pre->next;
	}
	pre->next = make_envp_node(var, val);
}

void	show_export(t_data *data)
{
	t_env	*curr;

	curr = data->envi->next;
	envp_ascending_order(data);
	while (curr != NULL)
	{
		if (!curr->val)
			printf("declare -x %s\n", curr->var);
		else
			printf("declare -x %s=\"%s\"\n", curr->var, curr->val);
		curr = curr->next;
	}
	restore_envp_order(data);
	data->status = 0;
}

void	export_add_key(t_data *data, int i)
{
	char		**args;

	if (ft_search_char(data->curr->cmd[i], '=') == -1)
		add_env(data, data->curr->cmd[i], NULL);
	else
	{
		args = make_key_value(data->curr->cmd[i]);
		if (!args)
			return ;
		add_env(data, args[0], args[1]);
		ft_free_str(args, 0);
	}
	data->status = 0;
}

void	ft_export(t_data *data)
{
	int	i;
	int	res;

	res = 0;
	i = 1;
	if (!data->curr->cmd[i])
		show_export(data);
	while (data->curr->cmd[i])
	{	
		if (ft_search_char(data->curr->cmd[i], '=') == 0 \
		|| is_invalid_key(data->curr->cmd[i], 0))
			res += ft_error(data, data->curr->cmd[i], EXP_ERROR, 1);
		else
			export_add_key(data, i);
		i++;
	}
	if (res > 0)
		data->status = 1;
}
