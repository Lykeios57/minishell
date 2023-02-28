/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:45:44 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:44:08 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_split_env(t_env *envp)
{
	char		**tab;
	int			len;
	int			i;
	t_env		*curr;

	len = 0;
	curr = envp->next;
	while (curr != NULL)
	{
		len++;
		curr = curr->next;
	}
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	curr = envp->next;
	i = 0;
	while (curr && i < len)
	{
		tab[i] = ft_strjoin3(curr->var, "=", curr->val);
		curr = curr->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_find_path(t_env *envp)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = envp->next;
	while (curr != 0)
	{
		if (ft_strcmp(curr->var, "PATH") == 0)
			return (ft_split(curr->val, ':'));
		curr = curr->next;
	}
	return (NULL);
}

char	*ft_get_path(char *first_cmd, char **splited_path)
{
	int		i;
	int		path_count;
	char	*temp_path;
	char	*cmd_path;

	path_count = ft_double_strlen(splited_path);
	temp_path = ft_strjoin("/", first_cmd);
	i = 0;
	while (i < path_count)
	{
		cmd_path = ft_strjoin(splited_path[i], temp_path);
		if (access(cmd_path, X_OK) == 0)
			break ;
		else
			free(cmd_path);
		i++;
	}
	free(temp_path);
	if (i == path_count)
		return (NULL);
	return (cmd_path);
}

char	*make_exec_path(t_data *data)
{
	char	**splited_path;
	char	*path;

	splited_path = ft_find_path(data->envi);
	if (!splited_path)
		exit(ft_error(data, data->curr->cmd[0], FILE_ERROR, 127));
	path = ft_get_path(data->curr->cmd[0], splited_path);
	ft_free_str(splited_path, 0);
	return (path);
}

void	exec_non_builtin(t_data *data)
{
	char	*path;
	char	**envp_arr;

	if (no_cmd(data, 1))
		exit(0);
	if (ft_search_char(data->curr->cmd[0], '/') != -1)
		path = data->curr->cmd[0];
	else
		path = make_exec_path(data);
	if (!path || !ft_strcmp(data->curr->cmd[0], "\0"))
		exit(ft_error(data, data->curr->cmd[0], CMD_ERROR, 127));
	if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
		exit(ft_error(data, path, PERM_ERROR, 126));
	envp_arr = ft_split_env(data->envi);
	if (!envp_arr)
		exit(1);
	execve(path, data->curr->cmd, envp_arr);
	exit(ft_errcm(data, NULL, path, 127));
}
