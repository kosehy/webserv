/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Datatype.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:01:24 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 15:43:19 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <sstream>

#include "Datatype.hpp"

Datatype::Datatype(std::string cont)
{
	size_t offset;
	int i = 0;
	std::string wd;
	std::vector<int> vec;
	bool isNum = true;

	parameters = new std::map<std::string, std::string>();
	while (i < 10)
	{
		if (cont.find(key[i]) == cont.npos)
		{
			std::cout << "Parameter \"" + key[i] + "\" is missing\n";
			throw MissingParamException();
		}
		else
		{
			offset = cont.find(key[i]) + key[i].length() + 1;
			std::string val = cont.substr(offset, cont.find("\n", offset) - offset);
			parameters->operator[](key[i]) = val;
		}
	}
	i = 400;
	while (i < 505)
	{
		err_pgs[i] ="err_pages/" + std::to_string(i) + ".html";
		if (i == 417)
			i = 499;
	}

	std::istringstream s(cont.substr(cont.find("err_page [") + 1, cont.size()));
	
	while (s >> wd)
	{
		if (wd == "]")
			break ;
		int i = 0;
		while (i < wd.length())
		{
			if (!std::isdigit(wd[i]))
			{
				isNum = false;

				break ;
			}
			++i;
		}
		if (isNum)
			vec.push_back(std::stoi(wd));
		else
		{
			i = 0;
			while (i < wd.length())
			{
				err_pgs.operator[](vec[i]) = wd;
			}
		}
	}

	std::istringstream stod(cont.substr(cont.find("method [") + 1, cont.size()));
	while (stod >> wd)
	{
		methods.push_back(wd);
		if (wd == "]")
		break ;
	}
}

Datatype::Datatype()
{
	int i = 0;
	parameters = new std::map<std::string, std::string>();

	while (i < 10)
	{
		parameters->operator[](key[i]) = defaults[i];
		++i;
	}
}

const char* Datatype::MissingParamException::what() const throw()
{
	return "Missing Parameter";
}

int Datatype::get_port(){
	return std::stoi(parameters->operator[]("port"));
}