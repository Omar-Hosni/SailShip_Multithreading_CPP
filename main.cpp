#include <iostream>
#include <queue>
#include <thread>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;


namespace ship {

	void clean() {
		std::cout << "\nCleaning Crew\t: Aye, aye, Captain! We will polish the ship." << std::endl;
		std::cout << "Cleaning Crew\t: Ship has been cleaned! Captain." << std::endl << std::endl << std::endl;
	}

	void fullSpeedAhead() {
		std::cout << "Engine Crew\t: Aye, aye, Captain! We are throttling the engines to max speed!" << std::endl;
		std::cout << "Engine Crew\t: The ship has reached full speed, Captain!" << std::endl << std::endl << std::endl;
	}

	void stopTheEngine() {
		std::cout << "Engine Crew\t: Aye, aye, Captain! We are hitting the brakes!" << std::endl;
		std::cout << "Engine Crew\t: The ship has stopped, Captain!" << std::endl << std::endl << std::endl;
	}

}

class TaskScheduler {
	std::queue<unsigned short int> _engineCrewTasks;
	std::queue<unsigned short int> _cleaningCrewTasks;

	unsigned short int _input;
	std::vector<std::string> _commands;


	void showIntro() {
		std::cout << "Ship Captain's Task Scheduling Program" << std::endl;
		std::cout << "======================================" << std::endl;
	}

	void showTasks() {
		std::cout << "\n\nCommands Available : " << std::endl;
		for (auto a : _commands) {
			std::cout << a << std::endl;
		}
	}

	void handleInput() {
		switch (_input)
		{
		case 1:_engineCrewTasks.emplace(_input);
			break;
		case 2:_engineCrewTasks.emplace(_input);
			break;
		case 3:_cleaningCrewTasks.emplace(_input);
			break;
		default:
			std::cout << "Invalid command." << std::endl;
			break;
		}
	}

	void performEngineTasks() {
		if (!_engineCrewTasks.empty()) {
			auto task = [](unsigned short int cmd) {
				if (cmd == 1) ship::stopTheEngine();
				else ship::fullSpeedAhead();
			};
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			task(_engineCrewTasks.front());
			_engineCrewTasks.pop();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

	void performCleanTasks() {
		if (!_cleaningCrewTasks.empty()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			ship::clean();
			_cleaningCrewTasks.pop();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}


public:
	TaskScheduler() :_input{ 0 }, _commands{ "1)\tStop Engine","2)\tFull Speed Ahead","3)\tClean","100)\tExit Task Scheduler" }{
	}


	void scheduleTask() {

		while (true)
		{
			showIntro();
			showTasks();

			std::cout << "\nEnter any command:";
			std::cin >> _input;
			if (_input != 100) {
				handleInput();
			}
			else break;

			std::thread engine_task_scheduler{ &TaskScheduler::performEngineTasks,this };
			engine_task_scheduler.detach();
			std::thread clean_task_scheduler{ &TaskScheduler::performCleanTasks,this };
			clean_task_scheduler.detach();
		}
	}
};


int main() {
	TaskScheduler scheduler;
	scheduler.scheduleTask();
}
