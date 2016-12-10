#ifndef _PathList_h_
#define _PathList_h_

#include "Common.h"

namespace Core {

class PathList;

class PathList {

public:
	PathList() {
		const char *env = getenv("PATH");

		_pathList.push_back("./");  // present directory
		_pathList.push_back("../"); // back one
		_pathList.push_back("../../"); // back two

		if (env) {
			_pathList.push_back(std::string(env) + "/"); // Path lacks a terminating slash
		}
	}

	void addPath(const std::string &path) {
		_pathList.push_back(path);
	}

	void clearPaths() {
		_pathList.clear();
	}

	bool getFilePath(const std::string &file, std::string &path) {
		std::string pathString;

		for (std::vector<std::string>::iterator it = _pathList.begin();
				it != _pathList.end(); it++) {
			pathString = *it + file;
			FILE *fp = fopen(pathString.c_str(), "rb");
			if (fp) {
				fclose(fp);
				path = pathString;
				return true;
			}
		}

		return false;
	}

	bool getPath(const std::string &file, std::string &path) {
		std::string pathString;

		for (std::vector<std::string>::iterator it = _pathList.begin();
				it != _pathList.end(); it++) {
			pathString = *it + file;
			FILE *fp = fopen(pathString.c_str(), "rb");
			if (fp) {
				fclose(fp);
				path = *it;
				return true;
			}
		}

		return false;
	}

	void print() {
		for (auto it = _pathList.begin(); it != _pathList.end(); it++) {
			std::cout << *(it) << std::endl;
		}

	}

private:
	std::vector<std::string> _pathList;

};

}
#endif // _PathList_h_
