#!/bin/sh
len=$(expr $(cat config.txt | wc -l) + 2)
echo "#define backup_config_txt_len $len"
echo "char backupcfgtxt[backup_config_txt_len][255] = { \"# Do not edit. Version 0.0.1. This is a backup config that will be overwritten by fss. The real config file must be named config.txt.\","
while read line 
do
  lineescape=$(echo "$line" | sed -e 's/\"/\\\"/g')
  echo "\"$lineescape\","
done < config.txt
echo "\"\" };"
