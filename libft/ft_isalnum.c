/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:12:44 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 01:31:08 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9'));
}
