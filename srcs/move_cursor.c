/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:00:29 by atverdok          #+#    #+#             */
/*   Updated: 2017/06/21 15:00:33 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		make_count_n(char *buf, int pos)
{
	int i;
	int count_n;

	i = 0;
	count_n = 0;
	while (buf[i] != '\0' && i != pos)
	{
		if (buf[i] == '\n')
			count_n++;
		i++;
	}
	return (count_n);
}

void	clean_screan(char *buf, int pos, char **env)
{
	int count_n;
	int len;

	count_n = make_count_n(buf, pos);
	len = (int)ft_strlen(buf);
	if (count_n && len)
	{
		ft_putstr("\e[");
		ft_putnbr(count_n);
		ft_putstr("F");
		if (ft_getenv("PROMPT", env))
		{
			ft_putstr("\e[");
			ft_putnbr((int)ft_strlen(ft_getenv("PROMPT", env)));
			ft_putstr("C");
		}
	}
	else if (len && pos)
	{
		ft_putstr("\e[");
		ft_putnbr(pos % (len + 1));
		ft_putstr("D");
		ft_putstr("\e[K");
	}
	ft_putstr("\e[J");
}

void	mov_left_up(int pos, char *buf, char **env)
{
	size_t	len;
	int		start_pos;
	char	*ptr;

	start_pos = pos - 1;
	while (start_pos && buf[start_pos] != '\n')
		start_pos--;
	if (buf[start_pos] == '\n')
		start_pos++;
	ptr = ft_strsub(buf, (unsigned int)start_pos, (size_t)(pos - start_pos));
	if (!start_pos && ft_getenv("PROMPT", env))
		len = ft_strlen(ptr) + ft_strlen(ft_getenv("PROMPT", env));
	else
		len = ft_strlen(ptr);
	ft_strdel(&ptr);
	ft_putstr("\e[1A");
	ft_putstr("\e[");
	ft_putnbr((int)len);
	ft_putstr("C");
}

void	move_left_right(char *buf, int c, int *pos, char **env)
{
	size_t	len;

	len = ft_strlen(buf);
	if (c == KEY_LEFT && (*pos > 0))
	{
		(*pos)--;
		ft_putstr("\e[1D");
		if (buf[*pos] == '\n')
			mov_left_up(*pos, buf, env);
	}
	else if (c == KEY_RIGHT && (*pos < (int)len))
	{
		if (buf[*pos] == '\n')
			ft_putstr("\e[1E");
		else
			ft_putstr("\e[1C");
		(*pos)++;
	}
}

void	move_up_down(char **buf, int c, int *pos, char **env)
{
	if (c == KEY_UP)
	{
		clean_screan(*buf, *pos, env);
		ft_memcpy(*buf, history(*buf, c), (MAX_INPUT - 1));
		ft_putstr(*buf);
		*pos = (int)ft_strlen(*buf);
	}
	else if (c == KEY_DOWN)
	{
		clean_screan(*buf, *pos, env);
		ft_memcpy(*buf, history(*buf, c), (MAX_INPUT - 1));
		ft_putstr(*buf);
		*pos = (int)ft_strlen(*buf);
	}
}
