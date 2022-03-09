#!/bin/sh
sleep 10
rm ./logs/logs.txt && echo "logs deleted"
./create_db
make cp_logs
touch ./logs/logs.txt && echo "logs created"
./server