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

void	splitIntoPairs(std::vector<int> &vector, std::vector<int> &high_nums, std::vector<int> &low_nums, int &leftover){
	if (vector.size() <= 1)
		return;
	for (size_t i = 0; i + 1 < vector.size(); i += 2){
		if (vector[i] > vector[i + 1]){
			high_nums.push_back(vector[i]);
			low_nums.push_back(vector[i + 1]);
		}
		else{
			high_nums.push_back(vector[i + 1]);
			low_nums.push_back(vector[i]);
		}
	}

	if (vector.size() % 2 != 0)
		leftover = vector.back();
}

void	insertLowNums(std::vector<int> &insert_vector, std::vector<int> &low_nums){
	(void)insert_vector;
	(void)low_nums;
}

void binaryInsert(std::vector<int> &insert_vector, int leftover){
	(void)insert_vector;
	(void)leftover;
}

void	fordJohnson(std::vector<int> &vector){
	if (vector.size() <= 1)
		return;

	std::vector<int> high_nums;
	std::vector<int> low_nums;
	int	leftover = -1;

	splitIntoPairs(vector, high_nums, low_nums, leftover);

	fordJohnson(high_nums);

	std::vector<int> insert_vector;

	insertLowNums(insert_vector, low_nums);

	if (leftover != -1)
		binaryInsert(insert_vector, leftover);

	vector = insert_vector;
}
