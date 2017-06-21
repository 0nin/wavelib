/*
 * Gnuplot.hpp
 *
 *  Created on: Jul 20, 2016
 *      Author: avs
 */

#ifndef GNUPLOT_HPP_
#define GNUPLOT_HPP_

#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include "../Source/Conv.hpp"
#include "../Source/Exception.hpp"
#include "../Source/Global.hpp"

#ifdef _WIN32
#define TMPDIR "./tmp/"
#else
#define TMPDIR "/tmp/"
#endif

//#define "wxt" "wxt"
//#define GNUPLOT_NAME "gnuplot"

namespace Core {

template<typename T>
std::string atos(T real) {
#ifndef _WIN32
	std::string str = std::to_string(real);
#else
	std::ostringstream strs;
	strs << real;
	std::string str = strs.str();
#endif
	return str;
}

class Gnuplot {
public:
	explicit Gnuplot() {
#ifdef _WIN32
		gnuplotpipe = _popen("gnuplot", "w");
#else
		gnuplotpipe = popen("gnuplot > /dev/null 2>1", "w");
#endif
		if (!gnuplotpipe) {
			std::cerr << ("Gnuplot not found !");
		}
	}

	virtual ~Gnuplot() {
		cleanup();
		close();
	}

	void end() {
		this->send("e\n");
	}

	void cmd(const std::string &command) {
		fprintf(gnuplotpipe, "%s\n", command.c_str());
		render();
	}

	void send(const std::string &command) {
		fprintf(gnuplotpipe, "%s\n", command.c_str());
		render();
	}

	template<class Val1, class Val2>
	void sendRAM(const std::list<std::vector<std::pair<Val1, Val2>>>&arg) {
		std::string tmp;

		size_t maxSize=0;
		for (auto it = arg.begin(); it != arg.end(); ++it) {
			if (it->size() > maxSize) maxSize = it->size();
		}

		for (size_t i = 0; i < maxSize; i++) {
			for (auto it = arg.begin(); it != arg.end(); ++it) {
				if (it->size() > i) {
					tmp += atos(it->at(i).first) + " " + atos(it->at(i).second) + " ";
				}
			}

			this->send(tmp);
			tmp.clear();
		}
	}

	template<class Val1, class Val2>
	void plotRAM(const std::list<std::vector<std::pair<Val1, Val2>>>&arg) {
		sendRAM(arg);
		end();
	}

	template <class Val1, class Val2>
	void sendRAM(const std::vector<std::pair<Val1, Val2>> &arg) {
		for (auto it = arg.begin(); it != arg.end(); ++it) {
			this->send(atos(it->first) + " " + atos(it->second));
		}
	}

	template <class Val1, class Val2>
	void plotRAM(const std::vector<std::pair<Val1, Val2>> &arg) {
		sendRAM(arg);
		end();
	}

	template <class Val1, class Val2>
	void plot(const std::vector<std::pair<Val1, Val2>> &arg) {
		plotRAM(arg);
	}

	template <class Val1, class Val2>
	void plot(const std::list<std::vector<std::pair<Val1, Val2>>>&arg) {
		plotRAM(arg);
	}


	template<class Val1, class Val2>
	void plotFile(const std::list<std::vector<std::pair<Val1, Val2>>>&dataList) {
				std::stringstream tmp;
				std::string path;
				std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
				std::vector<std::string> plotDatFiles;

				for (auto it = dataList.begin(); it != dataList.end(); ++it) {
					fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
#ifndef _WIN32
					path = std::string("/tmp/") + fileName;
#else
					path = std::string("./tmp/") + fileName;
#endif
					plotDatFiles.push_back(path);
					this->tmpFiles.push_back(path);
					Conv::vec2dat (*it, path);
		}

		cmd("set grid");
		cmd(std::string("set term ") + "wxt" + std::string(" ") + atos(window));

		//	list2dat(dataList, path);
		typedef std::vector<std::string> StringVec;
		typedef StringVec::const_iterator StringVecCIt;

		for (StringVecCIt it = plotDatFiles.begin(); it != plotDatFiles.end(); ++it) {
			if (it == plotDatFiles.begin()) {
				tmp << "plot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
			}
			else {
				tmp << "replot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
			}

		}

		std::string command = tmp.str();
		cmd (command);

		tmp.str( std::string() );
		tmp.clear();
		this->window++;
	}

	template<class Val1, class Val2>
	void plotFile(const std::vector<std::pair<Val1, Val2>>&dataVec,const std::string &param="") {
		std::stringstream tmp;
		std::string path;
		std::string fileName = "gnuplot" + atos(window) + "_" + rand(3) +".dat";
		std::vector<std::string> plotDatFiles;

			fileName = "gnuplot" + atos(window) + "_" + rand(3) + ".dat";
#ifndef _WIN32
			path = std::string("/tmp/") + fileName;
#else
			path = std::string("./tmp/") + fileName;
#endif
			plotDatFiles.push_back(path);
			this->tmpFiles.push_back(path);
			Conv::vec2dat(dataVec, path);

		cmd("set grid");
		cmd(std::string("set term ") + "wxt" + std::string(" ") + atos(window));

		//	list2dat(dataList, path);
		typedef std::vector<std::string> StringVec;
		typedef StringVec::const_iterator StringVecCIt;

		for (StringVecCIt it = plotDatFiles.begin(); it != plotDatFiles.end(); ++it) {
			if (it == plotDatFiles.begin()) {
				tmp << "plot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
			}
			else {
				tmp << "replot " << " '" << *it << "' " << "using " << 1 << ":" << 2 << " with linespoints pt 7 ps 0.5" << std::endl;
			}

		}

		std::string command = tmp.str();
		cmd (command);

		tmp.str( std::string() );
		tmp.clear();
		this->window++;
	}


	void plotDat(const std::string &path, size_t col) {
		std::stringstream tmp;

		cmd("set grid");
		cmd(
				std::string("set term ") + "wxt" + std::string(" ")
						+ atos(window));

		for (size_t die = 1; die <= 2 * col; die += 2) {
			if (die == 1) {
				tmp << "plot " << " '" << path << "' " << "using " << die << ":"
						<< (die + 1) << " with linespoints pt 7 ps 0.5"
						<< std::endl;
			} else {
				tmp << "replot " << " '" << path << "' " << "using " << die << ":"
						<< (die + 1) << " with linespoints pt 7 ps 0.5"
						<< std::endl;
			}
		}

		std::string command = tmp.str();
		cmd(command);

		tmp.str(std::string());
		tmp.clear();

		window++;
	}


	void run(const std::string &script) {
		//TODO:
	}

	void render(void) {
		fflush(gnuplotpipe); // flush needed to start render
	}

	void cleanup(void) {
		if(!tmpFiles.empty()) {
			for (auto it = tmpFiles.begin(); it != tmpFiles.end(); ++it) {
				if (fileExist(*it)) remove(it->c_str());
			}
		}
	}

	void close(void) {
	cmd("exit");
	#ifdef _WIN32
		_pclose(gnuplotpipe);
	#else
		pclose(gnuplotpipe);
	#endif
	}

protected:
	FILE *gnuplotpipe = nullptr;
	size_t window = 0;
	std::vector<std::string> tmpFiles;
};

}
#endif /* GNUPLOT_HPP_ */
