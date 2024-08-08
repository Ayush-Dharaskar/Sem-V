read extern
read folder
mkdir -p $folder
files=`find . -maxdepth 1 -type f -name "*$extern"`
for i in $files
do
cp $i $folder
done