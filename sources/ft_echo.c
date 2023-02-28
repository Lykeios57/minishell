/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:32:45 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:24:58 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_n_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_strcmp(str, "-n") == 0)
		return (1);
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	ft_echo(t_data *data)
{
	char	**cmd;
	int		i;
	int		nl;

	cmd = data->curr->cmd;
	i = 1;
	nl = 1;
	while (is_n_option(cmd[i]))
	{
		nl = 0;
		i++;
	}
	if (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	while (cmd[i])
	{
		printf(" %s", cmd[i]);
		i++;
	}
	if (nl == 1)
		printf("\n");
	data->status = 0;
}
