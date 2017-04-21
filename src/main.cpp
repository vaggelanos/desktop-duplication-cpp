#include "application.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE, char*, int showCommand) {
	//SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	auto config = application::config{};
	config.instanceHandle = instanceHandle;
	config.showCommand = showCommand;
	config.displays.push_back(0); // TODO: parse commandline / config file

	application app(std::move(config));
    return app.run();
}
