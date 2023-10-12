#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <pid>"
  exit 1
fi

target_pid=$1

if kill -s QUIT "$target_pid" > /dev/null 2>&1; then
  exit 0
else
  echo "Failed to send SIGQUIT to process with PID $target_pid"
  exit 1
fi
