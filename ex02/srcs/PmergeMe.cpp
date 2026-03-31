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

size_t	comparison_count(bool print) {
	static size_t comparison_count = 0;
	if (print)
		return comparison_count;
	return comparison_count += 1;
}

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

size_t binarySearch(std::vector<int> &arr, int target, size_t end){
	size_t left = 0;
	size_t right = end;
	while (left < right) {
		comparison_count(false);
		size_t mid = left + (right - left) / 2;
		if (arr[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

void fordJohnson(std::vector<int>& arr) {
	size_t n = arr.size();
	if (n <= 1)
		return;

	bool has_leftover = (n % 2 != 0);
	int leftover = has_leftover ? arr.back() : 0;

	std::vector<std::pair<int, int>> pairs;
	for (size_t i = 0; i + 1 < n; i += 2) {
		comparison_count(false);
		if (arr[i] < arr[i + 1])
			pairs.push_back({arr[i + 1], arr[i]});
		else
			pairs.push_back({arr[i], arr[i + 1]});
	}

	std::vector<int> main_chain;
	for (auto& p : pairs)
		main_chain.push_back(p.first);
	fordJohnson(main_chain);
	// printVector(main_chain);

	std::vector<int> pending;
	for (int high : main_chain) {
		for (auto it = pairs.begin(); it != pairs.end(); it++) {
			if (it->first == high) {
				pending.push_back(it->second);
				pairs.erase(it);
				break;
			}
		}
	}
	// printVector(pending);

	static const size_t jacobsthal[] = {
		1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845,
		43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405
	};

	std::vector<int> result = main_chain;
	if (!pending.empty())
		result.insert(result.begin(), pending[0]);

	size_t last_jacob = 1;

	bool inserted_leftover = false;
	size_t leftover_threshold = 0;
	if (has_leftover) {
		size_t hp2 = 1;
		while ((hp2 * 2) <= n)
			hp2 *= 2;
		leftover_threshold = hp2 - 1;
	}

	for (size_t j = 1; pending.size() > 1; j++) {
		size_t curr_jacob = jacobsthal[j];
		if (curr_jacob > pending.size())
			curr_jacob = pending.size();

		for (size_t i = curr_jacob; i > last_jacob; i--) {
			int target = pending[i - 1];

			auto it_pair = std::find(result.begin(), result.end(), main_chain[i - 1]);
			size_t limit = std::distance(result.begin(), it_pair);

			size_t pos = binarySearch(result, target, limit);
			result.insert(result.begin() + pos, target);
		}

		if (has_leftover && !inserted_leftover && result.size() >= leftover_threshold) {
			size_t pos = binarySearch(result, leftover, result.size());
			result.insert(result.begin() + pos, leftover);
			inserted_leftover = true;
		}

		if (curr_jacob == pending.size())
			break;
		last_jacob = curr_jacob;
	}

	if (has_leftover && !inserted_leftover) {
		size_t pos = binarySearch(result, leftover, result.size());
		result.insert(result.begin() + pos, leftover);
	}

	arr = result;
}
