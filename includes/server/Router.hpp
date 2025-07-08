/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:57:05 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:00:09 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTER_HPP
# define ROUTER_HPP

# include <functional>
# include <map>
# include <vector>
# include "server/HttpRequest.hpp"

using RouteHandler = std::function<void(const HttpRequest&, HttpResponse&)>;

struct Route {
	std::string		method;
	std::string		path;
	RouteHandler	handler;
};

class Router
{
	private:
		std::vector<Route>	routes;

		bool	match_route(const std::string& pattern, const std::string& path);

	public:
		void	add_route(const std::string& method, const std::string& path, RouteHandler handler);
		void	get(const std::string& path, RouteHandler handler);
		void	post(const std::string& path, RouteHandler handler);
		void	handle_request(const HttpRequest& request, HttpResponse& response);
};

#endif
