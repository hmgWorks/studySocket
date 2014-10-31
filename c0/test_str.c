#include <stdio.h>
#include <stdlib.h>

int strLen(char* str)
{
	int cnt = 0;

	while(1)
	{
		if(str[cnt] == 0)
			break;
	
		cnt++;
	}
	
	return cnt;
}

char* strCat(char* str1, char* str2)
{
	char* ch;
	ch = (char*)malloc(sizeof(char) * (strLen(str1) + strLen(str2)+1));
	
	int i = 0;
	
	while(1)
	{
		if(str1[i] == 0)
		{
			i = 0;	
			break;
		}
		
		ch[i] = str1[i];
		i++;
	}

	while(1)
	{
		if(str2[i] == 0)
			break;
		
		ch[strLen(str1) + i] = str2[i];
		i++;
	}

	return ch;
}

void main()
{
	char* ch;
	char* str1 = "hello";
	char* str2 = "world";

	ch = strCat(str1, str2);
	printf("%s\n", ch);
}
