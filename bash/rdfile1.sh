#read one file line by line
for line in $(cat test1.txt);
    do echo $line ;
done;
#while read split line by space
while read line 
do 
    for word in $line 
    do  echo $word 
    done;
done <test1.txt

#string split or substring 
input=type=abcdefg
echo $input;
#get abcdefg
echo $input | cut -d'=' -f 2
echo $input | cut -d'=' -f 2


#${variable:startindex:len}
export str="123456789"
output=${str:3:3}
echo $output

#${varible##*string} 从左向右截取最后一个string后的字符串
#${varible#*string}  从左向右截取第一个string后的字符串
#${varible%%string*} 从右向左截取最后一个string后的字符串
#${varible%string*}  从右向左截取第一个string后的字符串

#常用保留变量：
$HOME：当前用户的根目录路径
$PATH：PATH环境变量
$PWD：当前工作路径
$0,$1,$2,…：第0个参数（shell脚本自身），第1个参数……
$RANDOM：1-65536之间的整数

#大小写转换
HI=HellO
 
echo "$HI" # HellO
echo ${HI^} # HellO
echo ${HI^^} # HELLO
echo ${HI,} # hellO
echo ${HI,,} # hello
echo ${HI~} # hellO
echo ${HI~~} #hELLo
^大写，,小写， ~大小写切换
重复一次只修改首字母，重复两次则应用于所有字母
#字符串的替换
${file/dir/path}：将第一个 dir 提换为 path：/path1/dir2/dir3/my.file.txt
${file//dir/path}：将全部 dir 提换为 path：/path1/path2/path3/my.file.txt
 
ref:http://my.oschina.net/leejun2005/blog/368777