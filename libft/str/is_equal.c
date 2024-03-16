/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_equal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:35:35 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/21 16:14:43 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	is_equal(char *s1, char *s2, ...)
{
	int		n;
	va_list	args;

	if (!s1 || !s2)
		return (false);
	va_start(args, s2);
	n = va_arg(args, int);
	va_end(args);
	if (n == 0)
		return (ft_strcmp(s1, s2) == 0);
	else
		return (ft_strncmp(s1, s2, n) == 0);
}
