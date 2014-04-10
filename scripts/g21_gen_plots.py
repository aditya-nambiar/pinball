import matplotlib.pyplot as plt
import numpy as ny
import subprocess
import random
import re

subprocess.call(['mkdir','-p','plots'])
iter=1050
reruns=49
ran=4

file=open('data/lab09_g21_data.csv', 'r')
all_data=[ [],[],[],[],[],[],[] ]

for line in file:
	inp=re.findall(r'[0-9.]+', line)
	#print(line)
	all_data[0].append(int(inp[0]))     #iteration
	all_data[1].append(int(inp[1]))     #rerun
	all_data[2].append(float(inp[2]))   #steptime
	all_data[3].append(float(inp[3]))	#collision time
	all_data[4].append(float(inp[4]))	#velocity time
	all_data[5].append(float(inp[5]))	#position time
	all_data[6].append(float(inp[6]))	#loop time

aver=[ [],[],[],[],[],[],[] ] ## average val for step, col,vel,pos,loop,sum
stddev=[]
for i in range(0,iter):
	aver[0].append(i+1)
	for j in range(2,7):
		temparr=all_data[j][i*reruns:(i+1)*reruns]
		aver[j-1].append(ny.mean(temparr))
	aver[6].append(aver[2][i]+aver[3][i]+aver[4][i])
	tempar=all_data[j][i*reruns:(i+1)*reruns]
	stddev.append(ny.std(tempar))
	
grap=plt.figure()
plot1 = grap.add_subplot(111)
plot1.set_title('Step and Loop time vs Iterations')    
plot1.set_xlabel('Number of Iterations')
plot1.set_ylabel('Averaged time over iterations in ms')
plot1.bar(aver[0], aver[1],facecolor='b',edgecolor='white',label='Average Step Time')
plot1.plot(aver[0],aver[5],label='Average Total Loop Time')
plot1.legend(loc=2)
grap.savefig('plots/g21_plot01.png')

grap = plt.figure()
plot2 = grap.add_subplot(111)
plot2.set_title('Time vs Number of iterations')    
plot2.set_xlabel('Number of Iterations')
plot2.set_ylabel('Averaged time over iterations (ms)')
plot2.plot(aver[0], aver[1],color='r',label='Average Step Time')
plot2.plot(aver[0], aver[2],color='b',label='Average Collision Time')
plot2.plot(aver[0], aver[3],color='g',label='Average Velocity update Time')
plot2.plot(aver[0], aver[4],color='c',label='Average Position update Time')
plot2.plot(aver[0], aver[6],color='m',label='Sum of Collision, Velocity and Position update Time')
plot2.legend()
grap.savefig('plots/g21_plot02.png')	

grap = plt.figure()
plot3 = grap.add_subplot(111)
plot3.set_title('Step Time vs Number of iterations')    
plot3.set_xlabel('Number of Iterations')
plot3.set_ylabel('Averaged time over iterations (ms)')
plot3.errorbar(aver[0], aver[1],stddev,color='r',ecolor='g',label='Error Bars')
plot3.plot(aver[0], aver[1],color='b',label='Average Step Time')
plot3.legend()
grap.savefig('plots/g21_plot03.png')

tempar=all_data[2][78*reruns:79*reruns]
freq79=ny.histogram(tempar,15)#15 bins
freq79_cum=ny.cumsum(freq79[0])

fig = plt.figure()
plot4 = fig.add_subplot(111)
plot4.set_title('Step Time Frequency Plot')    
plot4.set_xlabel('Step Time (ms)')
plot4.set_ylabel('Frequency')
plot4.hist(tempar,15,color='g',label='Step Time Frequency')
plot4.plot(freq79[1][1:],freq79_cum,color='b',label='Cumulative Step Time Frequency')
plot4.legend(loc=2)
fig.savefig('plots/g21_plot04.png')

randol=list()

for it in range(0,iter):
	temperlist=random.sample(all_data[2][it*reruns:(it+1)*reruns],ran)
	randol.append(ny.mean(temperlist))

mr,cr=ny.polyfit(range(1,iter+1),randol,1)
m,c=ny.polyfit(range(1,iter+1),aver[1],1)
randl=[mr+cr,mr*iter+cr]
norml=[m+c,m*iter+c]
#print(m,c,mr,cr)
grap = plt.figure()
plot5 = grap.add_subplot(111)
plot5.set_title('Step time vs Number of iterations')    
plot5.set_xlabel('Number of Iterations')
plot5.set_ylabel('Averaged time over iterations (ms)')
plot5.scatter(aver[0],aver[1],color='g',label='Average Step time for all reruns of iterations')
plot5.scatter(aver[0],randol,color='r',label='Average Step time for random reruns of iterations')
plot5.plot([1,iter],norml,color='m',label='Model fit for all reruns')
plot5.plot([1,iter],randl,color='b',label='Model fit for random reruns')
plot5.legend(loc=2)
#plt.show()
grap.savefig('plots/g21_plot05.png')			

