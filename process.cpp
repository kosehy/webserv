/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:22 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 20:07:34 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <map>
#include <vector>

const char* request_process(std::vector<Datatype> db,
							int port,const char *msg)
{
	const char *s;
	Datatype *config = nullptr;
	int error;
	std::map<std::string, std::string> request;
	std::map<std::string, std::string> lines;
	request = parse_hd(msg, &error);
	lines = parse_req(msg, &error);

	error = 200;
	std::map<std::string, const char *(*)(std::map<std::string, std::string>,
			 std::map<std::string, std::string>, Datatype, int)> ft;

	ft["HEAD"] = *request_get_head;
	ft["GET"] = request_get_head;
	ft["PUT"] = *request_put;
	ft["POST"] = *request_post;
	ft["DELETE"] = *request_delete;
	ft["OPTIONS"] = *request_options;
	ft["TRACE"] = *request_trace;
	
	int i = 0;
	while (i < db.size())
	{
		if (db.operator[](i).get_port() == port)
		{
			if (config == nullptr)
				config = &db.operator[](i);
			std::string k = db.operator[](i).parameters->operator[]("server_name");
			if ((k.find(request["Host"].substr(0, request["Host"].size() -1)))!=
				 k.npos)
			{
				config = &db.operator[](i);
				break ;
			}
		}
		++i;
	}
	std::string tmp = config->parameters->operator[]("body_size");
	if (tmp != "" && std::stoi(tmp) < 0)
		error = 413;

	if (request["Content-Lentgh"] == "" )
		error = 401;

	if (error > 200)
	{
		s = request_error(lines, *config , error);
		return s;
	}

	std::list<std::string>::iterator it = config->methods.begin();
	for(; it != config->methods.end(); it++)
	{
		if (lines["Type"] == *it)
			break ;
	}

	if (it == config->methods.end())
		error = 501;

	s = (*ft[lines["Types"]])(request,lines, *config, error);

	return s;
}