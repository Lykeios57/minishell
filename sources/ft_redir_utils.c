/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:58:11 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:35:22 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_infile_node(t_infile_node *lst, void *red_node)
{
	t_infile_node	*now;

	now = lst;
	while (now->next)
		now = now->next;
	now->next = red_node;
}

void	append_heredoc_node(t_infile_node *lst, void *red_node)
{
	t_infile_node	*now;

	now = lst;
	while (now->hnext)
		now = now->hnext;
	now->hnext = red_node;
}

void	append_outfile_node(t_outfile_node *lst, void *red_node)
{
	t_outfile_node	*now;

	now = (t_outfile_node *)lst;
	while (now->next)
		now = now->next;
	now->next = red_node;
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;

	if ((count != 0 && SIZE_MAX / count < size)
		|| (size != 0 && SIZE_MAX / size < count))
		return (NULL);
	buffer = malloc(size * count);
	if (!buffer)
		return (0);
	ft_bzero(buffer, count * size);
	return ((void *)buffer);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;
	size_t			index;

	buffer = (unsigned char *)s;
	index = 0;
	if (n == 0)
		return ;
	while (index < n)
	{
		buffer[index] = 0;
		index++;
	}
}
