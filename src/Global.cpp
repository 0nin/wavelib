/*
 * Global.cpp
 *
 *  Created on: 29 Jul 2016
 *      Author: avs
 */

#include "Global.hpp"

#include "Application.hpp"
#include "Exception.hpp"
#include "PathList.hpp"

using namespace Core;
namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

const char digits[] = "0123456789.\t\n";
static PathList singletonPathList;

Core::PathList* getPath () {
	return &singletonPathList;
}


double getDummy() {
#ifdef _WIN32
	return 0.0f;
#else
	return 0.0f;
#endif
}


std::string rand(size_t range) {
	static std::random_device rd;  // only used once to initialise (seed) engine
	std::mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
	const static char* ch = "ABCDEFGHIJKLMNOPQRSTUWXYZabcdefghijklmnopqrstuwxyz";
	std::uniform_int_distribution<int> uni(0, 49); // guaranteed unbiased

	std::string str;
	for (size_t i = 0; i < range; i++) { //length-1 for the '\0' at the end
		str.push_back(ch[uni(rng)]);
	}

	return str;
}

bool fileExist(const std::string &name) {
	static std::ofstream file;
	file.open(name);
	return file.is_open();
}


bool vec2csv(const std::vector<std::pair<double, double>>&dataList,
		const std::string &out) {
	std::stringstream tmp;
	std::string file;
	std::ofstream write;
	typedef std::vector<std::pair<double, double>>::const_iterator DataVecCIt;

	for (DataVecCIt it = dataList.begin(); it != dataList.end(); ++it) {
		tmp << it->first << "," << it->second << "," << std::endl;
		file += tmp.str();
		tmp.str(std::string());
		tmp.clear();

	}

	write.open(out);
	if (write.is_open()) {
		write << file;
		write.close();
	} else
		return false;
	file.clear();

	return true;
}


bool isDigit(char ch) {
//	const char digits[] = "0123456789.\t\n ";
	size_t N = sizeof(digits) / sizeof(char);

	for (size_t i = 0; i < N; i++) {
		if (ch == digits[i])
			return true;
	}
	return false;
}


bool normListNoRet(std::list<std::vector<std::pair<double, double>>>&inData) {
	if(inData.empty())
	return false;
	typedef std::list<std::vector<std::pair<double, double>>> DataList;

	for (DataList::iterator it = inData.begin(); it != inData.end(); ++it) {
		normVecNoRet (*it);
	}

	return true;
}

bool comp(std::pair<double, double> i, std::pair<double, double> j) {
	return (i.second > j.second);
}

double getTauVec(const std::vector<std::pair<double, double>>&dataVec) {
	if (dataVec.empty()) {
		return (double) 0.0f;
	}

	typedef std::vector<std::pair<double, double>> DataVec;
	typedef DataVec::const_iterator DataVecCIt;
	typedef std::vector<std::pair<double, double>> IntVec;
	typedef IntVec::const_iterator InVecCIt;
	InVecCIt maxIt;
	double result = 0.0f;
	IntVec intervals, ones; // withCopy

	for (DataVecCIt it = dataVec.begin(); it != dataVec.end(); ++it) {
		if (it->second == (double) 1.0f) {
			for (DataVecCIt jt = it + 1; jt != dataVec.end(); ++jt) {
				if (jt->second == (double) 1.0f) {
					intervals.push_back(
							std::make_pair(it->first, jt->first - it->first));
					break;
				} else {
					continue;
					//do nothing;
				}
			}
		} else {
			//do nothing
		}

		if (it->second == (double) 1.0f) {
			if (it != dataVec.end())
				ones.push_back(*it);
		}
	}

	for (auto it = ones.begin(); it != ones.end() - 1; ++it) {
		it->second = (it + 1)->first - it->first;
	}

	std::sort(ones.begin(), ones.end(), comp);

	for (size_t i = 1; i < ones.size() - 2; i++) {
		if (ones[i].first < ones[0].first) {
			result = ones[i].first + ones[1].second - dataVec[0].first;
			break;
		} else {
			continue;
		}
	}

#ifdef NDEBUG
	std::cout << "TAU: " << result << std::endl;
#endif

	if (!intervals.empty()) {
		intervals.clear();
	}
	if (!ones.empty()) {
		ones.clear();
	}

	return result;
}

double getTauList(const std::list<std::vector<std::pair<double, double>>>&dataList) {
#ifndef NDEBUG
	throw ExceptionNotImplemented("getTauList");
#endif
	return (double)0.0f;
}
