#!/bin/bash

for file in `cat files_VBF_NoPU.txt`; do
   cmsRun testTowerPerf_fortest_cfg.py inputFiles=$file
   root -l -b -q printScan.C
done
