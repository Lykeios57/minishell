/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:17:55 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:24:33 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_syntax_err(const char *str)
{
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
	return (1);
}

int	check_pipe_err(t_parsing_node *parse, t_parsing_node *now)
{
	int	ret;

	ret = 0;
	if (!now->next)
	{
		if (now != parse)
			ret = print_syntax_err("newline");
	}
	else if (now->next->type == PIPE)
		ret = print_syntax_err(now->next->str);
	return (ret);
}

int	check_red_err(t_parsing_node *now)
{
	int	ret;

	ret = 0;
	if (!now->next)
		ret = print_syntax_err("newline");
	else if (now->next->type != WORD)
		ret = print_syntax_err(now->next->str);
	return (ret);
}

int	check_quote_err(char *line)
{
	int	quote;
	int	ret;

	ret = 0;
	quote = is_quote(line, ft_strlen(line) - 1);
	if (quote == 1)
		ret = print_syntax_err("\"");
	if (quote == 2)
		ret = print_syntax_err("\'");
	return (ret);
}
