/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_serv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:02:47 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 20:41:09 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void loop_serv(data_process* data)
{
	int d_rd, c_cn, server_finish = 0;
	int rc, len;
	int selected, port;
	int max_fd;
	char buffer[1025];
	char *s;
	struct sockaddr_in addr;
	std::string rc1;
	std::vector<int> accepted;
	
    while (server_finish == 0)
    {
        memcpy(&data->work_fd, &data->master_fd, sizeof(data->master_fd));
		memcpy(&data->write_fd, &data->master_fd, sizeof(data->master_fd));
		
		rc1 = std::to_string(data->listen_sd->operator[](1) + 1);
        std::cout << rc1 << std::endl;
        rc = select(data->listen_sd->operator[](data->size - 1) + 1,
					&data->work_fd,
					&data->write_fd,
					NULL,
					&data->time_out);
		
        if (rc == 0)
            break;

        if (rc < 0)
            perror(" select() failed"); break;
		
        d_rd = rc;
		std::cout << "Loop" << std::endl;
		int i = 0;
		while (i < data->size && d_rd)
		{
			if (FD_ISSET(data->listen_sd->operator[](i), &data->work_fd))
            {
                d_rd -= 1;
				
				int tmp = 0;
				int n = 0;
				tmp = accept(data->listen_sd->operator[](n), NULL, NULL);
				while (n < tmp)
				{
					accepted.push_back(tmp);
					if (accepted.operator[](n) < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror(" accepted() failed");
							server_finish = 1;
						}
						break;
					}

					FD_SET(accepted.operator[](n), &data->work_fd);
					c_cn = 0;
					rc = recv(accepted.operator[](n),
							  buffer,
							  sizeof(buffer),
							  MSG_DONTWAIT);
					if (rc < 0)
						perror(" recv() failed"); c_cn = 1; break;

					if (rc == 0)
						c_cn = 1; break;

					len = rc;
					
					if (rc > 0)
					{
						bzero(&addr, sizeof(addr));
						int len = sizeof(addr);
						port = ntohs(addr.sin_port);
						request_process(data->servers, port, buffer);
						rc = send(accepted.operator[](n), s, std::string(s).length(), 0);
					}
					if (rc < 0)
						perror(" send() failed"); c_cn = 1; break;
						
					memset(buffer, 0, sizeof(buffer));
					++n;
				}
				
				if (c_cn)
					FD_CLR(i, &data->work_fd); FD_CLR(i, &data->write_fd);
			}
		}
    }
}