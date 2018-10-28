#include "UI.hpp"

using namespace std;

void CLI::ask_question(std::string question)
{
	cout << question << endl;
	cout << "Y/N?" << endl;
}

bool CLI::get_answer()
{
	string answer;
	getline(cin, answer);

	return answer == "y" ||
		   answer == "Y";
}
