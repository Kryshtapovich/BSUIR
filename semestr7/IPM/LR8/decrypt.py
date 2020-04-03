from PIL import Image
from re import findall

def stega_decrypt():
	a = []
	keys = []
	img = Image.open('./newimage.png')
	pix = img.load()
	f = open('keys.txt','r')
	y = str([line.strip() for line in f])

	for i in range(len(findall(r'\((\d+)\,',y))):
		keys.append((int(findall(r'\((\d+)\,',y)[i]),int(findall(r'\,\s(\d+)\)',y)[i])))
	for key in keys:
		a.append(pix[tuple(key)][0])
	return ''.join([chr(elem) for elem in a])


if __name__ == '__main__':
	print("you message: ", stega_decrypt())