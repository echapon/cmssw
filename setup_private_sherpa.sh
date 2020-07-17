#!/bin/bash

origsherpa="/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/sherpa/2.2.8-pafccj2"
mysherpa="/afs/cern.ch/user/e/echapon/workspace/private/Sherpa/CMSSW_10_6_7/sherpa"

# environment variables
export SHERPA_INCLUDE_PATH=${mysherpa}/include/SHERPA-MC
export SRT_SHERPA_INCLUDE_PATH_SCRAMRTDEL=${mysherpa}/include/SHERPA-MC
export SRT_SHERPA_SHARE_PATH_SCRAMRTDEL=${mysherpa}/share/SHERPA-MC
export SHERPA_LIBRARY_PATH=${mysherpa}/lib/SHERPA-MC
export SRT_SHERPA_LIBRARY_PATH_SCRAMRTDEL=${mysherpa}/lib/SHERPA-MC
export SHERPA_SHARE_PATH=${mysherpa}/share/SHERPA-MC

# configuration files
configfiles="../.SCRAM/slc7_amd64_gcc820/MakeData/variables.mk ../.SCRAM/slc7_amd64_gcc820/MakeData/Tools/sherpa.mk ../.SCRAM/slc7_amd64_gcc820/MakeData/Tools.mk ../config/toolbox/slc7_amd64_gcc820/tools/selected/sherpa.xml ../external/slc7_amd64_gcc820/links.DB"
origsherpa_p=$(echo $origsherpa | sed 's/\//\\\//g')
mysherpa_p=$(echo $mysherpa | sed 's/\//\\\//g')
for file in $configfiles; do
   echo $file
   sed -i 's/'$origsherpa_p'/'$mysherpa_p'/g' $file | grep '10_6_7/sherpa'
done
