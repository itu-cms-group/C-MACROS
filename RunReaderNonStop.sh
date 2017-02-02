#!/bin/bash

export path=/media/cakir/cakir_data/snowmass2/
export Ntuplerpath=/home/cakir/NtuplerAnalyzer
export macropath=/home/cakir/Desktop/PlottingTool

ListOfScenarios=(140PU_ 50PU_ NoPU_) 
ListOfSamples=(DiBoson BosonJets TopJets TTbar)

cd $Ntuplerpath
for i in "${ListOfScenarios[@]}"; do 
	for k in "${ListOfSamples[@]}"; do
		python /home/cakir/NtuplerAnalyzer/runReader.py "DeepSingle" $i$k
	done
done
