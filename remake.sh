#!/bin/sh

TARGET="naragui"
MODULES="sql"
VERSION="0.2.0"

if [ ${OS} ]	# На Win* выдает что-то типа Windows_NT, на других платформах не определена
then
	GMAKE="/c/MinGW/bin/mingw32-make";
	QMAKE="/c/Qt/4.8.4/bin/qmake";
	LIBS="-L../narapg/release -lnarapg"
else
	GMAKE="/usr/local/bin/gmake"
	QMAKE="/usr/local/bin/qmake-qt4"
	LIBS="-L../narapg -lnarapg"
fi

DEFINES="VERSION=\\\\\\\"${VERSION}\\\\\\\""	# aaaaaaaaaaaaaaaaa fuck !!
INCLUDEPATH="../narapg"

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

	# includepath
	echo "INCLUDEPATH += ${INCLUDEPATH}" >> ${TARGET}.pro;
	echo "include += ${INCLUDEPATH}";


	echo "QMAKE_CXXFLAGS += ${CXX_FLAGS}" >> ${TARGET}.pro;
	echo "C++ flags \"${CXX_FLAGS}\" was added.";

	${QMAKE}
else
	echo "ERROR: file ${TARGET}.pro not found."
fi
