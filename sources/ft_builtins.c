/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:47:30 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:21:50 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_data *data)
{
	char		**cmd;
	int			i;
	int			res;

	res = 0;
	cmd = data->curr->cmd;
	i = 1;
	while (cmd[i])
	{
		res += remove_env(data, cmd[i]);
		i++;
	}
	if (res > 0)
		data->status = 1;
	else
		data->status = 0;
}

void	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("minishell: pwd");
		data->status = 1;
		return ;
	}
	printf("%s\n", path);
	data->status = 0;
	free(path);
}

void	ft_cd(t_data *data)
{
	char	*path;
	char	*old_path;
	char	**cmd;

	cmd = data->curr->cmd;
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		path = get_cd_path(data, "HOME");
	else if (!ft_strcmp(cmd[1], "-"))
	{
		path = get_cd_path(data, "OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	else
		path = data->curr->cmd[1];
	if (!path)
		return ;
	old_path = getcwd(NULL, 0);
	exec_chdir(data, path, old_path);
}

void	ft_env(t_data *data)
{
	t_env	*curr;

	if (data->curr->cmd[1])
	{
		ft_error (data, data->curr->cmd[1], FILE_ERROR, 127);
		return ;
	}
	curr = data->envi->next;
	while (curr != NULL)
	{
		if (curr->val)
			printf("%s=%s\n", curr->var, curr->val);
		curr = curr->next;
	}
	data->status = 0;
}

void	exec_builtin(t_data *data)
{
	t_cmd_node	*curr;

	curr = data->curr;
	if (ft_strcmp(curr->cmd[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(curr->cmd[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(curr->cmd[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(curr->cmd[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(curr->cmd[0], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(curr->cmd[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(curr->cmd[0], "exit") == 0)
		ft_exit(data);
}
