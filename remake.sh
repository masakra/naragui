#!/bin/sh

TARGET="naragui"
MODULES="sql"
GMAKE="/usr/local/bin/gmake"
QMAKE="/usr/local/bin/qmake-qt4"

${GMAKE} distclean

${QMAKE} -project

if [ -e ${TARGET}.pro ]
then
	echo "QT += ${MODULES}" >> ${TARGET}.pro;
	echo "modules \"${MODULES}\" was added.";

	#echo "CONFIG += plugin" >> ${TARGET}.pro;
	#echo "CONFIG += plugin added.";

	sed -i -e "s/TARGET =/TARGET = ${TARGET}/g" ${TARGET}.pro;

	#sed -i -e 's/TEMPLATE = app/TEMPLATE = lib/g' ${TARGET}.pro;

	${QMAKE} -spec freebsd-clang
else
	echo "ERROR: file ${TARGET}.pro not found."
fi
