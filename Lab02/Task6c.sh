# Kyle Tranfaglia - Cosc350 - Lab02 - Last updated: 09/18/23
#!/bin/bash

makeRightArrow() {
        local outerStar=`expr $1 / 2 + 1`
        local midpoint=$outerStar
        local stars="*"
        for i in $(seq 1 $1);
        do
		if [ $i -eq $midpoint ];
                then 
                        for j in $(seq 1 $2);
                        do
                                printf "*"
                        done
			printf "$stars\n"
		else
			printf "%*s\n" `expr ${#stars} + $2` "$stars"
		fi
               	if [ $i -lt  $midpoint ];
               	then
			outerStar=`expr $outerStar + 2`
                        stars=$stars"**"
		else
			outerStar=`expr $outerStar -  2`
                       	length=${#stars}
                      	stars="${stars:0:`expr $length - 2`}"
               	fi
        done
}

printf "Enter a size for the arrow base (must be an odd number greater than 3): "
read size

while [ "$size" -le 3  -o `expr "$size" % 2` != 1 ];
do
        printf "This is not a valid input. Enter an odd number greater than 3!: "
        read size
done

printf "Enter a size for the arrow tail: "
read tailLength

while [ "$tailLength" -le 0 ];
do
        printf "Why would you enter that? Enter a tail greater than 0!: "
        read tailLength
done

makeRightArrow $size $tailLength
exit 0
