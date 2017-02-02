#!/usr/bin/python


import sys
from ROOT import gROOT
from ROOT import TFile
from ROOT import TKey


# scenarios and samples
methods = ['KNN',"BDT","Likelihood","PDERS","LD","RuleFit","RF","SVM","MLPBNN","FDA_GA","PDEFOAM","LikelihoodPCA"]
Vb=['HT','MT','MET','MT2W'] #variables
C_KNN=[0.04,0.05] #cut values
C_RF=[]#[-80,-75,-70,-65,-60]
C_BDT=[]#[0.06,0.07,0.08,0.09]
SOB=["1","0"] #signal or background
gROOT.ProcessLine(".L /home/cakir/TMVA-v4.2.0/test/StackSigBckg.C")
for myth in methods:
	if myth=='KNN':
        	for vari in Vb:
                	for c_knn in C_KNN:
        	                print "Cut :", c_knn
                                print "myth:", myth
                                from ROOT import StackSigBckg 
                                StackSigBckg(vari,myth,c_knn)
                                print "KNN END"

