echo "Bascis:"
read basic

echo "TA:"
read ta

GS=`echo "scale=2; $ta + $basic * 1.1" | bc`
echo "GS: $GS"