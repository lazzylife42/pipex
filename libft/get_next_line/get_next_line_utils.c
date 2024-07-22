/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonte-e <smonte-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:42:30 by smonte-e          #+#    #+#             */
/*   Updated: 2023/10/26 11:35:32 by smonte-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(char *buff, size_t end)
{
	char	*str;
	size_t	i;

	str = (char *)ft_calloc(end + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i <= end && buff[i])
	{
		str[i] = buff[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_gnl_strjoin(char *line, char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	tlen;

	tlen = ft_strlen(line) + ft_strlen(buff) + 1;
	str = (char *)ft_calloc(tlen, sizeof(char));
	if (!str)
		free(line);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (buff[j])
	{
		str[i++] = buff[j++];
	}
	free(line);
	str[i] = '\0';
	return (str);
}
