#include "presenter.hpp"
#include <ctime>

int main()
{
	srand((unsigned)time(NULL));
	Presenter App;
	App.main_loop();
}