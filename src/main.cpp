/*
 * main.cpp
 *
 *  Created on: Dec 7, 2016
 *      Author: caveman
 */

#include "Global.hpp"
#include "Application.hpp"
#include "Exception.hpp"

using namespace Core;

int main(int argc, char *args[]) {
	try {
		Core::Application* app = new Core::Application("path.cfg", "core.cfg");
		app->go();
	} catch (Core::Exception& e) {
		Core::Exception::die(e.getDescription(), "error.log");
		return 1;
	}
	return 0;
}
