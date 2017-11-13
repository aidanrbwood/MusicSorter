// MusicSorter.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#define TAGLIB_STATIC 
#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>
#include <Windows.h>
#include <boost\filesystem.hpp>
#include <string>



using namespace TagLib;
using namespace std;
using namespace boost::filesystem;


int main(int argc, char *argv[])
{
	if (argc == 3) {
		FileRef* song = NULL; //taglib reference to target file
		path targetFile(argv[1]); //path to target file
		path targetFolder(argv[2]); //path to target folder
		bool exceptionCaught = false;

		try {
			song = new FileRef(argv[1]); //try to create file reference with user defined path
		}
		catch (const filesystem_error& ex) {
			cout << "Exception caught:" << ex.what(); // catch exception
			exceptionCaught = true;
		}
		if (!exceptionCaught && exists(targetFile) && is_directory(targetFolder)) { // if no exception and the file at the following path exists
			Tag *plz = song->tag(); // pull tag from target file and print artist
			String fileArtist = plz->artist();

			for (directory_iterator artistFolder(targetFolder); // create directory iterator that will cycle through ever folder in the target directory
				artistFolder != directory_iterator();
				artistFolder++) {
				path current = artistFolder->path();
				int targetFolderLength = targetFolder.string().length();
				if (fileArtist == current.string().substr(targetFolderLength)) //print the path of each element in the target folder without the inital targetfolder path
					cout << "folder yay" << endl;
			}

		}
		else
			cout << "Invalid file or invalid target folder";
	}
	else
		cout << "Invalid number of arguments, remember you need a target directory and a source folder" << endl;
	Sleep(3000);
	return 0;
}

