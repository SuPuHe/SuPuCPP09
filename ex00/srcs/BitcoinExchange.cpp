/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:30:38 by omizin            #+#    #+#             */
/*   Updated: 2026/01/06 14:51:23 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _db(copy._db){};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
	if (this != &copy)
		_db = copy._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

static bool	isValidDate(const std::string &date){
	if (date.length() != 10)
		return false;

	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; i++){
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009)
		return false;
	if (month < 1 || month > 12)
		return false;
	std::cout << year << " " << month << " " <<  day << std::endl;
	return true;
}

void	BitcoinExchange::loadDB(){
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw::std::runtime_error(RED"Error: could not open database file." RESET);

	std::string line;
	std::getline(file, line);

	std::cout << line << std::endl;

	int	line_count = 1;
	while(std::getline(file, line)){
		line_count++;
		std::stringstream ss(line);
		std::string date;
		std::string rateStr;
		if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr) || date.empty() || rateStr.empty()){
			std::cout << RED << "Error: Corrupted data on line " << line_count << RESET << std::endl;
			continue;
		}
		if (!isValidDate(date)){
			std::cout << RED << "Error: Incorrect data on line " << line_count << RESET << std::endl;
			continue;
		}
		//std::cout << line << std::endl;
	}
	file.close();
}
