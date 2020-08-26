#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void isFile(char *name);

void read_dir(char *dir) //处理目录
{
	DIR *dp;
	char path[256];
	struct dirent *sdp;
	dp = opendir(dir);//打开
	if(dp == NULL)
		{
			perror("opendir fail\n");
			return ;
		}
	while((sdp = readdir(dp)) != NULL)//读取
		{
			if(strcmp(sdp->d_name, ".") == 0 ||strcmp(sdp->d_name, "..") ==0)
				{
					continue;
				}
				//拼接路径
			sprintf(path, "%s/%s", dir,sdp->d_name);
			isFile(path);
		}
	closedir(dp);
}

void isFile(char *name) //判断文件类型
{
	int ret = 0;
	struct stat sb;

	//获取文件属性
	ret = lstat(name,&sb);
	if(ret == -1)
		{
			perror("stat error");
			return ;
		}
	//是目录文件
	if(S_ISDIR(sb.st_mode))
		{
			read_dir(name);
		}
	//是普通文件
	printf("%10s\t\t%ld\n",name,sb.st_size);
	return;
}
int main(int argc, char *argv[])
{
	//判断命令行参数
	if(argc == 1)
		{
			isFile(".");
		}
	else
		{
			isFile(argv[1]);
		}
	return 0;
}
