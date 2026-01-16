/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:51 by omizin            #+#    #+#             */
/*   Updated: 2026/01/16 13:15:10 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	addNumbersToVec(std::vector<int> &vector, char **numbers){
	for (int i = 1; numbers[i]; i++){
		try{
			size_t	pos;
			std::string line = numbers[i];
			int num = std::stoi(line, &pos);
			if (num < 0 || pos != line.length())
				throw std::runtime_error(RED"Error: incorrect number" RESET);
			vector.push_back(num);
		} catch (std::exception &e){
			throw std::runtime_error(RED"Error: incorrect number" RESET);
		}
	}
}

void	printVector(std::vector<int> &vector){
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}
