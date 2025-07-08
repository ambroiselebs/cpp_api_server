/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:42:07 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:14:07 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include <iostream>

int main() {
	Server server(8080);

	// Définir les routes
	server.get_router().get("/", [](const HttpRequest&, HttpResponse& res) {
		res.body = "Hello Home!";
	});

	server.get_router().get("/api/users", [](const HttpRequest&, HttpResponse& res) {
		res.headers["Content-Type"] = "application/json";
		res.body = "{\"users\": [\"alice\", \"bob\"]}";
	});

	server.get_router().post("/api/users", [](const HttpRequest& req, HttpResponse& res) {
		std::cout << "Body reçu: " << req.body << std::endl;
		res.body = "User created!";
	});

	server.start();
	return 0;
}
