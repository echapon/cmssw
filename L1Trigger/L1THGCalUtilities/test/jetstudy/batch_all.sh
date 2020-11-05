#!/bin/bash

# first argument, from 0 to 10: variation


dir=/afs/cern.ch/user/e/echapon/workspace/private/HGCAL/CMSSW_11_2_0_pre2/test

cd $dir
eval `scramv1 runtime -sh`


# towers only from unclustered TCs
if [ $1 -eq 0 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_fulltowers_20200724/200724_193136/0000/ntuple_*.root' $dir/eos/trees/default/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 1 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_fixphismooth_20200928/200928_115702/0000/ntuple_*root' $dir/eos/trees/fixphismooth/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 2 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_noarea_20201027/i201027_101806/0000/ntuple_*root' $dir/eos/trees/noarea/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 3 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_rphi_thr6p5_20200930/200930_164718/0000/ntuple_*root' $dir/eos/trees/rphi_thr6p5/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 4 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_xyseed_20200930/200930_082231/0000/ntuple_*root' $dir/eos/trees/xyseed/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 5 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200724/200724_192515/0000/ntuple_*root' $dir/eos/trees/default/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
elif [ $1 -eq 6 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_fixphismooth_20200928/200928_120045/0000/ntuple_*root' $dir/eos/trees/fixphismooth/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
elif [ $1 -eq 7 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_noarea_20201027/201027_101848/0000/ntuple_*root' $dir/eos/trees/noarea/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
elif [ $1 -eq 8 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164803/0000/ntuple_*root' $dir/eos/trees/rphi_thr6p5/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
elif [ $1 -eq 9 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_xyseed_20200930/200930_081900/0000/ntuple_*root' $dir/eos/trees/xyseed/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
elif [ $1 -eq 10 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_fulltowers_20200724/200724_192226/0000/ntuple_*root' $dir/eos/trees/default/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 11 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_fixphismooth_20200928/200928_115406/0000/ntuple_*root' $dir/eos/trees/fixphismooth/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 12 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_noarea_20201027/201027_101533/0000/ntuple_*root' $dir/eos/trees/noarea/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 13 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_rphi_thr6p5_20200930/200930_164538/0000/ntuple_*root' $dir/eos/trees/rphi_thr6p5/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 14 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_with_2dclusters_20200925/200925_133422/0000/ntuple_*root' $dir/eos/trees/with2dclusters/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 15 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_xyseed_20200930/200930_082425/0000/ntuple_*root' $dir/eos/trees/xyseed/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 16 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200724/200724_180823/0000/ntuple_*root' $dir/eos/trees/default/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
elif [ $1 -eq 17 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_fixphismooth_20200928/200928_115518/0000/ntuple_*root' $dir/eos/trees/fixphismooth/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
elif [ $1 -eq 18 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_noarea_20201027/201027_101620/0000/ntuple_*root' $dir/eos/trees/noarea/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
elif [ $1 -eq 19 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164623/0000/ntuple_*root' $dir/eos/trees/rphi_thr6p5/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
elif [ $1 -eq 20 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_xyseed_20200930/200930_082334/0000/ntuple_*root' $dir/eos/trees/xyseed/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root



# full towers
elif [ $1 -eq 21 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_fulltowers_20200722/200722_162737/0000/ntuple_*.root' $dir/eos/trees/default/fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
elif [ $1 -eq 22 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_fulltowers_20200723/200723_101343/0000/ntuple_*.root' $dir/eos/trees/default/fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
elif [ $1 -eq 23 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200723/200723_143747/0000/ntuple_*root' $dir/eos/trees/default/fulltowers/noPUsub/output_VBF_HToInvisible_PU200.root 
elif [ $1 -eq 24 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200723/200723_143747/0000/ntuple_*root' $dir/eos/trees/default/fulltowers/PUsub/output_VBF_HToInvisible_PU200.root doPU
elif [ $1 -eq 25 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200723/200723_143616/0000/ntuple_*root' $dir/eos/trees/default/fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root 
elif [ $1 -eq 26 ]; then
$dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200723/200723_143616/0000/ntuple_*root' $dir/eos/trees/default/fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root doPU
fi


### BACKUP
# # towers only from unclustered TCs
# if [ $1 -eq 0 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_fulltowers_20200724/200724_192226/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_rphi_thr6p5_20200930/200930_164538/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_unclseltowers_xyseed_20200930/200930_082425/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
# elif [ $1 -eq 1 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_fulltowers_20200724/200724_193136/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_rphi_thr6p5_20200930/200930_164718/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_unclseltowers_xyseed_20200930/200930_082231/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
# elif [ $1 -eq 2 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200724/200724_180823/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164623/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_xyseed_20200930/200930_082334/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root
# elif [ $1 -eq 3 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200724/200724_180823/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root doPU
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164623/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root doPU
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_unclseltowers_xyseed_20200930/200930_082334/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root doPU
# elif [ $1 -eq 4 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200724/200724_192515/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164803/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_xyseed_20200930/200930_081900/0000/ntuple_*root' $dir/unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root
# elif [ $1 -eq 5 ]; then
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200724/200724_192515/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root doPU
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_rphi_thr6p5_20200930/200930_164803/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root doPU
# # $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/unclunseltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_unclseltowers_xyseed_20200930/200930_081900/0000/ntuple_*root' $dir/unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root doPU


# # full towers
# elif [ $1 -eq 6 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_NoPU_fulltowers_20200722/200722_162737/0000/ntuple_*.root' $dir/fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root
# elif [ $1 -eq 7 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU_fulltowers_20200723/200723_101343/0000/ntuple_*.root' $dir/fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root
# elif [ $1 -eq 8 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200723/200723_143747/0000/ntuple_*root' $dir/fulltowers/noPUsub/output_VBF_HToInvisible_PU200.root 
# elif [ $1 -eq 9 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF_HToInvisible_PU200_fulltowers_20200723/200723_143747/0000/ntuple_*root' $dir/fulltowers/PUsub/output_VBF_HToInvisible_PU200.root doPU
# elif [ $1 -eq 10 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200723/200723_143616/0000/ntuple_*root' $dir/fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root 
# elif [ $1 -eq 11 ]; then
# $dir/hgcalL1JetPerf '/eos/cms/store/group/phys_heavyions/echapon/HGCal/l1jetperf/fulltowers/RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_fulltowers_20200723/200723_143616/0000/ntuple_*root' $dir/fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root doPU
# fi
