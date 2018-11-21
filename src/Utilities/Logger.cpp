#include <iostream>
#include <sstream>
#include "Logger.h"

using namespace std;

Logger::Logger()
{
    string greeting = "GAMES LIBRARY";
    string options = "OPTIONS";
    string limiter1 = string(greeting.length(), '=');
    string limiter2 = string(options.length(), '-');

    ostringstream oss;
    oss << greeting << endl << limiter1;

    headers["greeting"] = oss.str();
    oss.str(string());

    oss << limiter2 << endl
        << options << endl
        << limiter2;

    headers["options"] = oss.str();
    oss.str(string());

    oss << "Welcome to Games Library, a simple games library manager written in C++" << endl;

    info["instructions"] = oss.str();
    oss.str(string());

	headers["AddedToList"] = " added to board words list.";

    input["options"] = "1 - Add title\n0 - Exit\nSelect an option: ";

    info["extracting"] = "Extracting...";
    info["WriteFinished"] = "Writing finished.";

    errors["NotImplemented"] = "Function not yet implemented.\n";
    errors["InvalidOption"] = "Please insert a valid option!\n";
}

void Logger::error(const string &errorKey)
{
    setcolor(LIGHTRED);
    cerr << errors[errorKey] << endl;
    setcolor(WHITE);
}

void Logger::log(const string &infoKey)
{
    setcolor(WHITE);
    cout << info[infoKey] << endl;
}

void Logger::header(const string &headerKey)
{
    setcolor(YELLOW);
    cout << headers[headerKey] << endl;
    setcolor(WHITE);
}

void Logger::logInput(const std::string &inputKey)
{
    cout << input[inputKey];
}
