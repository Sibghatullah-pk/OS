#!/bin/bash

echo "Enter the units consumed:"
read unit

echo "Enter the type (regular or irregular):"
read type


if [ "$unit" -lt 50 ]; then
    bill=$((unit * 20))
elif [ "$unit" -le 100 ]; then
    bill=$((unit * 40))
else
    bill=$((unit * 80))
fi


if [ "$type" == "regular" ]; then
    final_bill=$bill
    echo "Regular customer bill: $final_bill"
elif [ "$type" == "irregular" ]; then
    tax=$(echo "$bill * 0.80" | bc )
    final_bill=$(echo "$bill + $tax" | bc )
    echo "Irregular customer base bill: $bill"
    echo "Tax (80%): $tax"
    echo "Total bill with tax: $final_bill"
else
    echo "Error: Type must be either 'regular' or 'irregular'"
    exit 1
fi
