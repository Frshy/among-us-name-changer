#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void throwError(string error) {
	SetConsoleTextAttribute(hConsole, 12);
	printf("[-] Error: %s\n", error.c_str());
}

int main() {

	//settings up path
	string username = getenv("USERNAME");
	ostringstream amongusConfigPath;
	amongusConfigPath << "C:\\Users\\" << username << "\\AppData\\LocalLow\\Innersloth\\Among Us\\playerPrefs";

	//reading config
	ifstream configFile;
	configFile.open(amongusConfigPath.str());
	if (!configFile.good()) {
		throwError("among us config file not found!");
		system("pause");
		return 0;
	}
	stringstream strStream;
	strStream << configFile.rdbuf();
	configFile.close();
	string config = strStream.str();
	
	//asking user for new name
	string newName;
	SetConsoleTextAttribute(hConsole, 14);
	printf("[?] Enter name you want to change to > ");
	cin >> newName;

	//replaceing name in readen file to new name
	string actualName = config.substr(0, config.find(","));
	config.replace(0, actualName.size(), newName);

	//writing file with new name
	ofstream newConfig;
	newConfig.open(amongusConfigPath.str());
	if(!newConfig.good()){
		throwError("can't write the file!");
		system("pause");
		return 0;
	}
	newConfig << config;
	newConfig.close();

	//you receive this message if everything went good
	SetConsoleTextAttribute(hConsole, 10);
	printf("[+] Changed nickname \"%s\" -> \"%s\" \n", actualName.c_str(), newName.c_str());
	system("pause");
	return 0;
}
