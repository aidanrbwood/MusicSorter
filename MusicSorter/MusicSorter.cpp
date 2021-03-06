// Written by Aidan Wood aidanrbwood@gmail.com / 2017

#include "stdafx.h"
//#define TAGLIB_STATIC 
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <taglib\tag.h>
#include <boost\filesystem.hpp>
#include <string>
#include "ErrorFile.cpp"
#include "LibraryDB.h"
#include "SongException.h"

/*

*/

void createNewPath(SongNode*, boost::filesystem::path, boost::filesystem::path);
bool isMusicFile(boost::filesystem::path);

int main(int argc, char *argv[])
{
	errorClass errors;
	std::cout << "start" << std::endl;
	if (argc == 3) {
		boost::filesystem::path unsortedPath(argv[1]); //path to target file
		boost::filesystem::path libraryPath(argv[2]); //path to target folder
		if (is_directory(unsortedPath) && is_directory(libraryPath)) { // if no exception and the file at the following path exists
			LibraryDB library(libraryPath);

			for (boost::filesystem::recursive_directory_iterator unsorted(unsortedPath);
				unsorted != boost::filesystem::recursive_directory_iterator();
				unsorted++) {
				if (isMusicFile(unsorted->path())) {
					try {
						SongNode *currentSong = new SongNode(unsorted->path());
						std::cout << unsorted->path() << std::endl;
						if (library.addArtist(currentSong)) {
							createNewPath(currentSong, libraryPath, unsorted->path());
						}
					}
					catch (SongException e) {
						std::cout << e.what() << std::endl;
					}
				}
			}
		}
		else
			errors.errorFunction(2);
	}
	else
		errors.errorFunction(1);
	std::cout << "end" << std::endl;
	system("pause");
	return 0;
}

void createNewPath(SongNode* s, boost::filesystem::path library, boost::filesystem::path unsorted) {
	std::string pathAsString = library.string();
	boost::filesystem::path artistPath(pathAsString + "\\" + s->artist());
	boost::filesystem::path albumPath(artistPath.string() + "\\" + s->album());
	boost::filesystem::path songPath(albumPath.string() + "\\" + s->name() + unsorted.extension().string());
	
	if (!is_directory(artistPath))
		boost::filesystem::create_directory(artistPath);
	if (!is_directory(albumPath))
		boost::filesystem::create_directory(albumPath);
	boost::filesystem::copy_file(unsorted, songPath);
}

bool isMusicFile(boost::filesystem::path p) {
	std::string ext = p.extension().string();
	if (!boost::filesystem::is_directory(p) && (ext == ".mp3" || ext == ".wav" || ext == ".flac" || ext == ".m4a" || ext == ".aiff" || ext == ".pcm" || ext == ".alac" || ext == ".ogg" || ext == ".wma")) {
		return true;
	}
	else
		return false;
}
