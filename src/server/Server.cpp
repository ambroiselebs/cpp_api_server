/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:43:02 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:13:03 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include <sstream>

Server::Server(int port) : port(port), server_fd(-1)
{}

Server::~Server(void)
{
	if (server_fd != -1)
		close(server_fd);
}

void	Server::start(void)
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		std::cerr << "Error: socket creation" << std::endl;
		return ;
	}

	struct	sockaddr_in	adress;
	adress.sin_family = AF_INET;
	adress.sin_addr.s_addr = INADDR_ANY;
	adress.sin_port = htons(this->port);

	if (bind(server_fd, (struct sockaddr*)&adress, sizeof(adress)) < 0)
	{
		std::cerr << "Error: bind" << std::endl;
		return ;
	}
	if (listen(server_fd, 10) < 0)
	{
		std::cerr << "Error: listen" << std::endl;
		return ;
	}

	std::cout << "Server running on port : " << this->port << std::endl;

	while (true)
	{
		int	client_id = accept(server_fd, nullptr, nullptr);
		if (client_id >= 0)
		{
			handle_request(client_id);
			close(client_id);
		}
	}
}

void	Server::handle_request(int client_fd)
{
	char	buffer[4096] = {0};

	read(client_fd, buffer, 4096);
	HttpRequest request = parse_request(std::string(buffer));
	HttpResponse response;
	router.handle_request(request, response);
	std::string response_str = response.to_string();
	write(client_fd, response_str.c_str(), response_str.length());
}

HttpRequest	Server::parse_request(const std::string& raw_request)
{
	HttpRequest			req;
	std::istringstream	stream(raw_request);
	std::string			line;

	if (std::getline(stream, line))
	{
		std::istringstream	first_line(line);
		first_line >> req.method >> req.path;
	}
	while (std::getline(stream, line) && line != "\r")
	{
		size_t	colon = line.find(':');
		if (colon != std::string::npos)
		{
			std::string	key = line.substr(0, colon);
			std::string	value = line.substr(colon + 2);
			req.headers[key] = value;
		}
	}
	return (req);
}
