echo "Enter file path:"
read path
if [ -d "$path" ]; then
	echo "$path is a directory"
elif [ -f "$path" ]; then
	echo "$path is a file"
else
	echo "$path is neither a file nor a directory"
fi