/**
 * async renderer to map the values onto the image
 */

#include <vector>

using namespace std;

void mapPointValues();

void mapData (vector< vector<int> > coordinates);

int estPt (int ptValue, int ptCoord, vector< vector<int> > sensorData);