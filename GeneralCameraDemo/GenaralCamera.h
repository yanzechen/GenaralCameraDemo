#pragma once
#define EXTERN_C extern "C"

// ��������ֵ
typedef enum tagCAMERA_STATUS
{
	STATUS_OK = 1,												// �����ɹ�
	STATUS_INTERNAL_ERROR = 0,							// �ڲ�����
	STATUS_NO_DEVICE_FIND = -1,							// û�з������
	STATUS_NOT_ENOUGH_SYSTEM_MEMORY = -2,		// û���㹻ϵͳ�ڴ�
	STATUS_HW_IO_ERROR = -3,								// Ӳ��IO����
	STATUS_PARAMETER_INVALID = -4,					// ������Ч
	STATUS_PARAMETER_OUT_OF_BOUND = -5,			// ����Խ��
	STATUS_FILE_CREATE_ERROR = -6,						// �����ļ�ʧ��
	STATUS_FILE_INVALID = -7,								// �ļ���ʽ��Ч
	STATUS_NO_RESOLUTION_FOUND = -8,					// ��֧�ִ˸�ʽ
	STATUS_NO_CAM_INIT = -9									// û�г�ʼ��
}CAMERA_STATUS;

// ��ɫ�ռ�
typedef enum tagCOLORSPACE
{
	COLORSPACE_YUY2,											// YUV2
	COLORSPACE_MJPG,											// MJPEG
	COLORSPACE_RGB24,										// RGB24
	COLORSPACE_I420											// I420
}COLORSPACE;

// ¼���ʽ
typedef enum tagVIDEOFORMAT
{
	VIDEOFORMAT_avi,											// AVI
	VIDEOFORMAT_asf											// ASF
}VIDEOFORMAT;

// ���ո�ʽ
typedef enum tagPICTUREFOMAT
{
	PICTUREFORMAT_JPG,										// JPEG
	PICTUREFORMAT_BMP										// BMP
}PICTUREFORMAT;

// ������
typedef enum tagCAMERA_PROPERTY
{
	PROPERTY_Brightness = 0,								// ����
	PROPERTY_Contrast = 1,									// �Աȶ�
	PROPERTY_Hue = 2,										// ɫ��
	PROPERTY_Saturation = 3,								// ���Ͷ�
	PROPERTY_Sharpness = 4,								// ������
	PROPERTY_Gamma = 5,									// ٤��
	PROPERTY_ColorEnable = 6,								// �ڰ�
	PROPERTY_WhiteBalance = 7,							// ��ƽ��
	PROPERTY_BacklightCompensation = 8,				// ���Ա�
	PROPERTY_Gain = 9										// ����
} CAMERA_PROPERTY;

// ������
typedef enum tagCAMERA_CONTROL
{
	CONTROL_Pan = 0,											// ȫ��
	CONTROL_Tilt = 1,											// ��б
	CONTROL_Roll = 2,											// ����ת
	CONTROL_Zoom = 3,										// ����
	CONTROL_Exposure = 4,									// �ع�
	CONTROL_Iris = 5,											// ��Ȧ
	CONTROL_Focus = 6										// ����
} CAMERA_CONTROL;

// �Ƿ��Զ�����
typedef enum tagPROPERTY_FLAGS
{
	PROPERTY_FLAGS_Auto = 1,								// �Զ�
	PROPERTY_FLAGS_Manual = 2								// �ֶ�
} PROPERTY_FLAGS, CONTROL_FLAGS;

// ��ԴƵ��
typedef enum tagPOWER_LINE
{
	POWER_LINE_50Hz = 1,
	POWER_LINE_60Hz = 2
}POWER_LINE;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�ص�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		DS_SNAP_PROC
*	Description:		�ص����������붨�壩
*	Parameters:	ÿ֡Ԥ��ͼ�����ݣ����ݳ���
*	Return :			��������
*/
typedef int (CALLBACK* DS_SNAP_PROC)(BYTE *pImageBuffer, LONG BufferLength);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�豸��Ϣ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ȡCamera������������ã�
*	Parameters:	Camera����
*/
EXTERN_C CAMERA_STATUS GetCameraCount(OUT LONG* CameraCout);

/*
*	Description:		��ȡCamera��Ϣ
*	Parameters:	�����ţ�VID��PID���豸����
*/
EXTERN_C CAMERA_STATUS GetCameraInfo(IN BYTE CamNum,
	OUT CHAR** VID, OUT CHAR** PID,
	OUT CHAR** DeviceName);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�豸��ʼ�����ͷ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ʼ��Camera��������ã�
*	Parameters:	�����ţ��ص�������Ԥ�����ھ��������Ԥ����NULL��
*/
EXTERN_C CAMERA_STATUS  CameraInit(BYTE CamNum,
	DS_SNAP_PROC pCallbackFunction,
	HWND hWndDisplay);

