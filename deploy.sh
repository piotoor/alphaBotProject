#!/bin/sh

TARGET_ADDRESS="pi@"$1

TARGET_BASE_DIR="/home/pi/"

TARGET_BIN_DIR=$TARGET_BASE_DIR"bins"

current_date=$(date +%Y%m%d_%H%M)

BACKUP_DIR_NAME="bins_bak_"$current_date

#backup binaries
echo "Backup"
ssh $TARGET_ADDRESS mv $TARGET_BIN_DIR" "$TARGET_BASE_DIR$BACKUP_DIR_NAME
#########

#copy binaries from local to target
echo "Copy to target"
ssh $TARGET_ADDRESS "mkdir "$TARGET_BIN_DIR
scp ./* $TARGET_ADDRESS":"$TARGET_BIN_DIR
#