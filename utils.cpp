/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:55 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 01:02:55 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string get_ext(std::string fn)
{
	int i;
	std::string result;

	i = 0;
	while(i < fn.length())
	{
		if (fn[i] == '.')
		{
			break;
		}
		++i;
	}
	result = fn.substr(i, fn.length());
	return result;
}
