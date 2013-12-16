#!/bin/sh

TARGET="naragui"
MODULES="sql"
GMAKE="/usr/local/bin/gmake"
QMAKE="/usr/local/bin/qmake-qt4"
COMPILER=clang
CXX_FLAGS="-m64 -mmmx -msse -msse2 -msse3"

${GMAKE} distclean

${QMAKE} -project

if [ -e ${TARGET}.pro ]
then
	echo "QT += ${MODULES}" >> ${TARGET}.pro;
	echo "modules \"${MODULES}\" was added.";

	#echo "CONFIG += plugin" >> ${TARGET}.pro;
	#echo "CONFIG += plugin added.";

	sed -i -e "s/TARGET =/TARGET = ${TARGET}/g" ${TARGET}.pro;

	sed -i -e 's/TEMPLATE = app/TEMPLATE = lib/g' ${TARGET}.pro;

	echo "QMAKE_CXXFLAGS += ${CXX_FLAGS}" >> ${TARGET}.pro;
	echo "C++ flags \"${CXX_FLAGS}\" was added.";

	${QMAKE} -spec freebsd-${COMPILER}
else
	echo "ERROR: file ${TARGET}.pro not found."
fi
