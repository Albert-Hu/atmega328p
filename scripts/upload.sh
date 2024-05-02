#!/usr/bin/env bash

# Default values
port=""
file=""
use_docker=false

# Parse arguments
while [[ $# -gt 0 ]]; do
  case "$1" in
    -p|--port)
      port="$2"
      shift 2
      ;;
    -f|--file)
      file="$2"
      shift 2
      ;;
    -d|--docker)
      use_docker=true
      shift
      ;;
    *)
      echo "Unknown option: $1"
      exit 1
      ;;
  esac
done

# Check if the serial port and file are set
if [[ -z "$port" || -z "$file" ]]; then
  echo "Usage: $0 -p <port> -f <file> [-d]"
  exit 1
fi

# Check if the serial port exists
if [[ ! -e "$port" ]]; then
  echo "Serial port $port does not exist"
  exit 1
fi

# Check if the file exists and is a hex file
if [[ ! -f "$file" || "${file##*.}" != "hex" ]]; then
  echo "File $file does not exist or is not a hex file"
  exit 1
fi

# Get the absolute path of the file
file=$(realpath "$file")

# Check if the user wants to use Docker
if [[ "$use_docker" == true ]]; then
  docker run --rm -it --device=$port -v $file:/tmp/file.hex avr-env /bin/bash -c "avrdude -v -V -p atmega328p -c arduino -P $port -b57600 -D -U flash:w:/tmp/file.hex:i"
else
  avrdude -v -V -p atmega328p -c arduino -P $port -b57600 -D -U flash:w:$file:i
fi
