# CAENHVpython

Simple python bindings to CAEN HV boards

## Setup

First you must install the CAEN HV Wrapper C library: https://www.caen.it/products/caen-hv-wrapper-library/

Then you have to copy the include file `CAENHVWrapper.h` to this repo.

On the python side, only the `pybind11` package is required:

``` pip install pybind11```

After this, just run the `build.sh` file:

``` sh build.sh ```

A file `CAENHV.cpython-...` should be created, this is the package only a class CAEN is included inside, that will connect to the mainframe via IP. To import it:

``` from CAENHV import CAEN ```

## Usage

First thing is to import:

``` from CAENHV import CAEN ```

Then create the object:

``` CAEN1 = CAEN(name, username, password, ip_address) ```

All the parameters in init are strings. meaning of each one:

- name: A name of your choice for the object.
- username: username of the mainframe.
- password: password of the mainframe.
- ip_address: ipaddress of the mainframe.

After that you should connect to the mainframe:

``` CAEN1.connect() ```

It will return True if successful, False if not.

