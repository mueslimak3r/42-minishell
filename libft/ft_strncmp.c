/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:45:13 by calamber          #+#    #+#             */
/*   Updated: 2018/05/07 16:29:29 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i] && s1[i] && n != 1)
	{
		n--;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
