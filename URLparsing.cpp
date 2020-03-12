#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
// strut to hold the components of the URL
struct url {
    bool invalidUrl; // boolean flag for

    std::string protocol;
    std::string domain;
    std::string port;
    std::string filePath;
    std::string parameters;

    bool validProtocol;
    bool validDomain;
    bool validPort;
    bool validFilePath;

};

// function used to find a specfic charatcer in a string
int findCharacter(url &userURL, std::string userEntry, char charToFind) {
    for (int i = 0; i < userEntry.length(); i++) { // for the length of the given string, check for the character
        if (userEntry[i] == charToFind) { // if character is found
            return i; // return the index of it
        }
    }
    userURL.invalidUrl = true; // if reached, the character was not found - syntax error
    return -1; // return
}

void getProtocol(url &userUrl, std::string &userEntry) {
    int indexOfChar = findCharacter(userUrl, userEntry, ':'); // finds the ":" which marks the end of the protocol
    if (!userUrl.invalidUrl) { // ensures that the : is found
        std::string protocol = userEntry.substr(0, indexOfChar); // removes the protocol from the string
        if (protocol == "http" || protocol == "https" || protocol == "ftp" || protocol == "ftp" ||
            protocol == "ftps") { // checks that it is a valid protocol
            userUrl.protocol = protocol; // if so, sets the protocol
        } else {
            userUrl.validProtocol = false; // if the conditions were not met, the protocol is invalid
            userUrl.protocol = protocol + " is not a valid protocol."; // add the error message to the protocol
        }
        std::string endOfProtocol = userEntry.substr(indexOfChar, 3);
        if (!(endOfProtocol == "://")) {
            userUrl.invalidUrl = true; // invalid
            return;
        }
        userEntry = userEntry.substr(indexOfChar + 3); // removes the protocol & "://" from the string
    } else {
        cout << "The URL entered is not in the correct syntax."
             << endl; // the ":" was not found, therefore invalid sntax
    }

}

void getDomain(url &userUrl, std::string &userEntry) {
    int indexOfFirstPart = findCharacter(userUrl, userEntry, '.');
    int indexOfSecondPart = findCharacter(userUrl, userEntry.substr(indexOfFirstPart + 1),
                                          '.'); // finds the second "."
    indexOfSecondPart += indexOfFirstPart + 1; // removes the .

    if (indexOfSecondPart == indexOfFirstPart + indexOfSecondPart) { // there are no characters between the "."s
        userUrl.validDomain = false; // not a valid domain
    }
    int indexOfEndOfDomain = findCharacter(userUrl, userEntry, ':'); // checks if the URL has a port
    if (indexOfEndOfDomain == -1) { // if not
        indexOfEndOfDomain = findCharacter(userUrl, userEntry, '/'); // find the start of the file path
    }
    userUrl.domain = userEntry.substr(0, indexOfEndOfDomain); // separates the domain

    // checks if the domain is NOT .com, .net, .edu, .biz. or .gov
    std::string host = userUrl.domain.substr(indexOfSecondPart);
    if (!(host == ".com" || host == ".net" || host == ".edu"
          || host == ".biz" || host == ".gov")) {
        userUrl.validDomain = false; // if incorrect, set validDomain to false
        userUrl.domain = host;
    }

    if (!userUrl.validDomain) { // if invalid domain
        userUrl.domain.append(" is an invalid domain"); // attach the error message
    }

    userEntry = userEntry.substr(indexOfEndOfDomain); // trim the userEntry down

}

void getPort(url &userUrl, std::string &userEntry) {
    if (userEntry.at(0) != ':') { // if the first character is not ":", the URL does not have a port
        return; // return to main
    } else { // the URL has a port
        userEntry = userEntry.substr(1); // remove the ":" from the string for processing
        int indexOfSlash = findCharacter(userUrl, userEntry, '/'); // find the start of the file path
        userUrl.port = userEntry.substr(0, indexOfSlash); // separate the port from the string
        int port = std::stoi(userUrl.port); // convert the string to an int
        if (port > 65535 || port < 1) { // check if the port is out of the bounds
            userUrl.validPort = false; // if so, it is false
            userUrl.port = "port number must be between 1 and 65535"; // add the error message
        }
        userEntry = userEntry.substr(indexOfSlash); // remove the port from the userEntry
    }

}

