filename="$1"
flag="$2"

if [ "$flag" = 0 ]; then
  # 读取文件内容
  content=$(cat "$filename")
  echo "文件内容：$content"
elif [ "$flag" = 1 ]; then
  # 获取学号后3位
  student_id="21069100223"
  last_three_digits="${student_id: -3}"

  # 写入文件
  echo "$last_three_digits    MYFILE" > "$filename"
  echo "已成功写入文件：$filename"
else
  echo "无效的标志位!请使用0(读)或1(写)作为第二个参数。"
fi
