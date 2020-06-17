/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:01:49 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 16:30:48 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <vector>
#include <sys/types.h>
#include <iostream>
#include <fstream>

std::vector<Datatype> serv_init()
{
	std::vector<Datatype> serv;
	std::ifstream file;
	int pos = 0, start = 0;

	file.open("web_serv.config");
	if (!(file.is_open()))
	{
		serv.push_back(Datatype());
		return serv;
	}
	std::string cont(std::istreambuf_iterator<char>(file),
					 (std::istreambuf_iterator<char>()));

	for (; pos < cont.length() -1; ++pos)
	{
		start = cont.find("server", pos);
		pos =  cont.find("}", start);
		serv.push_back(Datatype(cont.substr(start, pos)));
	}
	return serv;
}

data_process &loop_init(std::vector<Datatype> servers)
{
	data_process *db = new data_process;
	db->listen_sd = new std::vector<int>();
	db->address = new std::vector<sockaddr_in>();
	int rc, n = 0;

	db->servers = servers;
	db->size = servers.size();
	FD_ZERO(&db->master_fd);
	
	while (n < db->size)
	{
		std::cout<< "END" <<std::endl;
		db->listen_sd->push_back(socket(AF_INET, SOCK_STREAM, 0));

		if (db->listen_sd->operator[](n) == 0)
			perror("fail: socket"); exit(EXIT_FAILURE);

		rc = setsockopt(db->listen_sd->operator[](n),
					SOL_SOCKET,
					SO_REUSEADDR,
                    (char *)&db->on, sizeof(db->on));
		if (rc < 0)
			perror("fail: set_socket");	close(db->listen_sd->operator[](n)); exit(-1);

		rc = ioctl(db->listen_sd->operator[](n),
					FIONBIO,
					(char *)&db->on);
		if (rc < 0)
			perror("ioctl() failed"); close(db->listen_sd->operator[](n)); exit(-1);

		sockaddr_in *add = new sockaddr_in();

		add->sin_family = AF_INET;
		add->sin_addr.s_addr = INADDR_ANY;
		add->sin_port = htons(servers[n].get_port());
		db->address->push_back(*add);

		rc = bind(db->listen_sd->operator[](n),
					(struct sockaddr *)&db->address->operator[](n),
					sizeof(db->address->operator[](n)));

		if (rc < 0)
			perror("bind() failed"); close(db->listen_sd->operator[](n)); exit(EXIT_FAILURE);

		rc = listen(db->listen_sd->operator[](n), 32);

		if (rc < 0)
			perror("listen() failed"); close(db->listen_sd->operator[](n));	exit(EXIT_FAILURE);
		
		FD_SET(db->listen_sd->operator[](n), &db->master_fd);
		std::cout<< "master_fd" <<std::endl;
		++n;
	}
	
	db->time_out.tv_sec = 30;
	db->time_out.tv_usec = 0;
	db->max_sd = db->listen_sd->operator[](db->size - 1);
	
	return *db;
}