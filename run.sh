#!/bin/sh
rm ./logs/logs.txt && echo "logs deleted"
./create_db
touch ./logs/logs.txt && echo "logs created"
./server