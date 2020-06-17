/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <sko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:00:58 by sko               #+#    #+#             */
/*   Updated: 2020/06/17 15:34:52 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0;
    long valread;
    struct sockaddr_in server_addr;
    char message[] = {"i'm client!"};    
    char buffer[1024] = {0};
	
	fork();

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n create error message \n");
        return -1;
    }
    
    memset(&server_addr, '0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");

        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\n Fail to Connect \n");
        
        return -1;
    }

    send(sock , message , strlen(message) , 0 );

    printf("Message sent\n");

    valread = read( sock , buffer, 1024);

    printf("%s\n",buffer );

    return 0;
}