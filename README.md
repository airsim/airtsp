C++ Simulated Airline Travel Solution Provider (TSP) Library
============================================================

# Summary
AirTSP is also named AirTSP (TSP standing for Travel Service Provider).
That project aims at providing a clean API and a simple implementation,
as a C++ library, of an Airline Schedule Management System. It is intended
to be used in simulated environments only: it is not designed to work
in the real-world of Airline IT operations.

AirTSP/AirTSP makes an extensive use of existing open-source libraries
for increased functionality, speed and accuracy. In particular the
Boost (C++ Standard Extensions: http://www.boost.org) library is used.

AirTSP/AirTSP is the one of the components of the Travel Market Simulator
(https://travel-sim.org). However, it may be used in a
stand-alone mode.

# Installation

## On Fedora/CentOS/RedHat distribution
Just use DNF:
```bash
$ dnf -y install airtsp-devel airtsp-doc
```

You can also get the RPM packages (which may work on Linux
distributions like Suse and Mandriva) from the Fedora repository
(_e.g._, for Fedora 32,
https://fr2.rpmfind.net/linux/RPM/fedora/32/x86_64/)


## Building the library and test binary from Git repository
The Git repository may be cloned as following:
```bash
$ git clone git@github.com:airsim/airtsp.git airtspgit # through SSH
$ git clone https://github.com/airsim/airtsp.git # if the firewall filters SSH
$ cd airtspgit
```

Then, you need the following packages (Fedora/RedHat/CentOS names here, 
but names may vary according to distributions):
* stdair-devel
* boost-devel / libboost-dev
* python-devel / python-dev
* gettext-devel / gettext-dev
* sqlite3-devel / libsqlite3-dev
* readline-devel / readline-dev
* ncurses-devel
* soci-mysql-devel, soci-sqlite3-devel
* doxygen, ghostscript, graphviz
* tetex-latex (optional)
* rpm-build (optional)


## Building the library and test binary from the tarball
The latest stable source tarball (`airtsp*.tar.gz` or `.bz2`) can be found here:
https://github.com/airsim/airtsp/releases

To customise the following to your environment, you can alter the path
to the installation directory:
```bash
export INSTALL_BASEDIR="${HOME}/dev/deliveries"
export AIRTSP_VER="1.01.9"
if [ -d /usr/lib64 ]; then LIBSUFFIX="64"; fi
export LIBSUFFIX_4_CMAKE="-DLIB_SUFFIX=$LIBSUFFIX"
```

Then, as usual:
* To configure the project, type something like:
```bash
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/airtsp-$AIRTSP_VER \
   -DWITH_STDAIR_PREFIX=${INSTALL_BASEDIR}/stdair-stable \
   -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON -DINSTALL_DOC:BOOL=ON \
   -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
```
* To build the project, type:
```bash
make
```
* To test the project, type:
```bash
make check
```
* To install the library (`libairtsp*.so*`) and the binary (`airtsp`), just type:
```bash
  make install
  cd ${INSTALL_BASEDIR}
  rm -f airtsp-stable && ln -s airtsp-${AIRTSP_VER} airtsp-stable
  cd -
```
* To package the source files, type:
```bash
make dist
```
* To package the binary and the (HTML and PDF) documentation:
```bash
make package
```
* To browse the (just installed, if enabled) HTML documentation:
```bash
  midori file://${INSTALL_BASEDIR}/airtsp-$AIRTSP_VER/share/doc/airtsp/html/index.html
```
* To browse the (just installed, if enabled) PDF documentation:
```bash
  evince ${INSTALL_BASEDIR}/airtsp-$AIRTSP_VER/share/doc/airtsp/html/refman.pdf
```
* To run the local binary version:
```bash
./airtsp/airtsp -b
```
* To run the installed version:
```bash
  ${INSTALL_BASEDIR}/airtsp-$AIRTSP_VER/bin/airtsp -b
```

Denis Arnaud (May 2015)

