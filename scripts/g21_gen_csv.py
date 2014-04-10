import subprocess
import re
subprocess.call(['mkdir','-p','data'])
subprocess.call(['rm','-f','data/lab09_g21_data.csv'])
outf=open("data/lab09_g21_data.csv",'a')
for it in range(1,3000):
	for rerun in range (1,50):
		print(it)
		print(rerun)
		p=subprocess.Popen(["mybins/cs296_21_exelib",str(it)],stdout=subprocess.PIPE)
		out=p.communicate()[0]
		match=re.findall(r"[0-9.]+",str(out))
		match.insert(1,str(rerun))
		out_str=",".join(match)+"\n"
		outf.write(out_str)
