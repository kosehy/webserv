/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:01:44 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 16:17:45 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

#define PORT 80

std::map<int, std::string> create_error()
{
  std::map<int, std::string> error;
  error[200] = "OK";
  error[201] = "Created";
  error[204] = "No Content";
  error[400] = "Bad Request";
  error[401] = "Unauthorized";
  error[402] = "Payment Required";
  error[403] = "Forbidden";
  error[404] = "Not Found";
  error[405] = "Method Not Allowed";
  error[406] = "Not Acceptable";
  error[407] = "Proxy Authentication Required";
  error[408] = "Request Timeout";
  error[409] = "Conflict";
  error[410] = "Gone";
  error[411] = "Length Required";
  error[412] = "Precondition Failed";
  error[413] = "Payload Too Large";
  error[414] = "URI Too Long";
  error[415] = "Unsupported Media Type";
  error[416] = "Range Not Satisfiable";
  error[417] = "Expectation Failed";
  error[418] = "I'm a teapot";
  error[421] = "Misdirected Request";
  error[422] = "Unprocessable Entity (WebDAV)";
  error[423] = "Locked (WebDAV)";
  error[424] = "Failed Dependency (WebDAV)";
  error[425] = "Too Early";
  error[426] = "Upgrade Required";
  error[428] = "Precondition Required";
  error[429] = "Too Many Requests";
  error[431] = "Request Header Fields Too Large";
  error[451] = "Unavailable For Legal Reasons";
  error[501] = "Not Implemented";

  return error;
}

std::map<int, std::string> errors = create_error();

int main(int argc, char const *argv[])
{
	std::vector<Datatype> serv;
    data_process *data;

	serv = serv_init();
	data = &loop_init(serv);
	loop_serv(data);
}
