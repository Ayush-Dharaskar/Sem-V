files=`find . -name *.txt`

for i in $files
do
mv $i ${i%.txt}.text
done
echo finished