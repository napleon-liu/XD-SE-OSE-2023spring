#!/bin/bash

# Set the filename and flag variables
filename="$1"
flag="$2"

# Generate the script content
script_content=$(cat <<'EOF'
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
EOF
)

# Write the script content to a file
script_filename="rw.sh"
echo "$script_content" > "$script_filename"
echo "Generated script: $script_filename"

# Make the generated script executable
chmod +x "$script_filename"

# Execute the generated script with the provided arguments
./"$script_filename" "$filename" "$flag"
