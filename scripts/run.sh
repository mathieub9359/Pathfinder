#!/bin/bash

PATHFINDER="../build/src/app/pathfinder"

if [ -e "$PATHFINDER" ]; then
    # Check if the executable exists
    $PATHFINDER
else
    echo "Error: $PATHFINDER does not exist. Build the executable before running this script (build.sh)."
fi
