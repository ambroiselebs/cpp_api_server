/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:43:09 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:11:39 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <cstring>
# include "server/HttpRequest.hpp"
# include "server/Router.hpp"

class Server
{
	private:
		int		port;
		int		server_fd;
		Router	router;

		HttpRequest	parse_request(const std::string& raw_request);

	public:
		Server(int port);
		~Server();

		void	start(void);
		void	handle_request(int client_fd);
		Router&	get_router() { return router; }
};


#endif
