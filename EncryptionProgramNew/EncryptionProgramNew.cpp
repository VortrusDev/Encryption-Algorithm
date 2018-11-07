// EncryptionProgramNew.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;
#define RANDOM_LIMIT ((1000 + 1 - 100) + 100)
#define NUM_SUBSTITUTE 3 //The number of corresponding numbers to any given character. If 3, a = 123. If 4, a = 1234, etc 

fstream FilePathStream; //stream to the file we are working on

vector<unsigned char> FileData; //the data in the file to be encrypted

void GetPathToFile();

string EncryptOrDecrypt();

void FillFileData();

bool Encrypt(); //returns true or false for whether the file was encrypted correctly

bool Decrypt(); //returns true or false for successful or unsuccessful decryption

string GetPassword(); //prompt user to enter password and returns it

int main()
{
	srand(time(NULL)); //set random seed every time different

	bool programPassed; //did the program work right? 

	GetPathToFile(); //Get the path to the file to open

	string encOrDec = EncryptOrDecrypt(); //find out if encrypting or decrypting

	if (encOrDec == "encrypt")
	{
		programPassed = Encrypt();
	}
	else
	{
		programPassed = Decrypt();
	}
}

bool Encrypt()
{
	map<char, int> contentMap; //The map for reference of characters; a=111, for example. Then you can find it with find('a')

	map<char, int>::iterator iterator; //for iteration over contentMap

	string encryptedDataString;

	string password; //What is used to decrypt the file

	FillFileData();

	cout << "File contents read. Encrypting file..." << endl;

	int randomNum = 0;

	for (int i = 0; i < FileData.size(); i++)
	{

		while (randomNum < 101 || randomNum > 999)
		{
			randomNum = rand() % RANDOM_LIMIT;
		}

		iterator = contentMap.find(FileData[i]);
		
		if (iterator == contentMap.end())
		{
			if (FileData[i] != '\n')
			{
				contentMap[FileData[i]] = randomNum; //limits 100 to 999, but allows us to store the chars
				cout << FileData[i] << " = " << randomNum << endl;
				password += FileData[i];
			}
		}
		else
		{
			randomNum = iterator->second;
		}

		if (FileData[i] == '\n') //If it's a new line, set it to write end of line chars instead of the regular ones
		{
			encryptedDataString += "100";
		}
		else
		{
			encryptedDataString += to_string(randomNum);
		}
		randomNum = 0;
	}

	cout << encryptedDataString << endl;

	cout << "The file was successfully encrypted. Copy the next line of characters and paste it somewhere safe." << endl << password;

	return true;

}

