/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:51:04 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:32:29 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_one_node(t_cmd_node *node)
{
	int	i;

	i = 0;
	if (node == 0)
		return ;
	if (node->cmd)
	{
		while (node->cmd[i])
		{
			ft_free(node->cmd[i]);
			i++;
		}
		ft_free(node->cmd);
	}
	ft_free(node);
}

void	free_double_char(char **cmd)
{
	int		i;
	char	*str;

	i = 0;
	if (!cmd)
		return ;
	str = cmd[i];
	while (cmd[i])
	{
		printf("free %p %s\n", cmd[i], cmd[i]);
		ft_free(cmd[i]);
		i++;
	}
	ft_free(cmd);
}
