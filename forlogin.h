#pragma once

#define true 1
#define false 0
//�˺�����ĳ��ȹ淶
#define MINLENGTH 6
#define MAXLENGTH 13
//��ȡ�ļ���ÿ����󳤶�
#define	MAXLENGTH_PER_LINE 30

struct LoginInformation
{
	char login_ID[13];
	char login_Password[13];
	char login_Permission;
}loginInformation[50];		//�����������ֻ��50���û����������ţ��Ժ�̬�����ڴ棩

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