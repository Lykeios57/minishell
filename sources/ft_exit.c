/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:51:41 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 16:59:02 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit_str(char *str, int i)
{
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit_atoi(char *str, int *is_not_num, int i)
{
	long long	num;
	int			sign;

	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!str[i] || !ft_isdigit_str(str, i))
	{
		*is_not_num = 1;
		return (-1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

int	ft_exit_reg(int idx)
{
	if (idx > 0)
	{
		while (idx > 0)
			idx = idx - 256;
	}
	else
	{
		while (idx < 0)
			idx = idx + 256;
	}
	return (idx);
}

int	ft_exit_with_arg(t_data *data, int exit_arg, int is_not_num)
{
	int	exit_code;

	exit_code = exit_arg;
	if (is_not_num == 1)
	{
		ft_error(data, data->curr->cmd[1], NUM_ARG, 255);
		exit_code = 255;
	}
	else if (data->curr->cmd[2])
	{
		ft_error(data, NULL, MANY_ARG, 1);
		return (-1);
	}
	else if (exit_arg > 255 || exit_arg < 0)
		exit_code = ft_exit_reg(exit_arg);
	return (exit_code);
}

void	ft_exit(t_data *data)
{
	int	arg;
	int	code;
	int	num;

	num = 0;
	if (data->cmd_num == 1)
		printf("exit\n");
	if (data->curr->cmd[1])
	{
		arg = ft_exit_atoi(data->curr->cmd[1], &num, 0);
		code = ft_exit_with_arg(data, arg, num);
		if (code == -1)
		{
			data->status = 1;
			return ;
		}
		data->status = code;
		exit(code);
	}
	if (data->cmd_num == 1)
		exit(data->status);
	data->status = 0;
	exit(0);
}
