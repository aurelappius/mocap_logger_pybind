import statistics
import csv
import os
import math
import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

plotflag = True
plt.ion()
proj_plt = plt.subplot(2, 2, 1, projection="3d")
xy_plt = plt.subplot(2, 2, 3)
x_plt = plt.subplot(6, 2, 2)
y_plt = plt.subplot(6, 2, 4)
z_plt = plt.subplot(6, 2, 6)
ro_plt = plt.subplot(6, 2, 8)
pi_plt = plt.subplot(6, 2, 10)
ya_plt = plt.subplot(6, 2, 12)

header_list = ["Frame", "x", "y", "z", "roll", "pitch", "yaw"]  # new format
N=0

def on_press(event):
	if event.key == 'x':
		plotflag=False
		print("false")
	if event.key == 'y':
		plotflag=True
		print("True")

while(plotflag):
	DATA = pd.read_csv("log/temp.csv",usecols=header_list,skiprows=N,names=header_list).to_numpy()
	proj_plt.scatter(DATA[:,1],DATA[:,2],DATA[:,3], marker="o", s=1, c="red")
	xy_plt.scatter(DATA[:,1],DATA[:,2], marker="o", s=1, c="red")
	x_plt.scatter(DATA[:,0],DATA[:,1], marker="o", s=1, c="red")
	y_plt.scatter(DATA[:,0],DATA[:,2], marker="o", s=1, c="red")
	z_plt.scatter(DATA[:,0],DATA[:,2], marker="o", s=1, c="red")
	ro_plt.scatter(DATA[:,0],DATA[:,4], marker="o", s=1, c="red")
	pi_plt.scatter(DATA[:,0],DATA[:,5], marker="o", s=1, c="red")
	ya_plt.scatter(DATA[:,0],DATA[:,6], marker="o", s=1, c="red")
	N+=DATA.shape[0]
	plt.pause(0.01)
	plt.show()
 	

	#plt.draw()
	#np.append(DATA,[[t,x,y,z,ro,pi,ya]])
	# x_plt.set_xlabel("time [s]")
	# x_plt.set_ylabel("X [mm]")
	
	# y_plt.set_xlabel("time [s]")
	# y_plt.set_ylabel("Y [mm]")
	
	# z_plt.set_xlabel("time [s]")
	# z_plt.set_ylabel("Z [mm]")
	
	# ro_plt.set_xlabel("time [s]")
	# ro_plt.set_ylabel("roll [deg]")
	
	# pi_plt.set_xlabel("time [s]")
	# pi_plt.set_ylabel("pitch [deg]")
	
	# ya_plt.set_xlabel("time [s]")
	# ya_plt.set_ylabel("yaw [deg]")

# def show_plot():
# 	proj_plt.scatter(x,y,z, marker="o", s=1, c="red")
# 	
