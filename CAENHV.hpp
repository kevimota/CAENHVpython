#ifndef CAEN_H
#define CAEN_H

#include "CAENHVWrapper.h"
#include <iostream>
#include <string>
#include <stdlib.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

class CAEN {
    private:
        std::string name_;
        std::string username_;
        std::string passwd_;
        std::string address_;
        
        int sysHndl_ = -1;
        int lk = LINKTYPE_USB_VCP;
        //int lk = LINKTYPE_TCPIP;
        /* int CAEN_CONN = 0;
        int MAX_ATTEMPTS = 3;
        int ATTEMPTS = 0;
        int ATTEMPTS_CONN = 1; */
        
    public:
        CAEN(std::string name, std::string commport, std::string baudrate, std::string commdata, std::string commstop, std::string commparity, std::string lbusaddress) {
            name_ = name;
            username_ = "";
            passwd_ = "";
            address_ = commport + "_" + baudrate + "_" + commdata + "_" + commstop + "_" + commparity + "_" + lbusaddress;
        };
        bool connect();
        void disconnect();
        bool setintvalue(std::string param, int ch, int slot, int value);
        bool setfloatvalue(std::string param, int ch, int slot, float value);
        int getintvalue(std::string param, int ch, int slot);
        float getfloatvalue(std::string param, int ch, int slot);
        int getSysHndl() {
            return sysHndl_;
        };
        float getISet(int ch, int slot) { 
            return getfloatvalue("ISet", ch, slot); 
        };
        bool setISet(int ch, int slot, float value) {
            return setfloatvalue("ISet", ch, slot, value);
        };
        float getVSet(int ch, int slot) { 
            return getfloatvalue("VSet", ch, slot); 
        };
        bool setVSet(int ch, int slot, float value) {
            return setfloatvalue("VSet", ch, slot, value);
        };
        float getVMon(int ch, int slot) {
            return getfloatvalue("VMon", ch, slot);
        };
        float getIMon(int ch, int slot) {
            return getfloatvalue("IMonH", ch, slot);
        };
        float getStatus(int ch, int slot) {
            return getintvalue("ChStatus", ch, slot);
        };
        bool powerOn(int ch, int slot) {
            return setintvalue("Pw", ch, slot, 1);
        };
        bool powerOff(int ch, int slot){
            return setintvalue("Pw", ch, slot, 0);
        };
};

const char *doc_init = R"(Creates the CAEN obj.
- arg0 - name: A name of your choice for the object.
- arg1 - username: username of the mainframe.
- arg2 - passwd: password of the mainframe.
- arg3 - address: ipaddress of the mainframe.)";

PYBIND11_MODULE(CAENHV, m) {
    m.doc() = "Module to connect to CAEN HV boards";
    py::class_<CAEN>(m, "CAEN")
        .def(py::init<std::string, std::string, std::string, std::string, std::string, std::string, std::string>(), doc_init)
        .def("connect", &CAEN::connect, "Connect to the mainframe")
        .def("disconnect", &CAEN::disconnect, "Disconnect from the mainframe")
        .def("setintvalue", &CAEN::setintvalue, "Set a int value on parameter 'param' of the 'slot.ch' of the mainframe")
        .def("setfloatvalue", &CAEN::setfloatvalue, "Set float value on parameter 'param' of the board on 'slot.ch' of the mainframe")
        .def("getintvalue", &CAEN::getintvalue, "Get a int value on parameter 'param' of the board on 'slot.ch' of the mainframe")
        .def("getfloatvalue", &CAEN::getfloatvalue, "Get float value on parameter 'param' of the the board on 'slot.ch' of the mainframe")
        .def("getSysHndl", &CAEN::getSysHndl, "Returns the handler of the connection (for debug purposes)")
        .def("getISet", &CAEN::getISet, "Get the I0Set parameter of the board on 'slot.ch' of the mainframe")
        .def("setISet", &CAEN::setISet, "Set value on I0Set parameter of the board on 'slot.ch' of the mainframe")
        .def("getVSet", &CAEN::getVSet, "Get the V0Set parameter of the board on 'slot.ch' of the mainframe")
        .def("setVSet", &CAEN::setVSet, "Set value on V0Set parameter of the board on 'slot.ch' of the mainframe")
        .def("getVMon", &CAEN::getVMon, "Get the VMon parameter of the board on 'slot.ch' of the mainframe")
        .def("getIMon", &CAEN::getIMon, "Get the IMon parameter of the board on 'slot.ch' of the mainframe")
        .def("getStatus", &CAEN::getStatus, "Get the Status parameter of the board on 'slot.ch' of the mainframe")
        .def("powerOn", &CAEN::powerOn, "Power on the channel 'slot.ch' of the mainframe")
        .def("powerOff", &CAEN::powerOff, "Power off the channel 'slot.ch' of the mainframe");
}

#endif