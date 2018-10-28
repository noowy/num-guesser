#ifndef QUESTION_COMPOSER_HPP
#define QUESTION_COMPOSER_HPP
#include "guesser.hpp"
#include <string>
#include <vector>
#include <ctime>

static class QuestionComposer
{
public:
	static std::string compose_digit_question(const std::vector<int> &exceptions);
	static std::string compose_number_question(const int &bot_boundary = 100, 
											   const int &top_boundary = 999);
	static std::string compose_divisibility_question(const std::vector<int> &exceptions);
	static std::string compose_sorted_question(const std::list<std::string> &exceptions);
};

#endif