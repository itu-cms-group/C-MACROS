#!/usr/bin/python

import sys
from ROOT import gROOT
from ROOT import TFile
from ROOT import TKey

MyFile=TFile("/home/cakir/NtuplerAnalyzer/SusySignals/ThirdRuns/NoPU/diboson/DeepSingle+DelphMET_NoPU_DiBoson_his.root")

# scenarios and samples
methods = ['KNN',"BDT","Likelihood","PDERS","LD","RuleFit","RF","SVM","MLPBNN","FDA_GA","PDEFOAM","LikelihoodPCA"]
Vb=['HT','MT','MET','MT2W'] #variables
C_KNN=[0.04,0.05] #cut values
C_RF=[]#[-80,-75,-70,-65,-60]
C_BDT=[]#[0.06,0.07,0.08,0.09]
C_SVM=[]
C_MLPBNN=[]
C_FDA_GA=[]
C_LD=[]
C_PDEFOAM=[]
C_PDERS=[]
C_LikelihoodPCA=[]
C_Likeli=[]


SOB=["1","0"] #signal or background
gROOT.ProcessLine(".L /home/cakir/TMVA-v4.2.0/test/ReadTMVA.C")
gROOT.ProcessLine(".L /home/cakir/TMVA-v4.2.0/test/ReadTMVAWOCut.C")
for sb in SOB:
	for myth in methods:
		if myth=='KNN':
			for vari in Vb:
				for c_knn in C_KNN:
					print "Cut :", c_knn
					print "myth:", myth  
					from ROOT import ReadTMVA
					ReadTMVA(vari,myth,c_knn,sb)
				#	from ROOT import ReadTMVAWOCut
				#	ReadTMVAWOCut(vari,myth,sb)
					print "KNN END"
		if myth=='BDT':
			for vari in Vb:
                                for c_bdt in C_BDT:
                                        print "Cut :", c_bdt
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_bdt,sb)
                                        print "BDT END"
                if myth=='PDERS':
                        for vari in Vb:
                                for c_pders in C_PDERS:
                                        print "Cut :", c_pders
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_pders,sb)
                                        print "PDERS END"
                if myth=='Likelihood':
                        for vari in Vb:
                                for c_likeli in C_Likeli:
                                        print "Cut :", c_likeli
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_likeli,sb)
                                        print "Likelihood END"
                if myth=='LD':
                        for vari in Vb:
                                for c_ld in C_LD:
                                        print "Cut :", c_ld
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_ld,sb)
                                        print "LD END"

                if myth=='RuleFit':
                        for vari in Vb:
                                for c_rf in C_RF:
                                        print "Cut :", c_rf
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_rf,sb)
                                        print "RuleFit END"
                if myth=='SVM':
                        for vari in Vb:
                                for c_svm in C_SVM:
                                        print "Cut :", c_svm
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_svm,sb)
                                        print "SVM END"
                if myth=='LikelihoodPCA':
                        for vari in Vb:
                                for c_likelipca in C_LikelihoodPCA:
                                        print "Cut :", c_likelipca
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_likelipca,sb)
                                        print "LikelihoodPCA END"
                if myth=='PDEFOAM':
                        for vari in Vb:
                                for c_pdefoam in C_PDEFOAM:
                                        print "Cut :", c_pdefoam
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_pdefoam,sb)
                                        print "PDEFOAM END"
                if myth=='MLPBNN':
                        for vari in Vb:
                                for c_mlpbnn in C_MLPBNN:
                                        print "Cut :", c_mlpbnn
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_mlpbnn,sb)
                                        print "MLPBNN END"
                if myth=='FDA_GA':
                        for vari in Vb:
                                for c_mlpbnn in C_FDA_GA:
                                        print "Cut :", c_fdaga
                                        print "myth:", myth
                                        from ROOT import ReadTMVA
                                        ReadTMVA(vari,myth,c_fdaga,sb)
                                        print "FDA_GA END"
