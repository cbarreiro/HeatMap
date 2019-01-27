#include "../include/Collector.h"

CCollector::CCollector() {
    CUart* colUart = new CUart;  // Initialize collector UART connection
}

CCollector::~CCollector() {}

void CCollector::collect(void) {
    // Reset colBuf to dummy values
    memset(colBuf, -150.0, sizeof(colBuf));
    // Reset timeout counter
    int collectCounter = 0;

    while (!colExitFlag) {
        // Collect data from a single node through UART
        colUart->uartRx();

        // Flatten and clone the current UART buffer, and check if all nodes
        // have viable data. If so, throw colCompleteFlag
        vector<float> flatTemp;

        transform(colUart->tempData.begin(),
                  colUart->tempData.end(),  // Flatten vector
                  back_inserter(flatTemp),
                  [&flatTemp](const pair<float, float>& p) {
                      flatTemp.push_back(p.first);
                      return p.second;
                  });

        // If all values are non-dummy, or if collector timeouts, exit
        // collection
        if (std::none_of(flatTemp.begin(), flatTemp.end(),
                         [](float i) { return i != -300.0; }) ||
            collectCounter > 100)
            colExitFlag = 1;

        collectCounter++;
    }

    // At this point, there should be a fully valid tempData buffer in UART
    // object OR the collector has timed out
    for (int i = 0; i < colUart->tempData.size(); i++) {
        if (abs(tempData[i].first - tempData[i].second) < 5 &&
            tempData[i].first != -300.0)
            colBuf[i] = tempData[i].first;
    }
}