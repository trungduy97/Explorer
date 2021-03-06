#ifndef CDRIVE_H
#define CDRIVE_H
#include <windows.h>
#include <tchar.h>
#include "DriveSize.h"

#define MAX_BUFFER_LEN 105

//Define for GetVolumeInformation
#define VOLUME_NAME_SIZE		MAX_BUFFER_LEN
#define VOLUME_SERIAL_NUMBER	NULL
#define MAX_COMPONENT_LEN		NULL
#define FILE_SYSTEM_FLAG		NULL
#define FILE_SYSTEM_NAME_BUFF	NULL
#define FILE_SYSTEM_NAME_SIZE	0

//For allocate memory
#define MAX_TYPE_LEN		20
#define MAX_DRIVE_LETTER	4
#define MAX_VOLUME_NAME		30
#define MAX_DISPLAY_NAME	30


//For type of drive
#define FIXED_DRIVE		_T("Local Disk")
#define REMOVABLE_DRIVE _T("Removable Drive")
#define CD_ROM			_T("CD-ROM")
#define REMOTE_DRIVE	_T("Network Drive")

class DriveHelper
{
private:
	TCHAR** mDriveType;
	int mNumberOfDrive;
	TCHAR** mDriveLetter;
	TCHAR** mVolumeLabel;
	CDriveSize** mDriveSize;
	CDriveSize* getDriveSize(int i);

public:
	DriveHelper();
	~DriveHelper();

	TCHAR* getDriveLetter(const int &i);
	TCHAR* getDisplayName(const int &i);
	TCHAR* getDriveType(int position);
	LPWSTR getTotalSize(int i);
	LPWSTR getFreeSpace(int i);
	int getCount();
	void getSystemDrives();
};

#endif