void getFilePath(url &userUrl, std::string &userEntry) {
    if (userEntry.at(0) != '/') { // if it does not start with '/', it is invalid
        userUrl.validFilePath = false;
    }

    int indexOfEndOfFilePath = findCharacter(userUrl, userEntry, '?'); // find the start of the parameter

    if (indexOfEndOfFilePath == -1) {
        indexOfEndOfFilePath = findCharacter(userUrl, userEntry, '\n'); // find the end of the line
    }

    std::string filePath = userEntry.substr(0, indexOfEndOfFilePath); // separate the file path

    int indexOfPeriod = findCharacter(userUrl, filePath, '.'); // find the index of the '.'
    userUrl.filePath = userEntry.substr(0, indexOfEndOfFilePath); // set the file path
    if (filePath.substr(indexOfPeriod) == ".html" ||
        filePath.substr(indexOfPeriod) == ".htm") { //  checks for the correct file path ending
        userUrl.validFilePath = true; // if correct, the file path is valid
    } else { // if not
        userUrl.filePath.append(" is not a valid file path."); // add the warning message
        userUrl.validFilePath = false; // set the file path to invalid
    }

    userEntry = userEntry.substr(indexOfEndOfFilePath); // remove the file path from the string

}

void getParameters(url &userUrl, std::string &userEntry) {
    if (!userEntry.empty()) {
        if (userEntry.at(0) != '?') {
            userUrl.invalidUrl = true; // the URL is invalid
            return;
        }
        userUrl.parameters = userEntry;
    }
}


int main() {

    url userUrl; // creates an instance of a URL
    // initalizes the variables
    userUrl.invalidUrl = false;
    userUrl.validProtocol = true;
    userUrl.validDomain = true;
    userUrl.validPort = true;
    userUrl.validFilePath = true;


    cout << "Please enter a URL." << endl; // prompts the user
    std::string userEntry; // declares the user input
    getline(cin, userEntry); // gets the input from the user

    getProtocol(userUrl, userEntry); // gets the protocol
    getDomain(userUrl, userEntry); // gets the domain
    getPort(userUrl, userEntry); // gets the port
    getFilePath(userUrl, userEntry); // gets the file path
    getParameters(userUrl, userEntry); // gets the parameters

    if (userUrl.invalidUrl) { // if a syntax error was found
        cout << "The URL that was entered was of the incorrect syntax. " << endl; // print message
    } else { // if syntax error was not found

        if (!userUrl.validProtocol || !userUrl.validDomain || !userUrl.validPort ||
            !userUrl.validFilePath) { // if any part of the URL was not valid
            cout << "Invalid URL with following erroneous components" << endl;
            if (!userUrl.validProtocol) {
                cout << left << setw(15) << "Protocol: " << userUrl.protocol << endl;
            }
            if (!userUrl.validDomain) {
                cout << left << setw(15) << "Domain: " << setw(40) << userUrl.domain << endl;
            }
            if (!userUrl.validPort) {
                cout << left << setw(15) << "Port: " << setw(40) << userUrl.port << endl;
            }
            if (!userUrl.validFilePath) {
                cout << left << setw(15) << "File Path: " << setw(40) << userUrl.filePath << endl;
            }

        } else { // if all components are valid
            cout << left << setw(15) << "Protocol: " << userUrl.protocol << endl;
            cout << left << setw(15) << "Domain: " << userUrl.domain << endl;
            cout << left << setw(15) << "Port: " << userUrl.port << endl;
            cout << left << setw(15) << "File Path: " << userUrl.filePath << endl;
            cout << left << setw(15) << "Parameters: " << userUrl.parameters << endl;
        }
    }

}
