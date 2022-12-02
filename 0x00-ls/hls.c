#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>


int word_check(const char *str){
	int i = 0;
	while (str[i] != '\0'){
		if (str[i] == '.')
			i++;
		else
			return 1;
	}
	return 0;
}

char* _strcat(const char *fst,const char *scd){
	int i = 0, j = 0, ctr;
	char *buf;

	while (fst[i] != '\0') i++;
	while (scd[j] != '\0') j++;
	j += i;
	buf = (char*)malloc((j + 2)*sizeof(char));
	for(ctr = 0; ctr <= j; ctr++)
	{
		if (ctr == i) buf[ctr] = '/';
		else if (ctr > i) buf[ctr] = scd[ctr - i - 1];
		else buf[ctr] = fst[ctr];
	}
	buf[ctr] = '\0';
	return buf;
}


void _ls(const char *dir,int op_a,int op_l)
{
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	struct stat fileStat;
	char *filename;
	struct passwd *username;
	struct passwd *groupname;

	if (!dh)
	{
		if (errno = ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL)
	{
		//If hidden files are found we continue
		//!op_a => When op_a is 0
		if (!op_a && d->d_name[0] == '.')
			continue;
		else if(op_a == 2 && !word_check(d->d_name))
			continue;
		else if(op_l)
		{
			filename = _strcat(dir, d->d_name);
			if (!lstat(filename, &fileStat))
		        {
				printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
				printf(" %ld", fileStat.st_nlink);
				username = getpwuid(fileStat.st_uid);
				groupname = getpwuid(fileStat.st_gid);
				printf(" %s %s", username->pw_name, groupname->pw_name);
				printf(" %ld ", fileStat.st_size);
			} else
			{
				perror("Error in stat");
			}
		}
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}


int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		_ls(".",0,0);
	}
	else if (argc >= 2)
	{
		if (argv[1][0] == '-')
		{
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'A') op_a = 2;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			if (argc == 2)
				_ls(".",op_a,op_l);
			else
				_ls(argv[2],op_a,op_l);
		}
		else
			_ls(argv[1],0,0);
	}
	return 0;
}
