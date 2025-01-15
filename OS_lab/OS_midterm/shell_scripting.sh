
# 1.

#!/bin/sh
echo "Current date and time $(date)"
echo "Username : $(whoami)"
echo "current directory : $(pwd)"




# 2

#!/bin/sh

if["$#" -ne 2]; then
    echo "Error: Two numbers are required."
    echo "Usage : $0 num1 num2"
fi

num1 = $1
num2 = $2

sum = $((num1 + num2))
echo "The sum of $num1 and $num2 is : $sum"



# 3

#!/bin/sh

if["$#" -ne 3]; then
    echo "Error : You must supply exactly 3 numbers as arguments."
    echo "Usage : $0 num1 num2 num3"
    exit 1
fi

num1 = $1
num2 = $2
num3 = $3

if["$num1" -ge "$num2"] && ["$num1" -ge "$num3"]; then
    largest = $num1
elif ["$num2" -ge "$num1"] && ["$num2" -ge "$num3"]; then
    larget = $num2
else
    largest = $num3
fi

echo "Largest number is : $largest"



# 4 - Printing 5,4,3,2,1 using While loop

#!/bin/sh

number = 5

while["$number" -ge 1]
do
    echo "$number"
    number = $((number - 1))
done


# 5

#!/bin/sh

if["$#" -ne 3]; then
    echo "Usage : $0 number1 operator number2"
    echo "Operators: + for addition , - for subtraction, x for multiplication, / for division"
    exit 1
fi

num1 = $1
operator = $2
num2 = $3

case "$operator" in
    +)
    result = $((num1 + num2))
    ;;

    -)

    result = $((num1 - num2))
    ;;

    x)

    result = $((num1 * num2))
    ;;

    /)

    if["$num2" -ne 0]; then
        result = $((num1 / num2))
    else
        echo "Error: Division by Zero not allowed."
        exit 1
    fi
    ;;

    *)
    echo "Error : Invalid operator. Use +,-,x,/."
    exit 1
    ;;
esac

echo "The result of $num1 $operator $num2 is : $result"







