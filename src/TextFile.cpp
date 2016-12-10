#include "TextFile.hpp"

#include <sstream>
#include <fstream>
#include "Exception.hpp"
#include "Log.hpp"
#include "PathList.hpp"
#include "Global.hpp"

namespace Core {



void TextFile::write(const std::string &text, const std::string &fileName) {
	std::ofstream mFile;
	mFile.open(fileName.c_str());
	if (mFile.is_open()) {
		mFile << text;
		mFile.close();
	} else {
		std::cerr << "I can't write to" + fileName << std::endl;
	}
//	else
//		throw Exception(std::string("I can't write to") + fileName);
}

void TextFile::clear(const std::string &fileName) {
	//не работает
}



TextFile::TextFile(const std::string &fileName) :
		fileName(fileName), fileCopy() {
}

TextFile::~TextFile(void) {
}

void TextFile::operator<<(const std::string &str) {
	write(str);
}

void TextFile::setFile(const std::string &fileName) {
	std::string fullPath;
//	this->fileName = fileName;
//	std::fstream m_stream;
//	m_stream.open(fileName.c_str());
//	m_stream.close();

//	if (PathList::getSingletonPtr()->getPath(fileName, fullPath)) {
	if (getPath()->getPath(fileName, fullPath)) {
		this->fileName = fileName;
		std::fstream m_stream;
		m_stream.open(fileName.c_str());
		m_stream.close();
	} else {
//		std::cerr << "Can't find file:: " << fileName;
		throw ExceptionNoFile(fileName);
	}
}

void TextFile::write(const std::string &text) {
	write(text, this->fileName);
	return;
}

void TextFile::copy(void) {
	std::string line;
	std::ifstream m_file(this->fileName.c_str());
	if (m_file.is_open()) {
		while (getline(m_file, line)) {
			this->fileCopy.push_back(line);
		}
		m_file.close();
		line.clear();
	} else {
		std::cerr << "I can't open to" + fileName << std::endl;
	}
//	else
//		throw Exception("I can't open file" + this->fileName);
}


void TextFile::clear(void) {
	clear(this->fileName);
}

void TextFile::print(void) {
//	std::vector<std::string>::const_iterator it = fileCopy.begin();
	for (auto it = fileCopy.begin(); it != fileCopy.end(); it++)
		std::cout << *(it) << " " << std::endl;
}

} /* namespace Core */
