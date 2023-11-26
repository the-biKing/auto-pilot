# -*- coding: utf-8 -*-
"""
Created on Sun Nov 26 12:16:02 2023

@author: Josh
"""

from PIL import Image
import os

rightPicNumber=6
straightPicNumber=8

# Open the image
input_dir = 'imageForTraining/right/'
output_dir = 'txtForTraining/right/'

# Process each image from 1.png to 8.png
for i in range(1, rightPicNumber+1):
    # Open the image
    img = Image.open(os.path.join(input_dir, f'{i}.png'))

    # Convert the image to grayscale
    img = img.convert('L')

    # Get the pixel values as a list
    pixel_values = list(img.getdata())

    # Reshape the list into a 128x128 matrix
    pixel_matrix = [pixel_values[j:j + 128] for j in range(0, len(pixel_values), 128)]

    # Map pixel values to 0 or 1 directly (black: 0, white: 1)
    bw_matrix = [[1 if pixel >= 150 else 0 for pixel in row] for row in pixel_matrix]

    # Create a text file for each image
    with open(os.path.join(output_dir, f'{i}.txt'), 'w') as file:
        # Write the matrix dimensions (128x128)
        file.write("128 128\n")

        # Write the matrix content to the file
        for row in bw_matrix:
            file.write(' '.join(map(str, row)) + '\n')
            
input_dir = 'imageForTraining/straight/'
output_dir = 'txtForTraining/straight/'

# Process each image from 1.png to 8.png
for i in range(1, straightPicNumber+1):
    # Open the image
    img = Image.open(os.path.join(input_dir, f'{i}.png'))

    # Convert the image to grayscale
    img = img.convert('L')

    # Get the pixel values as a list
    pixel_values = list(img.getdata())

    # Reshape the list into a 128x128 matrix
    pixel_matrix = [pixel_values[j:j + 128] for j in range(0, len(pixel_values), 128)]

    # Map pixel values to 0 or 1 directly (black: 0, white: 1)
    bw_matrix = [[1 if pixel >= 150 else 0 for pixel in row] for row in pixel_matrix]

    # Create a text file for each image
    with open(os.path.join(output_dir, f'{i}.txt'), 'w') as file:
        # Write the matrix dimensions (128x128)
        file.write("128 128\n")

        # Write the matrix content to the file
        for row in bw_matrix:
            file.write(' '.join(map(str, row)) + '\n')