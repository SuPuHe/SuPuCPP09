/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:31:10 by omizin            #+#    #+#             */
/*   Updated: 2026/01/07 15:00:41 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2){
		std::cerr << RED << "Usage: ./btc input.txt" << RESET << std::endl;
		return 1;
	}

	BitcoinExchange a;

	try{
		a.loadDB();
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}

	std::string filename = argv[1];

	try{
		a.processingInputFile(filename);
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}


	return 0;
}
