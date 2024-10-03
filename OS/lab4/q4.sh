files=$1
option=$2

case $option in 
	-linecount)
	echo "Line Count:$(wc -l $files)"
	;;
	-wordcount
	echo "Word Count: $(wc -w $files)"
	;;
	-charactercount
	echo "Character Count: $(wc -m $files)"
	;;
esac


