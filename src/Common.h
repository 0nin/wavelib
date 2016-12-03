/*
 * define.h
 *
 *  Created on: Jun 10, 2016
 *      Author: avs
 */

#ifndef _common_h_
#define _common_h_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>
#include "Define.h"

//#undef NDEBUG

#define DEBUG_IO

#ifdef _WIN32
#define TMPDIR "./tmp/"
#else
#define TMPDIR "/tmp/"
#endif

#define DUMMY 999.99f

#ifdef NDEBUG
#define ENABLE_RUNTIME
#define ENABLE_LOG2FILE
#endif

#endif

