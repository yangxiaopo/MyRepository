#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>

#define MAXLINE 1024

template<class T> void read_config(T& m,char *name)
{
	std::ifstream input(name);
	if(input.is_open())
	{
		std::string line;
		while(std::getline(input,line))
		{
			if(line == "" || line[0] == '#'){
				continue;
			}

			size_t mask_index = line.find_first_of('-');
			std::string mask(line,0,mask_index);

			size_t num_index = line.find_last_of('-');
			std::string num(line,num_index+1);
			auto x=stoul(num);

			m[mask] = x;
		}
		input.close();
	}
}

template<class T> void write_config(T& c,char *name,bool sorted)
{
	std::ofstream output(name,std::ios::out | std::ios::trunc | std::ios::binary);

	if(output.is_open())
	{
		typename T::const_iterator p;
		unsigned long accumulator = 0;
		unsigned int length = 0;
		unsigned int index = 0;
//		std::ofstream output_spec("specification",std::ios::out | std::ios::binary | std::ios::app);

//		if(output_spec.is_open())
//		{
			for(p = c.cbegin();p != c.cend();++p)
			{
				if(!sorted)
				{
					if(length != (p->first).length())
					{
						if(length != 0)
						{
//							output_spec<<"#长度为"<<length/2<<"的password个数为"<<accumulator<<";mask个数为"<<++index<<"\n\n";
							output<<"#长度为"<<length/2<<"的password个数为"<<accumulator<<";mask个数为"<<++index<<"\n\n";
						}
						length = (p->first).length();
						accumulator = p->second;
						index = 0;
					}else{
						accumulator += p->second;
						index++;
					}
				}
				output<<p->first<<"----------"<<p->second<<'\n';
			}
			if(!sorted)
			{
//				output_spec<<"#长度为"<<length/2<<"的password个数为"<<accumulator<<";mask个数为"<<++index<<"\n\n";
				output<<"#长度为"<<length/2<<"的password个数为"<<accumulator<<";mask个数为"<<++index<<"\n\n";
			}
//			output_spec.close();
//		}
		output.close();
	}
}

class cmp
{
public:
	bool operator()(const std::string& a,const std::string& b)
	{
		if(a.length() < b.length())
		{
			return true;
		}else if(a.length() == b.length())
		{
			return a < b;
		}else
		{
			return false;
		}
	}
};

void calculate(char *filename,bool read_or_not,char *fnm)
{
	std::map<std::string,unsigned long,cmp> m;

	if(read_or_not)
	{
		read_config(m,fnm);
	}

	std::ifstream input(filename);
	if(input.is_open())
	{
		std::string line;
		std::string::const_iterator p;
		while(std::getline(input,line))
		{
			std::string mask="";
			for(p=line.cbegin();p != line.cend();p++)
			{
				if ('0' <= *p&&*p <= '9')
					mask += "?d";
				else if ('a' <= *p&&*p <= 'z')
					mask += "?l";
				else if ('A' <= *p&&*p <= 'Z')
					mask += "?u";
				else
					mask += "?s";
			}
			if(p == line.cend())
				m[mask]++;
		}
		input.close();
	}

	write_config(m,fnm,false);
}

void sort(char *before,char *after)
{
	std::map<std::string,unsigned long> m;
	read_config(m,before);
	std::vector<std::pair<std::string,unsigned long>> v(m.begin(),m.end());
	std::sort(v.begin(),
			  v.end(),
			  [](const std::pair<std::string,unsigned long>& a,const std::pair<std::string,unsigned long>& b)
			  {
				  return a.second != b.second?  a.second > b.second : a.first > b.first;
			  });
	write_config(v,after,true);
}

/************************************************************************/

int dirwalk(char *path,void (*fcn)(char*,bool,char*))
{
	WIN32_FIND_DATA findData;
	HANDLE h = INVALID_HANDLE_VALUE;
	char name[MAXLINE] = {0};
	char subname[MAXLINE] = {0};
	DWORDLONG dwHighBase = MAXDWORD;  
	dwHighBase += 1;  

	sprintf(name,"%s\\*",path);
	h = FindFirstFile(name, &findData);
	if(h == INVALID_HANDLE_VALUE) {
		FindClose(h);
		return -1;
	}

	do{
		if(strcmp(findData.cFileName,".") == 0 || strcmp(findData.cFileName,"..") == 0)
			continue;

		sprintf(subname,"%s\\%s",path,findData.cFileName);
		if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
			dirwalk(subname,fcn);
		else
			fcn(subname,true,"result.txt");
	}while(FindNextFile(h, &findData) != 0);

	return 0;
}

/***********************************************************************/

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		std::cerr<<"expect 1 arg"<<'\n';
		return -1;
	}
	dirwalk(argv[1],calculate);
	sort("result.txt","sort.txt");
}

//int main()
//{
//	std::ofstream output_spec("specification.txt",std::ios::out | std::ios::trunc | std::ios::binary);
//
//	if(output_spec.is_open())
//	{
//		output_spec<<"#长度为 E JUST BE OK! ";
//		output_spec.close();
//	}
//}