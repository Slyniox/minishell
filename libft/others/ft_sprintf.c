/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:08:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/02/17 19:53:36 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	cases(va_list args, char *str, char c, int *j)
{
	char	*s;
	char	*d_str;

	if (!str || !c)
		return ;
	if (c == 's')
	{
		s = va_arg(args, char *);
		while (*s)
			str[(*j)++] = *s++;
	}
	else if (c == 'd')
	{
		d_str = ft_itoa(va_arg(args, int));
		if (!d_str)
			return ;
		while (*d_str)
		{
			str[*j] = *d_str;
			(*j)++;
			d_str++;
		}
		free(d_str);
	}
}

int	ft_sprintf(char *str, const char *format, ...)
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			cases(args, str, format[i], &j);
		}
		else
			str[j++] = format[i];
		i++;
	}
	str[j] = '\0';
	va_end(args);
	return (j);
}
