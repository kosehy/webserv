/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:42 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 15:19:29 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <stdlib.h>
# include <stdio.h>
# include <string>
# include <string.h>
# include <unistd.h>

# include <iostream>
# include <sstream>

# include <sys/ioctl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include <vector>

# include <errno.h>

# include "Datatype.hpp"

extern std::map<int, std::string> errors;


struct sockaddr_in;
struct timeval;

typedef struct s_loop_data
{
	int i, check_socket;
	int on,max_sd, new_sd, size;

	std::vector<int> *listen_sd;
	std::vector<sockaddr_in> *address;
	std::vector<Datatype> servers;
	
	timeval time_out;
	fd_set master_fd, work_fd, read_fd, write_fd;
}				data_process;

std::string get_ext(std::string filename);

std::vector<Datatype> serv_init();

std::map<std::string, std::string> parse_hd(const char *s, int *error);
std::map<std::string, std::string> parse_req(const char *s, int *error);

data_process &loop_init(std::vector<Datatype> servers);


void loop_serv(data_process* data);
const char *request_error(std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_get_head(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_post(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_put(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_delete(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_options(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char *request_trace(std::map<std::string, std::string> req, std::map<std::string, std::string> lines, Datatype data, int error);
const char* request_process(std::vector<Datatype> data, int port,const char *msg);

#endif