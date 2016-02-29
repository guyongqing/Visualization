// Ԥ����
#include "stdafx.h"

// �ļ�����
#include "VisualizationFile.h"

// ·��ȫ�ֱ���
TCHAR	ThePath[MAX_PATH];
TCHAR	TheFileName[MAX_PATH];

//************************************************************************************************
//*************************** �� Ȩ �� �� ********************************************************
//************************************************************************************************

// �շ�����Ϸ�����֤
bool LicenseVerify(void)
{

	TCHAR pszFileName[MAX_PATH] = {0};
    GetModuleFileName(0, pszFileName, MAX_PATH);            // ��ǰ����EXE���ļ���
    MYSTORE_VERIFY_CONTEXT mystore = {0};
    DWORD dwRet = MyStoreVerify(pszFileName, &mystore);     // ��֤���ļ��Ƿ�Ϸ�

	// ��֤�Ϸ�
	if(dwRet==0){

		// ����
		if(mystore.Expired){

			return false;
			
		}else{

			// ���
			if((mystore.Reserved[0]&0x40)==0x40){

				return false;
			
			// �շ�
			}else{

				return true;
			
			}
		
		}

	}

	return false;

}

//************************************************************************************************
//*************************** �ļ����� ***********************************************************
//************************************************************************************************

// ��ȡ����ǰĿ¼
void FileGetPath(void)
{

	// ��ȡ
	GetModuleFileName(NULL,ThePath,MAX_PATH);
	
	// ȥ���ļ���
	for(int i=MAX_PATH;i>0;i--){
		if(ThePath[i]=='\\'){
			break;
		}else{
			ThePath[i]='\0';
		}
	}

}

// ��ȡ�ļ�·��
void FileGetName(LPTSTR fileName)
{

	int j = 0;

	// ����·�����ļ���
	for(int i=0;i<MAX_PATH;i++){

		if(ThePath[i]=='\0'){

			TheFileName[i] = fileName[j];
			if(fileName[j]=='\0'){break;}	
			j++;
		
		}else{

			TheFileName[i] = ThePath[i];

		}

	}

}

// ��ȡ�ļ�����
bool FileGetData(LPTSTR fileName, char* fileBuffer, int fileSize)
{

	// ��ȡ�ļ���
	FileGetName(fileName);

	// �ļ����
	HANDLE hFile = CreateFile(TheFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// ��ȡ�ֽ���
	DWORD dSize = 0;

	// �޷����ļ�
	if(hFile==INVALID_HANDLE_VALUE){
		return false;
	}

	// ��ȡ�ļ�
	if(!ReadFile(hFile,fileBuffer,fileSize,&dSize,NULL)){
		return false;
	}

	// �ر��ļ����
	CloseHandle(hFile);

	return true;

}