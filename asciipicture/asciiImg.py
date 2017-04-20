#!/usr/bin/env python
# -*- coding:utf-8 -*-

from PIL import Image
import argparse      

parser = argparse.ArgumentParser()
parser.add_argument('file') 
parser.add_argument('-o','--output',type=str,default="asciiImg.txt",help="give the name of asciiImg")
parser.add_argument('-W','--width',type=int,default=100,help="give the value of width")
parser.add_argument('-H','--height',type=int,default=100,help="give the value of height")
args = parser.parse_args()

img = args.file
width = args.width
height = args.height
output = args.output

def get_char(r,g,b,alpha=255):
	'''
	将256灰度映射到70个字符上
	'''
	ascii_char = list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
	if alpha == 0:
		return ' '
	gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b) #灰度公式
	unit = 256.0 / len(ascii_char)
	return ascii_char[int(gray/unit)]
	
def transform(img):
	txt = ""
	for i in range(height):
		for j in range(width):
			txt += get_char(*img.getpixel((j,i))) 
		txt += '\n'
	return txt

def save(txt):	
	with open(output,'w') as f:
		f.write(txt)
		
if __name__ == '__main__':
	im = Image.open(img).resize((width,height),Image.NEAREST) #Returns a resized copy of this image
	asciiImg = transform(im)
	save(asciiImg)
	
	
	
