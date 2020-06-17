/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:17 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 19:57:00 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include <stdlib.h>
#include <map>

#include "server.hpp"

const char* white_space = " \t\n\r\f\v";

std::map<std::string, std::string> parse_req(const char *s, int *error){
    std::map<std::string, std::string> request;
    const char *head = s;
    const char *tail = s;
    size_t len = strlen(s);
    const char *msg_end = s + len;

    if (len > 8000)
        *error = 400;

    while (tail != msg_end && *tail == ' ') ++tail;
    head = tail;
    while (tail != msg_end && *tail != '\r') ++tail;
    request["Version"] = std::string(head, tail);

    while (tail != msg_end && *tail == ' ') ++tail;
    head = tail;
    while (tail != msg_end && *tail != ' ') ++tail;
    request["Path"] = std::string(head, tail);

    if (tail - head > 2000)
      *error = 414;
    
    while (tail != msg_end && *tail != ' ') ++tail;
    request["Type"] = std::string(head, tail);

    if (tail - head > 8)
        *error = 501;

    return (request);
}

inline std::string& rtrim(std::string& s,
                          const char* t = white_space)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string& ltrim(std::string& s,
                          const char* t = white_space)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string& trim(std::string& s,
                         const char* t = white_space)
{
    return ltrim(rtrim(s, t), t);
}

std::map<std::string, std::string> parse_hd(const char *s, int *error){
    std::istringstream resp(s);
    std::string header;
    std::string::size_type idx;
    std::map<std::string, std::string> hd;
    
    if (hd.find("Host") == hd.end() )
       *error = 400;
    hd["request"] = std::string(s);

    while (std::getline(resp, header) && header != "\r") {
        idx = header.find(':', 0);
        if(idx != std::string::npos) {
        std::string key = header.substr(0, idx);
        std::string value = header.substr(idx + 1);
        if (key.find(' ') != std::string::npos)
            *error = 400;
            hd.insert(std::make_pair(
                trim(key, white_space),
                trim(value, white_space)
            ));
        }
    }
    return (hd);
}