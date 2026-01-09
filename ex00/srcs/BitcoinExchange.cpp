/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:30:38 by omizin            #+#    #+#             */
/*   Updated: 2026/01/07 16:12:28 by omizin           ###   ########.fr       */
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

static bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static bool	isValidDate(const std::string &date, bool flag){
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

	if (year < 2009 && flag)
		return false;
	if (month < 1 || month > 12)
		return false;

	int	allowed_day_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && isLeapYear(year))
		allowed_day_in_month[1] = 29;

	if (day < 1 || day > allowed_day_in_month[month - 1])
		return false;

	return true;
}

void	skipSpaces(std::string &line){
	line.erase(0, line.find_first_not_of(" \t"));
	line.erase(line.find_last_not_of(" \t") + 1);
}

bool isValidAmount(double amount){
	if (amount < 0 || amount > 1000)
		return false;
	return true;
}

double	BitcoinExchange::getRateForDate(std::string &date){
	std::map<std::string, double>::iterator it;

	it = _db.find(date);
	if (it != _db.end())
		return it->second;

	it = _db.lower_bound(date);
	if (it == _db.begin())
		throw std::runtime_error(RED"Error: no earlier date in db" RESET);

	if (it == _db.end() || it->first != date)
		--it;

	return it->second;
}

void	BitcoinExchange::processingInputFile(std::string filename){
	std::ifstream file(filename);
	if (!file.is_open())
		throw::std::runtime_error(RED"Error: could not open file." RESET);

	std::string line;
	if (!std::getline(file, line))
		throw::std::runtime_error(RED"Error: file is empty." RESET);

	if (line.compare("date | value") != 0)
		throw::std::runtime_error(RED"Error: missing valid header." RESET);

	while(std::getline(file, line)){
		std::stringstream ss(line);

		//std::cout << "|" << line << "|" << std::endl;
		std::string date;
		std::string amountSTR;
		if (!std::getline(ss, date, '|') || !std::getline(ss, amountSTR) || date.empty() || amountSTR.empty()){
			std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
			continue;
		}
		skipSpaces(date);
		skipSpaces(amountSTR);
		double amount;

		try{
			amount = std::stod(amountSTR);
		} catch (...){
			std::cerr << RED << "Error: bad input => " << date << " " << amountSTR << RESET << std::endl;
			continue;
		}

		if (!isValidDate(date, false) || !isValidAmount(amount)){
			std::cerr << RED << "Error: bad input => " << date << " " << amount << RESET << std::endl;
			continue;
		}

		try {
			double rate = getRateForDate(date);
			std::cout << date << "=> " << amount * rate << std::endl;
		} catch (std::exception &e){
			std::cout << e.what() << std::endl;
		}

	}
}

void	BitcoinExchange::loadDB(){
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw::std::runtime_error(RED"Error: could not open database file." RESET);

	std::string line;
	int	line_count = 1;

	if (!std::getline(file, line))
		throw::std::runtime_error(RED"Error: file is empty." RESET);

	if (line.compare("date,exchange_rate") != 0)
		throw::std::runtime_error(RED"Error: missing valid header." RESET);

	while(std::getline(file, line)){
		line_count++;
		std::stringstream ss(line);
		std::string date;
		std::string rateStr;
		if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr) || date.empty() || rateStr.empty()){
			std::cerr << RED << "Error: Corrupted data on line " << line_count << RESET << std::endl;
			continue;
		}
		if (!isValidDate(date, true)){
			std::cerr << RED << "Error: Incorrect date on line " << line_count << RESET << std::endl;
			continue;
		}
		try{
			_db.insert(std::make_pair(date, std::stod(rateStr)));
		} catch (...){
			std::cerr << RED << "Error: Failed to insert data to map on line " << line_count << RESET << std::endl;
		}
	}
	file.close();
}
