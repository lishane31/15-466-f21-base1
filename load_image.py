import sys

import numpy as np
from PIL import Image

#Taken from UCSD's CSE 8A Image library from when I was an undergrad there
def load_img(filename):
    img = Image.open(filename)
    pil_img = img.convert('RGB')
    arr = np.array(pil_img.getdata(), dtype=np.uint8).reshape(pil_img.height, pil_img
.width, 3)
    img = [ [ (int(p[0]),int(p[1]),int(p[2])) for p in row ] for row in arr ]
    return img

# clear, black, white, pink
# red, green, blue, black

images_0 = ['glitched_tile', 'spike', 'brick']
images_1 = ['friend', 'enemy', 'player']
path = "./tile/"
output = "./tile_txt/"

for file in images_0:
	image = load_img(path + file + '.png')

	with open(output + file + '.txt', 'w') as f:
		sys.stdout = f
		print("0")

		#rev row order
		for row in range(7, -1, -1):
			for col in range(0, 8, 1):
				pix = image[row][col]
				if pix == (255, 255, 255):
					print("0 0")
				elif pix == (0, 0, 0):
					print("0 1")
				elif pix == (255, 0, 255):
					print("1 1")
				else:
					print(pix)

for file in images_1:
	image = load_img(path + file + '.png')

	with open(output + file + '.txt', 'w') as f:
		sys.stdout = f
		print("1")

		#rev row order
		for row in range(7, -1, -1):
			for col in range(0, 8, 1):
				pix = image[row][col]
				if pix == (255, 0, 0):
					print("0 0")
				elif pix == (0, 255, 0):
					print("0 1")
				elif pix == (0, 0, 255):
					print("1 0")
				elif pix == (0, 0, 0):
					print("1 1")
				else:
					print(pix)

