/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:36 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 20:30:01 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <time.h>
#include <experimental/filesystem>

#include "server.hpp"

const char *request_put(std::map<std::string, std::string> request,
						std::map<std::string, std::string> lines,
						Datatype db,
						int error)
{
	std::string db_u, res, res1, res2, res3;
	std::string file, body, path;
	std::ifstream fd;
	int size;

	if (error == 200)
		error = 201;
	db_u = db.parameters->operator[]("uploads");
	if (db_u == "yes")
	{
		file = db_u + lines["Path"];
		fd.open(file);
		if (fd.is_open())
			error = 409;
		else
		{
			path = "echo " + request["Body"] + ">" + db_u + lines["Path"];
			system(path.c_str());
		}
	}
	else
		error = 501;
	std::cout << "file path :" + file << std::endl;
	res1 = "<html>\n<body>\n<h1>The file could not be created.</h1>\n</body>\n</html>";
	res2 = "<html>\n<body>\n<h1>The file was created.</h1>\n</body>\n</html>";
	if (error > 201)
		body =	res1;
	else
		body =	res2;
	res3 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res = res3 + "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: "
	+ std::to_string(body.size()) + "\nContent-Type: text/html" +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + body;
	
	return res.c_str();
}

const char *request_error(std::map<std::string, std::string> lines,
						  Datatype db, int error)
{
	std::string db_p, res, res1, res2;
	std::ifstream fd;
	std::string file, extension, path;

	db_p = db.parameters->operator[]("search_dir");
	if (db_p != "")
		path = db_p;
	file = path + lines["Path"];
	fd.open(db.err_pgs.at(error));
	while(std::getline(fd, file));

	res1 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res2 = "Content-Length: " + std::to_string(file.length()) + "\nContent-Type: " + extension;
	res = res1 + "Last-Modified" + "\nContent-Language: en\n" + res2 + "\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + file;

	return res.c_str();
}

const char *request_post(std::map<std::string, std::string> request,
						 std::map<std::string, std::string> lines,
					     Datatype db,
						 int error)
{
	std::string db_p, res, res1, res2, res3;
	std::string file, extension, path;
	std::ifstream fd;
	int size;

	db_p = db.parameters->operator[]("search_dir");
	if (db_p != "")
		path = db_p;

	file = path + lines["Path"];
	extension = get_ext(lines["Path"]);

	if (extension != db.parameters->operator[]("CGI_extension"))
		error = 501;
	else
	{
		if (fork() == 0)
		{
			system(file.c_str());
			exit(0);
		}
	}
	res1 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res = res1 + "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + "77" + "\nContent-Type: text/html" + "\n" + "Content-Location: "+ path + "\nServer: ft_webserv";
	res2 = "<html>\n<body>\n<h1>Request was Processed Successfully</h1>\n</body>\n</html>";
	res3 = "<html>\n<body>\n<h1>Request not Processed Successfully</h1>\n</body>\n</html>";
	if (error == 200)
		res = res + res2;
	else
		res = res + res3;
		
	return res.c_str();
}

const char *request_get_head(std::map<std::string, std::string> request,
							 std::map<std::string, std::string> lines,
							 Datatype db,
							 int error)
{
	std::string db_p, res, res1, res2;
	std::string file, extension, path;
	std::ifstream fd;
	int size;

	db_p = db.parameters->operator[]("search_dir");
	if (db_p != "")
		path = db_p;

	file = path + lines["Path"];
	fd.open(file);
	
	if (!fd.is_open())
		error = 404;
	while (std::getline(fd, file));
	size = file.size();
	if (std::stoi(db.parameters->operator[]("body_size")) < size)
		error = 413;
	res1 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res2 = "Content-Length: " + std::to_string(size) + "\nContent-Type: " + extension;
	res = res1 + "Last-Modified" + "\nContent-Language: en\n" + res2 + "\n" + "Content-Location: "+ path + "\nServer: ft_webserv";

	if (lines["Type"] == "GET" && error == 200)
		res = res + file;

	return res.c_str();
}

const char *request_delete(std::map<std::string, std::string> request,
						   std::map<std::string, std::string> lines,
						   Datatype db,
						   int error)
{
	std::string db_p, res, res1, res2, res3;
	std::string file, extension, path;
	std::ifstream fd;
	int size;

	db_p = db.parameters->operator[]("search_dir");
	if (db_p != "")
		path = db_p;

	file = path + lines["Path"];
	fd.open(file);
	std::cout << "file path :" + file << std::endl;
	if (!fd.is_open())
		error = 404;

	fd.close();
	file = "rm -f " + file;
	system(file.c_str());
	size = file.size();
	
	res1 = "<html>\n<body>\n<h1>URL not found.</h1>\n</body>\n</html>";
	res2 = "<html>\n<body>\n<h1>URL deleted.</h1>\n</body>\n</html>";
	if (error > 200)
		res = res1;
	else
		res = res2;
	res3 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res = res3 + "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: "
	+ std::to_string(res.length()) + "\nContent-Type: text/html" +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + res;

	return res.c_str();
}

const char *request_trace(std::map<std::string, std::string> request,
						  std::map<std::string, std::string> lines,
						  Datatype db,
						  int error)
{
	std::string res, res1;
	res1 = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res = res1 + "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: "
	+ std::to_string(request["request"].length()) + "\nContent-Type: message/http" +
	"\n" + "\nServer: ft_webserv";
	
	if (error == 200)
		res = res + request["request"];

	return res.c_str();
}

const char *request_options(std::map<std::string, std::string> request,
						    std::map<std::string, std::string> lines,
						    Datatype db,
						    int error)
{
	std::string res, res2, allowed;

	std::list<std::string>::iterator it = db.methods.begin();
	for (; it != db.methods.end(); it++)
	{
		allowed = allowed + *it + ",";
	}
	res2 =  "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: ";
	res = res2 + "Last-Modified" + "Allowed: " + allowed + "\nContent-Language: en\n" + "Content-Length: "
	+ std::to_string(request["request"].length()) + "\nContent-Type: httpd/unix-directory" + "\n" + "\nServer: ft_webserv";

	return res.c_str();
}