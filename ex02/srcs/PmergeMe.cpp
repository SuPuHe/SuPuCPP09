/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:05:51 by omizin            #+#    #+#             */
/*   Updated: 2026/01/16 16:52:11 by omizin           ###   ########.fr       */
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

void	fordJonson(std::vector<int> &vector){
	if (vector.size() <= 1)
		throw std::runtime_error(RED"Error: not enought numbers in vector" RESET);

	std::vector<int> hight_nums;
	std::vector<int> low_nums;
	std::vector<int> leftover_nums;

	for (size_t i = 0; i < vector.size(); i += 2){
		if (vector[i] && vector[i + 1]){
			if (vector[i] > vector[i + 1]){
				hight_nums.push_back(vector[i]);
				low_nums.push_back(vector[i + 1]);
			}
			else{
				hight_nums.push_back(vector[i + 1]);
				low_nums.push_back(vector[i]);
			}
		}
		else{
			leftover_nums.push_back(vector[i]);
		}
	}
	std::cout << "\n\nHight\n\n";
	printVector(hight_nums);
	std::cout << "\n\nlow_nums\n\n";
	printVector(low_nums);
	std::cout << "\n\nleftover_nums\n\n";
	printVector(leftover_nums);

}
