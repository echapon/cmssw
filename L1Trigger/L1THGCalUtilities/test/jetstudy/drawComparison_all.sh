#!/bin/bash


rootlb -q drawComparison.C'("unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root","fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU.root","RelValDiQ_Pt20To300_Etam1p6Tom2p9_NoPU")'
rootlb -q drawComparison.C'("unclunseltowers/noPUsub/output_VBF_HToInvisible_NoPU.root","fulltowers/noPUsub/output_VBF_HToInvisible_NoPU.root","VBF_HToInvisible_NoPU")'

rootlb -q drawComparison.C'("unclunseltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root","fulltowers/noPUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root","RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200")'
rootlb -q drawComparison.C'("unclunseltowers/noPUsub/output_VBF_HToInvisible_PU200.root","fulltowers/noPUsub/output_VBF_HToInvisible_PU200.root","VBF_HToInvisible_PU200")'

rootlb -q drawComparison.C'("unclunseltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root","fulltowers/PUsub/output_RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200.root","RelValDiQ_Pt20To300_Etam1p6Tom2p9_PU200_PUsub")'
rootlb -q drawComparison.C'("unclunseltowers/PUsub/output_VBF_HToInvisible_PU200.root","fulltowers/PUsub/output_VBF_HToInvisible_PU200.root","VBF_HToInvisible_PU200_PUsub")'
