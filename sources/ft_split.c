/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:49:03 by lreille           #+#    #+#             */
/*   Updated: 2023/02/11 16:16:07 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_nbchar(char *str, int i, char c)
{
	size_t	nb;

	nb = 0;
	while (str[i] && str[i] != c)
	{
		nb++;
		i++;
	}
	return (nb);
}

int	ft_word_cnt(char *str, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i + 1])
	{
		if (str[i] == c && str[i + 1] != c)
			nb++;
		i++;
	}
	if (str[0] != c)
		nb++;
	return (nb);
}

char	**ft_setsplit(char *s, char **str, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		else
		{
			str[j] = (char *)malloc(sizeof(char) * (ft_nbchar(s, i, c) + 1));
			k = 0;
			while (s[i] && s[i] != c)
			{
				str[j][k] = s[i];
				i++;
				k++;
			}
			str[j][k] = '\0';
			j++;
		}
	}
	return (str);
}

char	**ft_split(char *str, char c)
{
	char	**s;
	int		n;

	if (!str)
		return (NULL);
	n = ft_word_cnt(str, c);
	s = (char **)malloc(sizeof(char *) * (n + 1));
	if (s == NULL)
		return (NULL);
	s[n] = NULL;
	return (ft_setsplit(str, s, c));
}
