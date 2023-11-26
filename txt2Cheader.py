# -*- coding: utf-8 -*-
"""
Created on Sun Nov 26 12:41:56 2023

@author: Josh
"""
import os


folder_path = 'imageForTraining/right/'
# List all files in the folder
files = os.listdir(folder_path)
# Count the number of files
rightPicNumber = len(files)

folder_path = 'imageForTraining/straight/'
# List all files in the folder
files = os.listdir(folder_path)
# Count the number of files
straightPicNumber = len(files)

# Writing matrices into a C header file
with open("Rmatrix_data.h", "w") as file:
    file.write("#pragma once\n")
    file.write("#ifndef RMATRIX_DATA_H\n")
    file.write("#define RMATRIX_DATA_H\n\n")

    # Loop through each matrix file and write its content to the header file
    for i in range(1, rightPicNumber + 1):
        matrix_name = f"matrixR{i}"
        file.write(f"static int {matrix_name}[128][128] = {{\n")
        with open(f"txtForTraining/right/{i}.txt", "r") as txt_file:
            lines = txt_file.readlines()[1:]  # Skip the dimensions line
            for line in lines:
                values = line.strip().split()  # Split the values
                file.write(
                    "    {" + ", ".join(values) + "},\n"
                )  # Join values with commas
        file.write("};\n\n")

    file.write("#endif")

with open("Smatrix_data.h", "w") as file:
    file.write("#pragma once\n")
    file.write("#ifndef SMATRIX_DATA_H\n")
    file.write("#define SMATRIX_DATA_H\n\n")

    # Loop through each matrix file and write its content to the header file
    for i in range(1, straightPicNumber + 1):
        matrix_name = f"matrixS{i}"
        file.write(f"static int {matrix_name}[128][128] = {{\n")
        with open(f"txtForTraining/straight/{i}.txt", "r") as txt_file:
            lines = txt_file.readlines()[1:]  # Skip the dimensions line
            for line in lines:
                values = line.strip().split()  # Split the values
                file.write(
                    "    {" + ", ".join(values) + "},\n"
                )  # Join values with commas
        file.write("};\n\n")

    file.write("#endif")
