/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:31:10 by omizin            #+#    #+#             */
/*   Updated: 2026/01/05 14:00:29 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2){
		std::cerr << RED << "Usage: ./btc input.txt" << RESET << std::endl;
		return 1;
	}
	std::ifstream file(argv[1]);
	if (!file.is_open()){
		std::cerr << RED << "Error: could not open file." << RESET << std::endl;
		return 1;
	}
	if (file.peek() == std::ifstream::traits_type::eof()){
		std::cerr << RED << "Error: empty file." << RESET << std::endl;
	}
	return 0;
}
