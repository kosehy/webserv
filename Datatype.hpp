/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Datatype.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:01:35 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 15:03:09 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <string>
# include <list>
# include <map>

# include <fstream>
# include <iostream>

class Datatype
{
private:	
	std::string key[10] = {
		"port", "server_name", "err_page", 
		"body_size", "search_dir", "dir_listing", 
		"default_file", "CGI_extension", 
		"uploads", "uploads_dir"
	};
	std::string defaults[10] = {
		"port", "server_name", "err_page", 
		"body_size", "search_dir", "dir_listing", 
		"default_file", "CGI_extension", 
		"uploads", "uploads_dir"
	};

public:
	
	std::list<std::string> methods;	
	std::map<int, std::string> err_pgs;
	std::map<std::string, std::string>* parameters;
	Datatype();
	Datatype(std::string start);
	~Datatype(){}
	int get_port();
	
	class MissingParamException : public std::exception {virtual const char* what() const throw();};
};

#endif