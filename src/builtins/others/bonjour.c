/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonjour.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:11:36 by soelalou          #+#    #+#             */
/*   Updated: 2024/03/05 15:44:07 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bonjour(t_minishell *minishell, char *login)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(login) + 49 + 1));
	if (!tmp)
		return (get_error(minishell, NULL));
	ft_sprintf(tmp, "cp -f /sgoinfre/photos_students/2023/%s.jpg assets/",
		login);
	if (run_single_cmd(minishell, tmp, NULL, &minishell->original_stdout) == -1)
		return (free(tmp), 1);
	free(tmp);
	tmp = malloc(sizeof(char) * ((ft_strlen(login) * 2) + 119 + 1));
	ft_sprintf(tmp, "convert %s%s.jpg -crop 600x1000+1200+200 %s%s.jpg",
		"./assets/", login,
		"./assets/", login);
	if (run_single_cmd(minishell, tmp, NULL, &minishell->original_stdout) == -1)
		return (free(tmp), 1);
	free(tmp);
	tmp = malloc(sizeof(char) * (ft_strlen(login) + 57 + 1));
	printf("Bonjour %s ! J'espere que tu vas bien \
(et que tu mettras un bonne note)!\n", login);
	ft_sprintf(tmp, "jp2a --colors %s%s.jpg",
		"./assets/", login);
	if (run_single_cmd(minishell, tmp, NULL, &minishell->original_stdout) == -1)
		return (free(tmp), 1);
	return (free(tmp), 0);
}
