#include "../Header/ClockUtils.h"

void ClockUtils_mainStart(ClockControl* cc) {
	cc->mainStart = clock();
}

void ClockUtils_mainEnd(ClockControl* cc) {
	cc->mainEnd = clock();
}

double ClockUtils_mainDiff(ClockControl cc) {
	return ((cc.mainEnd - cc.mainStart) * 1000) / CLOCKS_PER_SEC;;
}

void ClockUtils_readStart(ClockControl* cc) {
	cc->readStart = clock();
}

void ClockUtils_readEnd(ClockControl* cc) {
	cc->readEnd = clock();
}

double ClockUtils_readDiff(ClockControl cc) {
	return ((cc.readEnd - cc.readStart) * 1000) / CLOCKS_PER_SEC;;
}

void ClockUtils_executeOPStart(ClockControl* cc) {
	cc->executeOPStart = clock();
}

void ClockUtils_executeOPEnd(ClockControl* cc) {
	cc->executeOPEnd = clock();
}

double ClockUtils_executeOPDiff(ClockControl cc) {
	return ((cc.executeOPEnd - cc.executeOPStart) * 1000) / CLOCKS_PER_SEC;;
}
