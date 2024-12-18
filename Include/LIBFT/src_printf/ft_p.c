/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:52:01 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/06/27 14:58:35 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_p(unsigned long p)
{
	int	c;

	c = 0;
	if (!p)
	{
		ft_putstr_pf_pf("0x0");
		return (3);
	}
	else
	{
		ft_putstr_pf_pf("0x");
		c = 2 + ft_putnbr_pf_x(p);
	}
	return (c);
}
