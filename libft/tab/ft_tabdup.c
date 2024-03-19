/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balthazar <balthazar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:17:33 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/19 12:41:13 by balthazar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**ret;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			return (NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
