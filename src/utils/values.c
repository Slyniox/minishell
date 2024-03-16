/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:05:24 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 17:18:45 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_g_exit(int value)
{
	g_exit = value;
	return ;
}

bool	valid(char c)
{
	if (c == ' ' || c == '\0')
		return (true);
	return (false);
}
