echo "enter directory:"
read dir

echo "Enter Pattern:"
read pattern

echo "Files present:"
find "$dir" -type f -name "*$pattern*" -exec basename {} \;