/*
*	Description:		�ͷ�Camera��������ã�
*	Parameters:	������
*/
EXTERN_C CAMERA_STATUS CameraUnInit(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Ԥ��
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ȡCamera֧�ֵ�Ԥ����ʽ����
*	Parameters:	�����ţ���ʽ����
*/
EXTERN_C CAMERA_STATUS GetPreviewResolutionCount(IN BYTE CamNum,
	OUT LONG* ResolutionCount);

/*
*	Description:		��ȡ��ӦԤ����ʽ��Ϣ
*	Parameters:	�����ţ���ʽ��ţ�ɫ�ʿռ䣬����
*/
EXTERN_C CAMERA_STATUS GetPreviewResolutionInfo(IN BYTE CamNum,
	IN BYTE ResolutionNum,
	OUT COLORSPACE* piColorspace,
	OUT LONG* plWidth,
	OUT LONG* plHeight);

/*
*	Description:		��ʼԤ��
*	Parameters:	������
*/
EXTERN_C CAMERA_STATUS CameraPlay(BYTE CamNum);

/*
*	Description:		ֹͣԤ��
*	Parameters:	������
*/
EXTERN_C CAMERA_STATUS CameraStop(BYTE CamNum);

/*
*	Description:		����Ԥ����ʽ
*	Parameters:	�����ţ���ʽ���
*/
EXTERN_C CAMERA_STATUS CameraSetVideoFormat(BYTE CamNum,
	BYTE ResolutionNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ȡCamera֧�ֵ����ո�ʽ����
*	Parameters:	�����ţ���ʽ����
*/
EXTERN_C CAMERA_STATUS GetStillResolutionCount(IN BYTE CamNum,
	OUT LONG* ResolutionCount);

/*
*	Description:		��ȡ��Ӧ���ո�ʽ��Ϣ
*	Parameters:	�����ţ���ʽ��ţ���ɫ�ռ䣬����
*/
EXTERN_C CAMERA_STATUS GetStillResolutionInfo(IN BYTE CamNum,
	IN BYTE ResolutionNum,
	OUT COLORSPACE* piColorspace,
	OUT LONG* plWidth,
	OUT LONG* plHeight);

/*
*	Description:		�������ո�ʽ
*	Parameters:	�����ţ���ʽ���
*/
EXTERN_C CAMERA_STATUS CameraSetStillFormat(BYTE CamNum,
	BYTE ResolutionNum);

/*
*	Description:		����
*	Parameters:	�����ţ�BMPorJPEG��ͼƬ�ļ����ƣ�����ͼƬ·�����ļ�����
*/
EXTERN_C CAMERA_STATUS CameraSnapShot(BYTE CamNum,
	PICTUREFORMAT uiformat,
	WCHAR* wszPictureFile
	);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	¼��
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ʼ¼��
*	Parameters:	�����ţ�AVIorASF��¼���ļ����ƣ�����ͼƬ·�����ļ�����
*/
EXTERN_C CAMERA_STATUS CameraStartCapture(BYTE CamNum,
	VIDEOFORMAT uiformat,
	WCHAR* wszCaptureFile);
/*
*	Description:		ֹͣ¼��
*	Parameters:	������
*/
EXTERN_C CAMERA_STATUS CameraStopCapture(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	���Լ�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		��ȡ����ҳ��Ŀ��Χ��������Ĭ��ֵ���Ƿ��Զ�
*	Parameters:	�����ţ�����ֵ����Сֵ�����ֵ���������Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraPropertyGetRange(IN BYTE CamNum,
	IN CAMERA_PROPERTY uiProperty,
	OUT LONG* pMin, OUT LONG* pMax,
	OUT LONG* pSteppingDelta,
	OUT LONG* pDefault,
	OUT PROPERTY_FLAGS* pCapsFlags
	);

/*
*	Description:		��ȡ����ҳ��Ŀ����ֵ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraPropertyGet(BYTE CamNum,
	CAMERA_PROPERTY uiProperty,
	OUT LONG* lValue,
	OUT PROPERTY_FLAGS* Flags
	);

/*
*	Description:		��������ҳ��Ŀ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraPropertySet(BYTE CamNum,
	CAMERA_PROPERTY uiProperty,
	IN LONG lValue,
	IN PROPERTY_FLAGS Flags
	);

/*
*	Description:		��ȡ����ҳ��Ŀ��Χ��������Ĭ��ֵ���Ƿ��Զ�
*	Parameters:	�����ţ�����ֵ����Сֵ�����ֵ���������Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraControlGetRange(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	OUT LONG* pMin, OUT LONG* pMax,
	OUT LONG* pSteppingDelta,
	OUT LONG* pDefault,
	OUT CONTROL_FLAGS* pCapsFlags
	);

/*
*	Description:		��ȡ����ҳ��Ŀ����ֵ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraControlGet(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	OUT LONG* lValue,
	OUT CONTROL_FLAGS* Flags
	);

/*
*	Description:		���ÿ���ҳ��Ŀ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*/
EXTERN_C CAMERA_STATUS CameraControlSet(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	IN LONG lValue,
	IN CONTROL_FLAGS Flags
	);

/*
*	Description:		��ȡ��ǰ֡��
*	Parameters:	�����ţ�֡��
*/
EXTERN_C CAMERA_STATUS CameraGetFrameSpeed(BYTE CamNum,
	OUT DOUBLE* dFramerate);

/*
*	Description:		����֡��
*	Parameters:	�����ţ�֡��
*/
EXTERN_C CAMERA_STATUS CameraSetFrameSpeed(BYTE CamNum,
	IN DOUBLE dFramerate);

/*
*	Description:		���õ�ԴƵ��
*	Parameters:	�����ţ���ԴƵ��
*/
EXTERN_C CAMERA_STATUS CameraSetPowerLine(BYTE CamNum,
	IN POWER_LINE PowerLine
	);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�Ĵ���
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		���Ĵ���
*	Parameters:	�����ţ��Ĵ�����ַ��ֵ
*/
EXTERN_C CAMERA_STATUS CameraReadDSP(BYTE CamNum,
	LONG laddress, OUT LONG* lData);

/*
*	Description:		д�Ĵ���
*	Parameters:	�����ţ��Ĵ�����ַ��ֵ
*/
EXTERN_C CAMERA_STATUS CameraWriteDSP(BYTE CamNum,
	LONG laddress, IN LONG* lData);