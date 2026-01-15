/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:31:10 by omizin            #+#    #+#             */
/*   Updated: 2026/01/15 13:28:00 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2){
		std::cerr << RED << "Usage: ./btc input.txt" << RESET << std::endl;
		return 1;
	}

	std::map<std::string, double> db;
	std::cout << GREEN << "\nCsv file output\n" << RESET << std::endl;
	try{
		loadDB(db);
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}

	std::string filename = argv[1];
	std::cout << GREEN << "\nInput file output\n" << RESET << std::endl;
	try{
		processingInputFile(filename, db);
	} catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}


	return 0;
}
