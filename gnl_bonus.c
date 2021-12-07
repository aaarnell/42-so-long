/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:11:12 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/05 16:09:01 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_fr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

char	*ft_nstr(size_t cnt)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * cnt + 1);
	if (!ptr)
		return (NULL);
	ptr[cnt] = '\0';
	while (cnt--)
		ptr[cnt] = '\0';
	return (ptr);
}

void	ft_lnrec(char **st, char **ln, int fd)
{
	char	*tmp;
	char	*nl;

	nl = ft_strchr(st[fd], '\n');
	if (!nl)
	{
		*ln = ft_strdup(st[fd]);
		ft_fr(&st[fd]);
	}
	else
	{
		*nl = '\0';
		*ln = ft_strdup(st[fd]);
		tmp = ft_strdup(++nl);
		ft_fr(&st[fd]);
		st[fd] = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	char		buf[GNL_BUF_SIZE + 1];
	ssize_t		cnt;
	static char	*st[FOPEN_MAX];
	char		*tmp;

	cnt = read(fd, buf, GNL_BUF_SIZE);
	if (!line || fd < 0 || cnt < 0)
		return (-1);
	if (!st[fd])
		st[fd] = ft_nstr(1);
	while (line && fd >= 0 && cnt > 0)
	{
		buf[cnt] = '\0';
		tmp = ft_strjoin(st[fd], buf);
		ft_fr(&st[fd]);
		st[fd] = tmp;
		if ((ft_strchr(st[fd], '\n')))
			break ;
		cnt = read(fd, buf, GNL_BUF_SIZE);
	}
	ft_lnrec(st, line, fd);
	if (!cnt && !st[fd])
		return (ft_fr(&st[fd]));
	return (1);
}
