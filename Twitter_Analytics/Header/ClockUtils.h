#ifndef _CLOCKUTILSH_
#define _CLOCKUTILSH_

#include <time.h>

typedef struct s_ClockControl {
	clock_t mainStart, mainEnd;
	clock_t readStart, readEnd;
	clock_t executeOPStart, executeOPEnd;
} ClockControl;

void ClockUtils_mainStart(ClockControl* cc);
void ClockUtils_mainEnd(ClockControl* cc);
double ClockUtils_mainDiff(ClockControl cc);

void ClockUtils_readStart(ClockControl* cc);
void ClockUtils_readEnd(ClockControl* cc);
double ClockUtils_readDiff(ClockControl cc);

void ClockUtils_executeOPStart(ClockControl* cc);
void ClockUtils_executeOPEnd(ClockControl* cc);
double ClockUtils_executeOPDiff(ClockControl cc);

#endif _CLOCKUTILSH_