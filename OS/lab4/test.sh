#var='I am global'
#function showvar(){
#local var1='I am Local'
#echo $var
#}

#showvar
#echo $var1
#echo $var


#function add(){
#a=$2
#b=$1
#c=$(echo $a+$b|bc)
#echo $c
#}

#add 1 2


#echo "ENTER NUMBER"
#read -a inputArrayOfNumbers
#echo -n "Entered input is…"
#for i in ${inputArrayOfNumbers[@]} ; do
#echo -n $i " "
#done

#arr=("$@")

#for i in ${arr[@]} ; do
#echo $i " "
#done

myFunction() {
param1=("${!1}")
param2=("${!2}")
for i in ${param1[@]}; do
for j in ${param2[@]}; do
if [ "${i}" == "${j}" ]; then
echo ${i}
echo ${j}
fi
done
done
}
a=(1 2 3)
b=(1 2 qux)
myFunction a[@] b[@]
