# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sko <sko@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 01:01:55 by sko               #+#    #+#              #
#    Updated: 2020/06/17 20:43:17 by sko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serv


all: $(NAME)

$(NAME) :
	clang++ -std=c++11 serv.cpp init.cpp Datatype.cpp process.cpp requests.cpp loop_serv.cpp parse.cpp utils.cpp -o serv

re :
	rm -f serv
	clang++ -std=c++11 serv.cpp init.cpp Datatype.cpp process.cpp requests.cpp loop_serv.cpp parse.cpp utils.cpp -o serv
