# /usr/bin/python3
import re
fout=open("report.html",'w')
fin=open("cs296_report_21.tex",'r')
fout.write("""<!DOCTYPE html>

<html>

<head>
<title>Cs296 Project</title>
<style>
body{margin-right:10em; margin-left:10em;font-family: Palatino, "Palatino LT STD", "Palatino Linotype", "Book Antiqua", Georgia, serif;background-image:url('images/bg.jpg');background-size: 100% auto;;color:white;font-size:140%;}
h1{text-align:center;color:#0000FF;text-transform:capitalize;font-family: "BRUSH SCRIPT MT", sans-serif;text-decoration:underline;}
h2{color:#000000;text-transform:capitalize;}
h3{color:#000000;text-transform:capitalize;}
table,td
{
border:1px solid black;
}
table
{
width:200%
border-collapse:collapse;
}
.txt {font-size:24px;}
</style>
</head>
<body>
<div class="txt">""")


cont=0
line=fin.readline()
fulltext=""
while True:
	line=fin.readline()
	if(line.find("Introduction")!=-1):
		break
while True:
	fulltext=fulltext+line
	line=fin.readline()
	if(line.find("bibliographystyle{plain}")!=-1):
		break

fulltext = re.sub(r"(\\subsection\s*{)(.*)}",r'<h2>\2</h2>',fulltext)
fulltext = re.sub(r"(\\section\s*{)(.*)}",r'<h1>\2</h1>',fulltext)
fulltext = re.sub(r"(\\subsubsection\s*{)(.*)}",r'<h3>\2</h3>',fulltext)

ol_pattern = re.compile(r"(\\begin\s*{itemize})(.*?)\\end\s*{itemize}",re.DOTALL)
center_pattern = re.compile(r"(\\begin\s*{center})(.*?)\\end\s*{center}",re.DOTALL)
fulltext= re.sub(r"\\textsf{(.*?)}",r"<fontc>\1</fontc>",fulltext)
descrip_pattern=re.compile(r"(\\item {\\textbf{)(.*)}}(.*)")
descrip_pattern2=re.compile(r"\\textbf\s*{(.*?)}")

fulltext=descrip_pattern2.sub(r"<b>\1</b>",fulltext)
fulltext = ol_pattern.sub(r"<ul>\2</ul>",fulltext) 
fulltext = center_pattern.sub(r"<div align='center'>\2</div><br>",fulltext)
fulltext = re.sub(r"(\\item)(.*)",r"<li>\2</li>",fulltext)
fulltext= re.sub(r"\\\\","<br>",fulltext) 
fulltext = re.sub(r"(\\it\s*)(.*)",r'<br><i>\2</i>',fulltext)
fulltext = re.sub(r"\\hspace.*",r'',fulltext)
fulltext = re.sub(r"\\\&",r'&',fulltext)
fulltext = re.sub(r"\$",r'',fulltext)
fulltext= re.sub(r"\\includegraphics\[scale=[0-9.]*\]{(.*)}",r'<img src="../doc/\1.png">',fulltext)
#print(fulltext)
fout.write(fulltext)
fout.write("""
<h1>References</h1>
<ul>
<li>http://www.youtube.com/watch?feature=player_detailpage&v=z_NauMiAguw#t=202/</li>
<li>http://stackoverflow.com/
</li>
<li>https://www.iforce2d.net/b2dtut/
</li>
<li>http://www.box2d.org/manual.html/
</li>
<li>Mihir Kulkarni for helping in scripts</li>
<ul>
</div> 
</body>
</html>"""
)	
