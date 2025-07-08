/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:22 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:06:24 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Router.hpp"
#include <iostream>

void	Router::add_route(const std::string& method, const std::string& path, RouteHandler handler)
{
	routes.push_back({ method, path, handler });
}

void	Router::get(const std::string& path, RouteHandler handler)
{
	add_route("GET", path, handler);
}

void	Router::post(const std::string& path, RouteHandler handler)
{
	add_route("POST", path, handler);
}

bool	Router::match_route(const std::string& pattern, const std::string& path)
{
	return (pattern == path);
}

void	Router::handle_request(const HttpRequest& request, HttpResponse& response)
{
	for (const auto& route : routes)
	{
		if (route.method == request.method && match_route(route.path, request.path))
		{
			route.handler(request, response);
			return ;
		}
	}

	response.status_code = 404;
	response.body = "404 Not found";
}

std::string	HttpResponse::to_string() const
{
	std::string	res = "HTTP/1.1 " + std::to_string(status_code) + " OK\r\n";

	for (const auto& header : headers)
		res += header.first + ": " + header.second + "\r\n";
	res += "Content-Length: " + std::to_string(body.length()) + "\r\n";
	res += "\r\n";
	res += body;
	return (res);
}
