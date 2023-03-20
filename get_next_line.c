/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:34:30 by cmassavi          #+#    #+#             */
/*   Updated: 2022/02/15 10:34:36 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*definir_jusquen(char *tout)
{
	int		i;
	char	*jusquen;

	i = 0;
	if (!tout[0])
		return (NULL);
	while (tout[i] && tout[i] != '\n')
		i++;
	i += new_line(&tout[i]);
	jusquen = malloc(sizeof(char) * (i + 1));
	if (!jusquen)
		return (NULL);
	i = 0;
	while (tout[i] && tout[i] != '\n')
	{
		jusquen[i] = tout[i];
		i++;
	}
	if (tout[i] == '\n')
	{
		jusquen[i] = '\n';
		i++;
	}
	jusquen[i] = '\0';
	return (jusquen);
}

char	*definir_depuisn(char *tout, char *jusquen)
{
	int		i;
	int		j;
	char	*depuisn;
	int		lenjusquen;

	lenjusquen = ft_strlen(jusquen);
	i = 0;
	j = 0;
	if (!tout)
		return (NULL);
	if (tout[lenjusquen] == '\0')
		return (ft_free(tout));
	i++;
	depuisn = malloc(sizeof(char) * (ft_strlen(tout) - lenjusquen + 1));
	if (!depuisn)
		return (NULL);
	while (tout[lenjusquen])
		depuisn[j++] = tout[lenjusquen++];
	depuisn[j] = '\0';
	free(tout);
	tout = NULL;
	return (depuisn);
}

char	*get_next_line(int fd)
{
	static char	*tout;
	char		*jusquen;
	char		*buf;
	int			fdread;

	fdread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!new_n(tout) && fdread != 0)
	{
		fdread = read(fd, buf, BUFFER_SIZE);
		if (fdread == -1)
			return (ft_free(buf));
		buf[fdread] = '\0';
		tout = ft_strjoin(tout, buf);
	}
	free(buf);
	jusquen = definir_jusquen(tout);
	tout = definir_depuisn(tout, jusquen);
	return (jusquen);
}
