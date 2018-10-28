#ifndef GUESSER_HPP
#define GUESSER_HPP
#include "nlohmann\json.hpp"
#include "question_composer.hpp"
#include "presenter.hpp"
#include <vector>
#include <random>
#include <ctime>

struct Properties
{
	std::vector<int> contains;
	std::vector<int> not_contains;
	int divisible;
	std::vector<int> not_divisible;
	int greater_than;
	int less_than;
	std::string order;
	std::list<std::string> not_order;
	std::string pending;

	void set_defaults();
	void process_pending(std::string property);
};

struct Question
{
	std::string content;
	std::string type;

	void set_defaults();
};

enum question_type {
	digit_existence,
	number_comparison,
	divisibility_rule,
	sorted_flag,
	enough
};

class Guesser
{
private:
	static std::vector<int> wrong_numbers;
	static Question question;
	static Properties num_properties;

	static void process_num_comparison_answer(const bool &answer);
	static void number_assemblance_check();
	static std::vector<int> assemble_number();

	friend class QuestionComposer;

public:
	static bool can_be_assembled;

	static void add_wrong_number(int number);
	static question_type get_random_question_type();
	static std::string get_question(const question_type &type);
	static void process_answer(const bool &answer);
	static int get_potential_number();
	static void init();
};

#endif