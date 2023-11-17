# Kyle Tranfaglia - Cosc350 - Lab02 - Last updated: 09/18/23
#!/bin/bash

makeDiamond() {
	local outerStar=`expr $1 / 2 + 1`
	local midpoint=$outerStar
	local stars="*"
	for i in $(seq 1 $1);
	do
		printf "%*s\n" $outerStar "$stars"
		if [ $i -lt  $midpoint ];
		then
			let outerStar++
			stars=$stars"**"
		else
			length=${#stars}
			stars="${stars:0:`expr $length - 2`}"
			let outerStar--
		fi
	done
}

printf "Enter a size for the Diamond base (must be an odd number greater than 3): "
read size

while [ "$size" -le 3  -o `expr "$size" % 2` != 1 ];
do
	printf "This is not a valid input. Enter an odd number greater than 3!: "
	read size
done

makeDiamond $size
exit 0
