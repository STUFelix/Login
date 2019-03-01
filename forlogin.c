#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "forlogin.h"

FILE *fp;

char ID[13];//�˺�
char Passworda[13];//����
char Passwordb[13];//�����ٴ�����ȷ������
char thePermission;//Ȩ�޵ȼ�
int IDnums = 0;//�û�����

//��������ֵΪ1������ʽ��ȷ��
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
		printf("�ļ�д��ʧ�ܣ�");
		fclose(fp);
		return;
	}

	while (true)
	{
		printf("������6-13λ�������˺ţ�  ");//���ﻹ��һ���˺ſ�����ͬ��������δ���.
		scanf_s("%s", &ID, 13);		
		fflush(stdin);
		if (judgeNumsFormat() == 1) {
			break;
		}
	}

	while (true)
	{
		printf("������6-13λ���룬�������ֺ���ĸ���ɣ�  ");
		scanf_s("%s", &Passworda, 13);
		fflush(stdin);
		printf("���ٴ��������룺  ");
		scanf_s("%s", &Passwordb, 13);
		fflush(stdin);
		if (judgePasswordFormat(Passworda) == 1 && judgePasswordFormat(Passwordb)==1 &&strcmp(Passworda,Passwordb)==0){
			break;
		}
	}

	while(true)
	{
		printf("������1λ���ִ���Ȩ�ޣ�	��0Ϊ��������Ա��1Ϊ����Ա��2Ϊ�û���");
		getchar();
		scanf_s("%c", &thePermission, 1);
		fflush(stdin);
		if (thePermission == 48 || thePermission == 49 || thePermission == 50) {
			break;
		}
	}
	
	//�ļ������˺�
	fputs(ID, fp);
	fputs("#", fp);
	//��������
	fputs(Passworda, fp);
	fputs("#", fp);
	//����Ȩ��
	fputc(thePermission, fp);
	fputc('\n', fp);

	printf("ע��ɹ�\n\n");
	fclose(fp);
	Sleep(1000);
	system("cls");//����

	initFileData();
	mLogin();
}


void initFileData() {
	char strLine[MAXLENGTH_PER_LINE];
	char temp[MAXLENGTH_PER_LINE];

	fp = fopen("database.txt", "r");
	if (fp == NULL) {
		printf("�ļ���ȡʧ�ܣ�");
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
		printf("�˺ţ�%s\n", loginInformation[IDnums].login_ID);


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
		printf("���룺%s\n", loginInformation[IDnums].login_Password);
		printf("Ȩ�ޣ�%c\n", loginInformation[IDnums].login_Permission);

		IDnums++;
	}
	fclose(fp);

}

void mLogin() {
	char lID[13];
	char lPassword[13];
	
	printf("�˺ţ�\t");
	scanf_s("%s",&lID,13);
	fflush(stdin);
	printf("���룺\t");
	scanf_s("%s", &lPassword, 13);
	fflush(stdin);
	
	int flag = -1;
	for (int i = 0; i < IDnums; i++) {
		if (strcmp(lID, loginInformation[i].login_ID) == 0 && strcmp(lPassword, loginInformation[i].login_Password) == 0) {
			flag = 1;
			switch (loginInformation[i].login_Permission)
			{
			case'0':
				printf("��������Ա��¼�ɹ�\n");
				mSuperAdminEntrance();
				break;
			case'1':
				printf("����Ա��¼�ɹ�\n");
				mAdminEntrance();
				break;
			case'2':
				printf("�û���¼�ɹ�\n");
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
		printf("��¼ʧ��");
	}

	system("pause");
}


void printPrompt() {
	printf("   _______________________________________\n");
	printf("   |                                      |\n");
	printf("   |                ��ѡ��                |\n");
	printf("   |                                      |\n");
	printf("   |         �������˻������밴 0         |\n");
	printf("   |                                      |\n");
	printf("   |         �������û������밴 1         |\n");
	printf("   |______________________________________|\n");
	printf("\t������\t\t");
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
	printf("��������Ա���ok");
};

void mAdminEntrance() {
	printf("����Ա���ok");
};

void mUserEntrance() {
	printf("�û����ok");
};