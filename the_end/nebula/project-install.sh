#!/bin/bash

PROJNAME="project_nebula"
PROJDIR="/home/masterdesky/GitHub/ELTE_Modelling_Lab_2021/project/project_nebula"
GEANT4INSTALL="/home/masterdesky/apps/Geant4/install"

# Source Geant4
if [ -f ${GEANT4INSTALL}/bin/geant4.sh ];
then
    cd ${GEANT4INSTALL}/bin/
    source geant4.sh
    cd ~-
fi

if [ ! -d ${PROJDIR}/NEBULA_build ];
then
  mkdir -p ${PROJDIR}/NEBULA_build
else
  rm -rf ${PROJDIR}/NEBULA_build/*
fi
cd ${PROJDIR}/NEBULA_build
cmake -DGeant4_DIR=${GEANT4INSTALL}/lib/Geant4-10.7.1/ \
			${PROJDIR}/NEBULA \
			|& tee >(ts "[%x %X]" > ${PROJDIR}/NEBULA_build/c.log)
make -j4 NEBULA |& tee >(ts "[%x %X]" > ${PROJDIR}/NEBULA_build/m.log)