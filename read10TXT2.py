#!/usr/local/bin/python
# -*- coding: utf-8 -*-
from math import *
from glob import glob
import os
import sys
#import readline 
for filename in glob("month10_v2.txt"):
                os.remove(filename)
text_file=open('month10.txt','r')
#satır satır okumayı readline ile yapıyor
while 1: 
	line=text_file.readline()
	#alttaki komutla dosya sonunda işlem bitiyor
	if not line: break
        CountSp=line.count(" ")
        word=line.split(" ")
#	print CountSp
#	print word[8]
       	try:
	  i = int(word[8])
	  with open("month10_v2.txt","a+") as f:
                f.writelines(line)
	except ValueError:
#	  print "not an integer\n"
	  word[9]=word[9].replace("N","22")
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
