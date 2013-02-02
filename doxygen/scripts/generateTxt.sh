for f in *.xml ; do xsltproc.exe ../extr.xslt  $f > $f.txt ; done
for f in namespace_quant_lib*.xml ; do xsltproc.exe extr.xslt  $f > $f.txt ; done

for f in *.xml.txt ; do n=`head -1 $f|tr '<:>' '[_]' | tr -d ' '` ; cp $f $n.txt ; done
