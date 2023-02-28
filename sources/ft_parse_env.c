/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:15:46 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:34:11 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*parse_envp(char **ev)
{
	t_env	*envp;
	t_env	*now;
	int		index;

	envp = ft_malloc(sizeof(t_env));
	now = envp;
	index = 0;
	while (ev[index])
	{
		now->next = new_envp_node(ev[index]);
		now = now->next;
		index++;
	}
	return (envp);
}

t_env	*new_envp_node(char *envp)
{
	t_env	*node;
	int		len;
	int		equal;

	len = ft_strlen(envp);
	node = malloc(sizeof(t_env));
	equal = (int)(ft_strchr(envp, '=') - envp);
	if (!node)
		exit (1);
	node->var = ft_substr(envp, 0, equal);
	node->val = ft_substr(envp, equal + 1, len - equal - 1);
	if (ft_strncmp(node->var, "OLDPWD", 6) == 0)
	{
		free(node->val);
		node->val = NULL;
	}
	node->next = NULL;
	return (node);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*substr;
	int		index;
	int		size;
	int		srclen;

	srclen = ft_strlen(s);
	if (srclen <= start)
		size = 0;
	else if (srclen < len + start)
		size = srclen - start;
	else
		size = len;
	substr = (char *)malloc(sizeof(char) * (size + 1));
	if (!substr)
		exit (1);
	index = 0;
	while (index < size && s[start])
		substr[index++] = s[start++];
	substr[index] = 0;
	return (substr);
}

char	*get_value_by_key(t_env *envi, char *var, int len)
{
	t_env	*now;

	if (len == 0)
		return (NULL);
	now = envi->next;
	while (now)
	{
		if (ft_strncmp(now->var, var, len) == 0 && !now->var[len])
			return (now->val);
		now = now->next;
	}
	return (NULL);
}
