#include "GoodEngineCore/Application.h"
#include <iostream>
#include <memory>

class MyApp :public GoodEngine::Application
{
	virtual void on_update() override
	{
		//std::cout << "Update frame: " << frame++ << std::endl;
	}
	int frame = 0;
};
int main()
{
	auto myApp = std::make_unique<GoodEngine::Application>();
	int out = myApp->start(1024, 768, "MyFirstApp");
	return out;
}