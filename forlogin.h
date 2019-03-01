#pragma once

#define true 1
#define false 0
//账号密码的长度规范
#define MINLENGTH 6
#define MAXLENGTH 13
//读取文件的每行最大长度
#define	MAXLENGTH_PER_LINE 30

struct LoginInformation
{
	char login_ID[13];
	char login_Password[13];
	char login_Permission;
}loginInformation[50];		//假设最大上限只有50个用户。（先用着，以后动态申请内存）

int judgeNumsFormat();

int judgePasswordFormat(char Password[]);

void mSignUp();

void initFileData();

void mLogin();

void printPrompt();

int main();

void mSuperAdminEntrance();

void mAdminEntrance();

void mUserEntrance();