/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:32:00 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:26:00 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_errcm(t_data *data, char *s1, char *s2, int status)
{
	char	*temp;
	char	*temp2;

	if (s1)
	{
		temp = ft_strjoin3("minishell: ", s1, ": ");
		temp2 = ft_strjoin(temp, s2);
		free(temp);
		perror(temp2);
		free(temp2);
	}
	else
	{
		temp = ft_strjoin("minishell: ", s2);
		perror(temp);
		free(temp);
	}
	data->status = status;
	return (status);
}

void	ft_werr(char *cmd, char *arg, char *comment, t_error error)
{
	ft_putstr_fd("minishell", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		if (error == EXP_ERROR || error == UNSET_ERROR)
		{
			ft_putstr_fd("`", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("'", 2);
		}
		else if (error == NOT_SET_ERROR)
			ft_putstr_fd(arg, 2);
		else
			ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(comment, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_error(t_data *data, char *arg, t_error error, int status)
{
	if (error == FILE_ERROR)
		ft_werr(NULL, arg, "No such file or directory", FILE_ERROR);
	if (error == CMD_ERROR)
		ft_werr(NULL, arg, "command not found", CMD_ERROR);
	else if (error == EXP_ERROR)
		ft_werr("export", arg, "not a valid identifier", EXP_ERROR);
	else if (error == UNSET_ERROR)
		ft_werr("unset", arg, "not a valid identifier", UNSET_ERROR);
	else if (error == NOT_SET_ERROR)
		ft_werr("cd", arg, "not set", NOT_SET_ERROR);
	else if (error == NUM_ARG)
		ft_werr("exit", arg, "Invalid arg", NUM_ARG);
	else if (error == MANY_ARG)
		ft_werr("exit", NULL, "too many arguments", MANY_ARG);
	else if (error == EXEC_ERROR)
		ft_werr(arg, arg, "exec error", EXEC_ERROR);
	else if (error == PERM_ERROR)
		ft_werr(NULL, arg, "Permission denied", PERM_ERROR);
	data->status = status;
	return (status);
}
