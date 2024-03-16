/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:16:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/15 05:32:14 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_tabjoin(char **tab, bool without_space)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	len = 0;
	while (tab[++i] != NULL)
		len += ft_strlen(tab[i]) - 1;
	str = malloc(sizeof(char) * (len + i + 1));
	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (tab[++i])
	{
		j = 0;
		while (tab[i][j] != '\0')
			str[len++] = tab[i][j++];
		if (!without_space)
			str[len++] = ' ';
	}
	str[len] = '\0';
	return (str);
}
