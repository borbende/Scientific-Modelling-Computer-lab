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

cd ${PROJDIR}/NEBULA_build

PHYSICS_LIST=('QBBC' 'QGSP_BERT_HP' 'QGSP_BIC_HP' 'QGSP_INCLXX' 'QGSP_INCLXX_HP')
for PHYS in "${PHYSICS_LIST[@]}"
do
  # Create folder for data if not exists already
  DATADIR=${PROJDIR}/data/${PHYS}
  if [[ ! -d ${DATADIR} ]];
  then
    mkdir -p ${DATADIR}
  fi

  for ENERGY in {45..355..10}
  do
    # Change the macro and include particle energy
    cp ${PROJDIR}/NEBULA/run1.mac ${PROJDIR}/NEBULA_build/run1.mac
    sed -i '/^\/gun\/energy/ { s|$| '"${ENERGY}"' MeV| }' ${PROJDIR}/NEBULA_build/run1.mac

    # Run the simulation macro
    ${PROJDIR}/NEBULA_build/${PROJNAME} ${PHYS} ${PROJDIR}/NEBULA_build/run1.mac

    # Append the energy to the name of the data files and move them to the
    # data folder
    for f in ${PROJDIR}/NEBULA_build/NEBULA*
    do
      mv "${f}" $(echo "${f}" | sed 's/.csv/_'"${ENERGY}"'MeV.csv/g')
    done
    mv ${PROJDIR}/NEBULA_build/NEBULA* ${DATADIR}
  done
done


cd ${PROJDIR}