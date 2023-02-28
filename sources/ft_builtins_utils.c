/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:27:06 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:22:33 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_env(t_data *data, char *var)
{
	t_env	*pre;
	t_env	*old;

	if (is_invalid_key(var, 1))
		return (ft_error(data, var, UNSET_ERROR, 1));
	pre = data->envi->next;
	while (pre->next != NULL)
	{
		if (!ft_strcmp(pre->next->var, var))
		{
			old = pre->next;
			if (old == NULL)
				return (0);
			pre->next = old->next;
			free(old->var);
			free(old->val);
			free(old);
			return (0);
		}
		else
			pre = pre->next;
	}
	return (0);
}

void	exec_chdir(t_data *data, char *path, char *old_path)
{
	char	*pwd;

	if (chdir(path) == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("mini: pwd error");
			data->status = 1;
			return ;
		}
		add_env(data, "PWD", pwd);
		add_env(data, "OLDPWD", old_path);
		free(pwd);
		free(old_path);
		data->status = 0;
	}
	else
	{
		ft_errcm(data, "cd", path, 1);
		free(old_path);
	}
}

char	*get_cd_path(t_data *data, char *var)
{
	char	*path;

	path = get_env_path(data->envi, var);
	if (!path)
	{
		ft_error(data, var, NOT_SET_ERROR, 1);
		return (0);
	}
	return (path);
}
