/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:17:36 by calamber          #+#    #+#             */
/*   Updated: 2019/03/24 10:19:23 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraydel(char **array)
{
	char	**temp;

	temp = array;
	while (*array)
	{
		ft_strdel(&(*array));
		array++;
	}
	if (temp)
		free(temp);
}
