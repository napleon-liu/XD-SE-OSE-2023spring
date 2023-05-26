#!/bin/bash
filename="$1"
flag="$2"

if [ "$flag" = "0" ]; then
  # Read file content
  content=$(cat "$filename")
  echo "文件内容：$content"
elif [ "$flag" = "1" ]; then
  # Get the last three digits of the student ID
  student_id="21069100223"
  last_three_digits="${student_id: -3}"

  # Write to the file
  echo "$last_three_digits    MYFILE" > "$filename"
  echo "已成功写入文件：$filename"
else
  echo "无效的标志位!请使用0(读)或1(写)作为第二个参数。"
fi
