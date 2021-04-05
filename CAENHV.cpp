#include "CAENHV.hpp"

bool CAEN::connect() {
    int sysHndl = -1;
    CAENHVRESULT ret = -1;
    ret = CAENHV_InitSystem((CAENHV_SYSTEM_TYPE_t)0, lk, (char *)address_.c_str(), username_.c_str(), passwd_.c_str(), &sysHndl);

    if(ret == CAENHV_OK) {
        std::cout << "Mainframe " << name_ << " connection established (sysHndl " << sysHndl << ")" << std::endl;
        sysHndl_ = sysHndl;
        return 1;
    }
    else if(ret == CAENHV_DEVALREADYOPEN) { // Both connections were already open
        std::cout << "Mainframe " << name_ << " connection already established" << std::endl;
        sysHndl_ = sysHndl;
        return 1;
    }
    else return 0;
}

void CAEN::disconnect() {
    std::cout << "Close mainframe connection (sysHndl " << sysHndl_ << ")" << std::endl;
    
    CAENHVRESULT ret = -1;
    ret = CAENHV_DeinitSystem(sysHndl_);
}

int CAEN::getintvalue(std::string param, int ch, int slot) {
    unsigned short *ChList;
    ChList = (unsigned short*)malloc(sizeof(unsigned short));
    ChList[0] = ch;
    
    int *lParValList = NULL;
    lParValList = (int*)malloc(sizeof(int));
    CAENHVRESULT ret = -1;

    ret = CAENHV_GetChParam(sysHndl_, slot, param.c_str(), 1, ChList, lParValList);
    if(ret != CAENHV_OK) {
        std::cout << "CAEN error: num. " << ret << std::endl;
        return -99;
    }
    else {
        return lParValList[0];
    }
}

bool CAEN::setintvalue(std::string param, int ch, int slot, int value) {
    unsigned short *ChList;
    ChList = (unsigned short*)malloc(sizeof(unsigned short));
    ChList[0] = ch;

    int *HVCAEN = NULL;
    HVCAEN = (int*)malloc(sizeof(int));
    HVCAEN[0] = value;
    CAENHVRESULT ret = -1;
    
    ret = CAENHV_SetChParam(sysHndl_, slot, param.c_str(), 1, ChList, HVCAEN);
    if(ret != CAENHV_OK) {
        std::cout << "CAEN error: num. " << ret << std::endl;
        return 0;
    }
    else return 1;    
}

float CAEN::getfloatvalue(std::string param, int ch, int slot) {
    unsigned short *ChList;
    ChList = (unsigned short*)malloc(sizeof(unsigned short));
    ChList[0] = ch;
    
    float *lParValList = NULL;
    lParValList = (float*)malloc(sizeof(float));
    CAENHVRESULT ret = -1;

    ret = CAENHV_GetChParam(sysHndl_, slot, param.c_str(), 1, ChList, lParValList);
    if(ret != CAENHV_OK) {
        std::cout << "CAEN error: num. " << ret << std::endl;
        return -99.;
    }
    else {
        return lParValList[0];
    }
}

bool CAEN::setfloatvalue(std::string param, int ch, int slot, float value) {
    unsigned short *ChList;
    ChList = (unsigned short*)malloc(sizeof(unsigned short));
    ChList[0] = ch;

    float *HVCAEN = NULL;
    HVCAEN = (float*)malloc(sizeof(float));
    HVCAEN[0] = value;
    CAENHVRESULT ret = -1;
    
    ret = CAENHV_SetChParam(sysHndl_, slot, param.c_str(), 1, ChList, HVCAEN);
    if(ret != CAENHV_OK) {
        std::cout << "CAEN error: num. " << ret << std::endl;
        return 0;
    }
    else return 1;   
}