bool Decrypt()
{

	map<int, unsigned char> valueMap; //the vector which assigns values to characters so they can be decrypted

	cout << "Decrypting file." << endl;

	FillFileData();

	string pw = GetPassword();

	int pass_increment = 0; //increment the number so that each 3 numbers that is UNIQUE is taken into account

	string originalFileData(FileData.begin(), FileData.end());

	string newFileData = originalFileData;

	string newFileDataSpaces = newFileData;

	for (int i = 0; i < newFileData.length(); i++)
	{
		newFileDataSpaces.at(i) = ' ';
	}

	cout << "Num to go to: " << (originalFileData.length() / NUM_SUBSTITUTE) + 1 << endl;

	bool lastValueWasNewLine = false;
	int numOfNewLineCounts = 0;

	for (int i = 0; i <= (originalFileData.length() / NUM_SUBSTITUTE); i++)
	{
		int val; //temporary value variable

			try
			{
				if (originalFileData.substr(i*NUM_SUBSTITUTE, NUM_SUBSTITUTE) != "100")
				{
					val = stoi(originalFileData.substr(i*NUM_SUBSTITUTE, NUM_SUBSTITUTE));
					lastValueWasNewLine = false;
					cout << "LAST WAS NOT NEW: " << lastValueWasNewLine << endl;
				}
				else
				{
					val = 100;
					if (lastValueWasNewLine == false)
					{
						pass_increment--;
						numOfNewLineCounts++;

						//Worked for only one password combo.

						//if (numOfNewLineCounts == 2)
						//{
						//	pass_increment += numOfNewLineCounts - 1;
						//}
						//if (numOfNewLineCounts == 3)
						//{
						//	pass_increment -= numOfNewLineCounts -4;
						//}
						//if (numOfNewLineCounts == 4)
						//{
						//	pass_increment += numOfNewLineCounts - 7;
						//}
						lastValueWasNewLine = true;
					}
				}
				map<int, unsigned char>::iterator mapIt = valueMap.find(val);
				if (mapIt == valueMap.end()) //check if it has the key already...
				{
					if (pw.length() > pass_increment)
					{
						valueMap[val] = pw.at(pass_increment);
					}
					pass_increment++;
				}
			}
			catch (invalid_argument e)
			{
				cout << endl << "Password is too long for the file. The decrypted file may be partially incorrect." << endl;
			}
			catch (out_of_range e)
			{
				cout << endl << "An error occurred - out_of_range exception, error code 0x01. Please report this." << endl;
			}

			string charAtPoint = "";
			stringstream ss;

			map<int, unsigned char>::iterator mapIt2 = valueMap.find(val);
			if (valueMap.count(val))
			{
				char c = valueMap.at(val);
				string s;
				try {
					ss << c;
					ss >> s;
					charAtPoint = string() + s;
				}
				catch (out_of_range e)
				{
					cout << endl << "An error occurred - out_of_range exception, error code 0x02. Please report this." << endl;
				}
				try {
					newFileDataSpaces = newFileDataSpaces.replace(i, NUM_SUBSTITUTE, charAtPoint);
				}
				catch (out_of_range e)
				{
					cout << endl << "An error occurred - out_of_range exception, error code 0x03. Please report this." << endl;
				}
			}
			if (val == 100)
			{
				newFileDataSpaces = newFileDataSpaces.replace(i, NUM_SUBSTITUTE, "\n");
			}
	}
	cout << "Decrypted string: " << newFileDataSpaces << endl;

	return true;

}

string GetPassword()
{
	char password[1024];

	string passwordString;

	while (passwordString.length() == 0)
	{
		cout << "Please enter the password for this file given to you upon encryption." << endl;

		cin.getline(password, sizeof(password));

		passwordString = password;
	}

	return passwordString;
}

void FillFileData()
{
	if (FilePathStream.is_open() == false) //If it's false, there is no defined path
	{
		cerr << "The file path is invalid. Please restart and try again." << endl;
		return;
	}

	while (!FilePathStream.eof()) //get the file data and assign it to fileData
	{
		FileData.push_back(FilePathStream.get());
	}
}

string EncryptOrDecrypt()
{
	string in, inLower;

	while (in != "encrypt" && in != "decrypt")
	{
		cout << "Would you like to encrypt or decrypt this file? Type \"quit\" to quit." << endl;

		cin >> in;

		inLower = in;

		for (int i = 0; i <= in.length(); i++) //convert to lowercase and store in the string - this is to 
										  //make it case-insensitive
		{
			inLower[i] = tolower(in[i]);
		}

		if (inLower == "quit")
		{
			exit(0);
		}
	}

	return in;
}

void GetPathToFile() //Gets the path to the file to encrypt
{
	string path, lowerPath; //the path inputted from the user and the path converted to a lowercase one

	while (FilePathStream.is_open() == false) //while the stream isn't open (aka we don't have a file path)
	{
		cout << "Please enter the complete file path to the file which you would like to encrypt or decrypt." <<
			"Type \"quit\" to quit." << endl;

		cin >> path;

		lowerPath = path; //assign to make it same length as path

		for (int i = 0; i <= path.length(); i++) //convert to lowercase and store in the string - this is to 
											  //make it case-insensitive
		{

			lowerPath[i] = tolower(path[i]);
		}

		if (lowerPath == "quit")
		{
			exit(0);
		}

		ifstream pathStream(path);

		if (!pathStream)
		{
			cerr << "Unable to open the file provided." << endl;
		}
		else
		{
			FilePathStream.open(path.c_str()); //Open the file and exit the loop
		}
	}

}
