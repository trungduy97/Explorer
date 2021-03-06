#include "stdafx.h"
#include "DriveHelper.h"
#include <shellapi.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")


DriveHelper::DriveHelper()
{
	mDriveLetter = NULL;
	mVolumeLabel = NULL;
	mDriveType = NULL;
	mNumberOfDrive = 0;
}

DriveHelper::~DriveHelper()
{
	for (int i = 0; i < mNumberOfDrive; ++i)
	{
		delete[] mDriveLetter[i];
		delete[] mVolumeLabel[i];
		delete[] mDriveType[i];
	}

	delete[] mDriveLetter;
	delete[] mVolumeLabel;
	delete[] mDriveType;
	mNumberOfDrive = 0;
}

TCHAR* DriveHelper::getDriveType(int position)
{
	return mDriveType[position];
}

TCHAR* DriveHelper::getDriveLetter(const int &i)
{
	return mDriveLetter[i];
}


TCHAR* DriveHelper::getDisplayName(const int &i)
{
	return mVolumeLabel[i];
}

int DriveHelper::getCount()
{
	return mNumberOfDrive;
}

LPWSTR DriveHelper::getFreeSpace(int i)
{
	return mDriveSize[i]->getFreeSpace();
}

LPWSTR DriveHelper::getTotalSize(int i)
{
	return mDriveSize[i]->getTotalSize();
}

CDriveSize* DriveHelper::getDriveSize(int i)
{
	__int64 totalSize;
	__int64 freeSpace;

	SHGetDiskFreeSpaceEx(getDriveLetter(i), NULL, (PULARGE_INTEGER)&totalSize, (PULARGE_INTEGER)&freeSpace);

	CDriveSize* driveSize = new CDriveSize(totalSize, freeSpace);

	return driveSize;
}

void DriveHelper::getSystemDrives()
{
	TCHAR buffer[MAX_BUFFER_LEN];  
	TCHAR* volumeTempName = new TCHAR[VOLUME_NAME_SIZE];
	GetLogicalDriveStrings(MAX_BUFFER_LEN, buffer);
	//Tìm số ổ đĩa
	mNumberOfDrive = 0;
	for (int i = 0; (buffer[i] != '\0') || (buffer[i - 1] != '\0'); i++) 
	{
		if (buffer[i] == '\0')
		{
			mNumberOfDrive++;
		}
	}

	//Cấp phát bộ nhớ để chứa chuỗi tương ứng
	mDriveLetter = new TCHAR*[mNumberOfDrive];
	mVolumeLabel = new TCHAR*[mNumberOfDrive];
	mDriveType = new TCHAR*[mNumberOfDrive];
	mDriveSize = new CDriveSize*[mNumberOfDrive];

	for (int i = 0; i < mNumberOfDrive; ++i)
	{
		mDriveLetter[i] = new TCHAR[MAX_DRIVE_LETTER];
		mVolumeLabel[i] = new TCHAR[MAX_DISPLAY_NAME];
		mDriveType[i] = new TCHAR[MAX_TYPE_LEN];
	}

	int j, k;
	int dem = 0;

	for (j = 0; j < mNumberOfDrive; ++j)
	{
		k = 0;
		while (buffer[dem] != 0)
		{
			mDriveLetter[j][k++] = buffer[dem++];
		}
		mDriveLetter[j][k] = '\0'; //Kết thúc chuỗi
		++dem;
	}

	int mType;
	for (int i = 0; i < mNumberOfDrive; ++i)
	{
		mType = GetDriveType(mDriveLetter[i]);
		switch (mType)
		{
		case DRIVE_FIXED:
			StrCpy(mDriveType[i], FIXED_DRIVE);
			break;
		case DRIVE_REMOVABLE:
			StrCpy(mDriveType[i], REMOVABLE_DRIVE);
			break;
		case DRIVE_REMOTE:
			StrCpy(mDriveType[i], REMOTE_DRIVE);
			break;
		case DRIVE_CDROM:
			StrCpy(mDriveType[i], CD_ROM);
			break;
		default:
			break;
		}

		//Lấy kích thước ổ
		mDriveSize[i] = getDriveSize(i);

		//Xóa buffer
		StrCpy(buffer, _T(""));

		//Nếu ổ đĩa là ổ đĩa cứng, ổ USB
		if ((mType == DRIVE_FIXED) || ((mType == DRIVE_REMOVABLE)) || (mType == DRIVE_REMOTE)) 
		{
			//Truy xuất thông tin về hệ thống tập tin và khối lượng liên kết với thư mục gốc được chỉ định
			GetVolumeInformation(mDriveLetter[i], buffer, MAX_BUFFER_LEN,VOLUME_SERIAL_NUMBER,MAX_COMPONENT_LEN,FILE_SYSTEM_FLAG,FILE_SYSTEM_NAME_BUFF,FILE_SYSTEM_NAME_SIZE);
			StrCpy(volumeTempName, buffer);
		}
		else
			if (mType == DRIVE_CDROM)
			{
				GetVolumeInformation(mDriveLetter[i], buffer, MAX_BUFFER_LEN, VOLUME_SERIAL_NUMBER, MAX_COMPONENT_LEN, FILE_SYSTEM_FLAG, FILE_SYSTEM_NAME_BUFF, FILE_SYSTEM_NAME_SIZE);
				
				if (wcslen(buffer) == 0)
				{
					StrCpy(volumeTempName, _T("CD-ROM"));
				}
				else
					StrCpy(volumeTempName, buffer);
			}
			else if (((i == 0) || (i == 1)) && (mType == DRIVE_REMOVABLE))
			{
				StrCpy(volumeTempName, _T("We don't talk to floppy disk any more"));
			}

				if (wcslen(volumeTempName) == 0)
				{
					StrCpy(mVolumeLabel[i], _T("Local Disk"));
				}
				else
				{
					StrCpy(mVolumeLabel[i], volumeTempName);
				}

				StrCat(mVolumeLabel[i], _T(" ("));
				StrNCat(mVolumeLabel[i], mDriveLetter[i], 3);
				StrCat(mVolumeLabel[i], _T(")"));
	}
}




