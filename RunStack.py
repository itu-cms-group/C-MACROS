#!/usr/bin/python

import sys
from ROOT import gROOT
from ROOT import TFile
from ROOT import TKey
def GetKeyNames( self ):
        return [key.GetName() for key in MyFile.GetListOfKeys()]
TFile.GetKeyNames = GetKeyNames

MyFile=TFile("/home/cakir/NtuplerAnalyzer/SusySignals/ThirdRuns/NoPU/diboson/DeepSingle+DelphMET_NoPU_DiBoson_his.root")
keyList = MyFile.GetKeyNames()
print "\nKeys in file:", keyList

# scenarios and samples
scenarios = ['NoPU']
conditions=['TreeS','TreeB']
gROOT.ProcessLine(".L /home/cakir/Desktop/PlottingTool/denemeStack.C")
for scene in scenarios:
	for samp in keyList:
		print "Key :", samp
		print "Scene:", scene  
		if not samp=='TreeS' or samp=='TreeB':	 
			from ROOT import denemeStack
			denemeStack(scene,samp)
		else:
			break
			print "THE END"

