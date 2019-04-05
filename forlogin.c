#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "forlogin.h"

FILE *fp;

char ID[13];//账号
char Passworda[13];//密码
char Passwordb[13];//用于再次输入确认密码
char thePermission;//权限等级
int IDnums = 0;//用户个数

//函数返回值为1则代表格式正确。
int judgeNumsFormat() {
	int i;
	for (i = 0; ID[i] != '\0'; i++) {
		if (ID[i] >= 48 && ID[i] <= 57) {
			continue;
		}
		else
		{
			return -1;
		}
	}
	if (i < MINLENGTH || i > MAXLENGTH) {
		return -1;
	}
	return 1;
}
int judgePasswordFormat(char Password[]) {
	int i;
	for (i = 0; Password[i] != '\0'; i++) {
		if (Password[i] >= 48 && Password[i] <= 57 || Password[i] >= 65 && Password[i] <= 90 || Password[i] >= 97 && Password[i] <= 122) {
			continue;
		}
		else
		{
			return -1;
		}
	}
	if (i < MINLENGTH || i > MAXLENGTH) {
		return -1;
	}
	return 1;
}



void mSignUp() {
	
	fp=fopen("database.txt", "a");

	if (fp == NULL) {
		printf("文件写入失败！");
		fclose(fp);
		return;
	}

	while (true)
	{
		printf("请输入6-13位纯数字账号：  ");//这里还有一个账号可能相同的问题尚未解决.
		scanf_s("%s", &ID, 13);		
		fflush(stdin);
		if (judgeNumsFormat() == 1) {
			break;
		}//应该增添strcmp(loginInformation[i].login_ID,ID)，判断是否已经存在该用户名。 
	}

	while (true)
	{
		printf("请输入6-13位密码，仅由数字和字母构成：  ");
		scanf_s("%s", &Passworda, 13);
		fflush(stdin);
		printf("请再次输入密码：  ");
		scanf_s("%s", &Passwordb, 13);
		fflush(stdin);
		if (judgePasswordFormat(Passworda) == 1 && judgePasswordFormat(Passwordb)==1 &&strcmp(Passworda,Passwordb)==0){
			break;
		}
	}

	while(true)
	{
		printf("请输入1位数字代表权限：	（0为超级管理员，1为管理员，2为用户）");
		getchar();
		scanf_s("%c", &thePermission, 1);
		fflush(stdin);
		if (thePermission == 48 || thePermission == 49 || thePermission == 50) {
			break;
		}
	}
	
	//文件加入账号
	fputs(ID, fp);
	fputs("#", fp);
	//加入密码
	fputs(Passworda, fp);
	fputs("#", fp);
	//加入权限
	fputc(thePermission, fp);
	fputc('\n', fp);

	printf("注册成功\n\n");
	fclose(fp);
	Sleep(1000);
	system("cls");//清屏

	initFileData();
	mLogin();
}


void initFileData() {
	char strLine[MAXLENGTH_PER_LINE];
	char temp[MAXLENGTH_PER_LINE];

	fp = fopen("database.txt", "r");
	if (fp == NULL) {
		printf("文件读取失败！");
		return;
	}

	while (!feof(fp))
	{
		int i, j, k;
		fgets(strLine, MAXLENGTH_PER_LINE, fp);
		printf("%s", strLine);

		memset(temp, '\0', sizeof(temp));
		memset(loginInformation[IDnums].login_ID, '\0', sizeof(loginInformation[IDnums].login_ID));
		for (i = 0; strLine[i] != '#'; i++)
		{
			temp[i] = strLine[i];
		}
		strcpy(loginInformation[IDnums].login_ID, temp);
		printf("账号：%s\n", loginInformation[IDnums].login_ID);


		memset(temp, '\0', sizeof(temp));
		memset(loginInformation[IDnums].login_Password, '\0', sizeof(loginInformation[IDnums].login_Password));
		for (k=0,j = i + 1; strLine[j] != '#'; j++)
		{
			temp[k] = strLine[j];
			k++;
		}
		strcpy(loginInformation[IDnums].login_Password, temp);
		thePermission = strLine[j + 1];
		loginInformation[IDnums].login_Permission = thePermission;
		printf("密码：%s\n", loginInformation[IDnums].login_Password);
		printf("权限：%c\n", loginInformation[IDnums].login_Permission);

		IDnums++;
	}
	fclose(fp);

}

void mLogin() {
	char lID[13];
	char lPassword[13];
	
	printf("账号：\t");
	scanf_s("%s",&lID,13);
	fflush(stdin);
	printf("密码：\t");
	scanf_s("%s", &lPassword, 13);
	fflush(stdin);
	
	int flag = -1;
	for (int i = 0; i < IDnums; i++) {
		if (strcmp(lID, loginInformation[i].login_ID) == 0 && strcmp(lPassword, loginInformation[i].login_Password) == 0) {
			flag = 1;
			switch (loginInformation[i].login_Permission)
			{
			case'0':
				printf("超级管理员登录成功\n");
				mSuperAdminEntrance();
				break;
			case'1':
				printf("管理员登录成功\n");
				mAdminEntrance();
				break;
			case'2':
				printf("用户登录成功\n");
				mUserEntrance();
				break;
			default:
				printf("error");
				break;
			}
			break;
		}
	}
	if (!flag) {
		printf("登录失败");
	}

	system("pause");
}


void printPrompt() {
	printf("   _______________________________________\n");
	printf("   |                                      |\n");
	printf("   |                请选择                |\n");
	printf("   |                                      |\n");
	printf("   |         我已有账户——请按 0         |\n");
	printf("   |                                      |\n");
	printf("   |         我是新用户——请按 1         |\n");
	printf("   |______________________________________|\n");
	printf("\t请输入\t\t");
}

int main() {
	int forprintPrompt;
	initFileData();
	printPrompt();
	scanf_s("%d", &forprintPrompt, 1);
	fflush(stdin);

	switch (forprintPrompt)
	{
	case 0:
		mLogin();
		break;
	case 1:
		mSignUp();
	default:
		break;
	}

	return 0;
}
void mSuperAdminEntrance() {
	printf("超级管理员入口ok");
};

void mAdminEntrance() {
	printf("管理员入口ok");
};

void mUserEntrance() {
	printf("用户入口ok");
};
