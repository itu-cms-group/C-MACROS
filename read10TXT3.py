#!/usr/local/bin/python
# -*- coding: utf-8 -*-
from math import *
from glob import glob
import os
import sys
#import readline 
for filename in glob("month10_v3.txt"):
                os.remove(filename)
text_file=open('month10_v2.txt','r')
#satır satır okumayı readline ile yapıyor
while 1: 
	line=text_file.readline()
	#alttaki komutla dosya sonunda işlem bitiyor
	if not line: break
        CountSp=line.count(" ")
        word=line.split(" ")
	ListAlpha=["A","B","C","D","E","F","G","H","G","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
#	print CountSp
	if CountSp==13:
#		print "if icinde"
#		print line
		line=line.replace(word[9]+" "+word[10],word[9]+""+word[10])
#		print line
#	if " " in word[9]:
#		print "if icinde"
#	for i in ListAlpha:
	#		print "for icind4eee"
	#		print i
#		for k in ListAlpha:
	#			print k
	#			print "2.dongude"
		#		print word[9]
		#		print word[9]
	#			print line
	elif CountSp==14:
#		print "elif icinde"
#		print line
		line=line.replace(word[9]+" "+word[10],word[9]+""+word[10])
#		print line
		word2=line.split(" ")
		CountSp2=line.count(" ")
#		print CountSp2
		if CountSp2==13:
			line=line.replace(word[10]+" "+word[11],word[10]+""+word[11])
#			print line
	with open("month10_v3.txt","a+") as f:
              f.writelines(line)
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
