#include <iostream>
#include <limits>
#include "Utilities\Date.h"
#include "GameLibrary.h"
#include "Utilities/Logger.h"
#include "Title/HomeTitle.h"
#include "Title/OnlineTitle.h"
#include "Title/FixedSubscription.h"
#include "Title/DynamicSubscription.h"

using namespace std;

Logger logger;

void handle_option1(GameLibrary &gl)
{
    string titleType;
    string name;
    double price;
    int minAge, maxAge;
    unsigned int year, month, day;
    string platform;
    string genre;
    string company;

    cout << "Insert title type (home, online): " << endl;
    cin >> titleType;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Name: "<< endl;
    getline(cin, name);

    cout << "Price: " << endl;
    cin >> price;

    cout << "Age Range (minAge, maxAge): " << endl;
    cin >> minAge >> maxAge;
    struct ageRange ar{minAge, maxAge};

    cout << "Release date (year, month, day): " << endl;
    cin >> year >> month >> day;
    Date releaseDate(day, month, year);

    cout << "Platform: " << endl;
    cin >> platform;

    cout << "Genre: " << endl;
    cin >> genre;

    cout << "Publisher: " << endl;
    cin >> company;


    //Title(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
    if (titleType == "home")
        gl.addTitle(new HomeTitle(name, price, releaseDate, ar, platform, genre, company));
    else if (titleType == "online") {
        string subscriptionType;
        double subsPrice;

        cout << "Subscrition type (fixed, dynamic): " << endl;
        cin >> subscriptionType;

        cout << "Subscription price: " << endl;
        cin >> subsPrice;

        if (subscriptionType == "fixed") {
            gl.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new FixedSubscription(subsPrice)));
        } else if (subscriptionType == "online") {
            gl.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new DynamicSubscription(subsPrice)));
        } else {
            logger.error("InvalidOption");
        }
    }

}

int main()
{
    GameLibrary gl = GameLibrary();

    logger.header("greeting");
    logger.log("instructions");

    unsigned char option;

    logger.header("options");

    while (true) {
        logger.logInput("options");
        cin >> option;

        if (!cin.fail() && (option == '0' || option == '1')) {
            switch (option) {
            case '1': {
                //logger.error("NotImplemented");
                handle_option1(gl);
                break;
            }
            case '0': exit(0); //TODO: Call destructors

            default: // it's very unlikely that code execution will get here
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else {
            logger.error("InvalidOption");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

