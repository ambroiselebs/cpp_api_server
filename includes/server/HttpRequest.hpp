/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:56:18 by aberenge          #+#    #+#             */
/*   Updated: 2025/07/09 00:05:02 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>
# include <map>

struct HttpRequest {
	std::string							method;
	std::string							path;
	std::map<std::string, std::string>	headers;
	std::string							body;
};

struct HttpResponse {
	int									status_code = 200;
	std::map<std::string, std::string>	headers;
	std::string							body;

	std::string to_string() const;
};

#endif
