/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:48:45 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/29 12:30:23 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			print_dquote(int *f_q_dq, char **env)
{
	if (IS_FLAG(*f_q_dq))
	{
		if (IS_QUOTE(*f_q_dq))
			ft_putstr("\nquote> ");
		else if (IS_DQUOTE(*f_q_dq))
			ft_putstr("\ndquote> ");
		else if (IS_BACKSLASH(*f_q_dq))
		{
			ft_putstr("\n");
			if (ft_getenv("PROMPT2", env))
				ft_putstr(ft_getenv("PROMPT2", env));
			*f_q_dq = (*f_q_dq ^ (1 << 4));
			*f_q_dq = (*f_q_dq ^ (1 << 0));
		}
	}
}

void			search_quote(char *str, int *f_q_dq)
{
	while (*str)
	{
		if (*str == '\\' && *(str - 1) != '\\' && *(str + 1) == '\0'
			&& !IS_FLAG(*f_q_dq))
		{
			*f_q_dq = (*f_q_dq ^ (1 << 4));
			*f_q_dq = (*f_q_dq ^ (1 << 0));
			str++;
		}
		else
			(void)hangling_dquote(f_q_dq, *str);
		str++;
	}
}

char			*read_line_n(char **env)
{
	char	*buf;
	int		pos;
	int		c;

	buf = ft_memalloc(sizeof(char) * (MAX_INPUT + 1));
	pos = 0;
	while (1)
	{
		c = ft_get_char();
		if (c == '\t')
			ft_putchar('\a');
		else if (c == 27)
		{
			ft_get_char();
			c = ft_get_char();
			move_left_right(buf, c, &pos, env);
			move_up_down(&buf, c, &pos, env);
		}
		else if (add_to_buff(&buf, &pos, c))
			return (buf);
	}
}

char			*read_line(char **env)
{
	static int	f_q_dq = 0;
	char		*line;
	char		*str;

	line = NULL;
	while (1)
	{
		str = read_line_n(env);
		search_quote(str, &f_q_dq);
		make_read_str(&line, str);
		if (!f_q_dq || ft_strlen(line) >= MAX_INPUT)
		{
			f_q_dq = 0;
			break ;
		}
		ft_memcpy((line + ft_strlen(line)), "\n", 1);
		print_dquote(&f_q_dq, env);
	}
	ft_putchar('\n');
	if (ft_strlen(line) > 0)
		return (ft_strdup(history(line, 1)));
	else
		return (line);
}
