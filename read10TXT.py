#!/usr/local/bin/python
# -*- coding: utf-8 -*-
from math import *
from glob import glob
import os
import sys
#import readline 
for filename in glob("month10.txt"):
                os.remove(filename)
text_file=open('Month10.txt','r')
#satır satır okumayı readline ile yapıyor
while 1: 
	line=text_file.readline()
	#alttaki komutla dosya sonunda işlem bitiyor
	if not line: break
	line=line.replace("                     ","")
        line=line.replace("  "," ")
	line=line.replace("     ","")
        line=line.replace("   ","")
        line=line.replace("                              ","")
        line=line.replace("      ","")
        line=line.replace("           ","")
        line=line.replace("     ","")
        line=line.replace("  ","")
	line=line.replace(" ","")
	line=line.replace("/2013","/2013 ")
	line=line.replace("/2012","/2012 ")             
	line=line.replace("/2011","/2011 ")
	line=line.replace(":"," ")
	line=line.replace("HKG","11111")
	line=line.replace("-","")
	line=line.replace("ngw Loa","ngw-Loa")
	line=line.replace("ngw oLo","ngw-oLo")
        line=line.replace(",10/"," 10 ")
        line=line.replace("/2012"," 2012")
	line=line.replace('","'," ")
	line=line.replace(',"'," ")
	line=line.replace('",'," ")
	line=line.replace('"\t',"\t")
	line=line.replace('"\r',"\r")
        line=line.replace('"\n',"\n")
        CountSp=line.count(" ")
        word=line.split(" ")
	line=line.replace("D3 D","D3D")
        line=line.replace("S2 T","S2T")
	line=line.replace("  "," 11111 ")
	line=line.replace("R D","RD")
	line=line.replace('" ','')
	line=line.replace("\t","")
	line=line.replace("S4 ","S4")
	line=line.replace(" HK ","2222")
        line=line.replace("Y4 M","Y4M")
        line=line.replace("G2 O","G2O")
        line=line.replace("L5 G","L5G")
        line=line.replace("S I","SI")
        line=line.replace("S4 G","S4G")
#	print word
#	print CountSp
#	print word
	if CountSp == 9:
		line=line.replace("\n","")
        with open("month10.txt","a+") as f:
                f.writelines(line)
"""	if word[8].isdigit()==False:
		print word[8]
"""			
#	if word[6] or word[7]
"""
#	print word	
#	print CountSp
#	print line
        if CountSp == 20:
#		print "19un icinde"
#		print line
		del line
#                line=line.replace(".","")
#                line=line.replace("\r","")
#                line=line.replace("  "," ")
                continue
	elif CountSp > 20:
#		print "else icinde"
#		print line
		line=line.replace(line[-4:],"")
	        line=line.join("\r\n")
#		print line
#		line=line.replace("\r","")
                line=line.replace("  "," ")
		line=line.replace("0 1\r\n","0\n")
		line=line.replace("0 2\r\n","0\n")
		line=line.replace("0 3\r\n","0\n")
	        line=line.replace("0 4\r\n","0\n")
	        line=line.replace("0 5\r\n","0\n")
	        line=line.replace("0 6\r\n","0\n")
	        line=line.replace("0 7\r\n","0\n")
	        line=line.replace("0 8\r\n","0\n")
	        line=line.replace("0 9\r\n","0\n")
		line=line.replace("\r","")
                line=line.replace(" 0 00 \n"," 0 00 00\n")
		line=line.replace(" 0 00\n"," 0 00 00\n")
#		print word
#		print line
"""
