#pragma once
#define EXTERN_C extern "C"

// 函数返回值
typedef enum tagCAMERA_STATUS
{
	STATUS_OK = 1,												// 动作成功
	STATUS_INTERNAL_ERROR = 0,							// 内部错误
	STATUS_NO_DEVICE_FIND = -1,							// 没有发现相机
	STATUS_NOT_ENOUGH_SYSTEM_MEMORY = -2,		// 没有足够系统内存
	STATUS_HW_IO_ERROR = -3,								// 硬件IO错误
	STATUS_PARAMETER_INVALID = -4,					// 参数无效
	STATUS_PARAMETER_OUT_OF_BOUND = -5,			// 参数越界
	STATUS_FILE_CREATE_ERROR = -6,						// 创建文件失败
	STATUS_FILE_INVALID = -7,								// 文件格式无效
	STATUS_NO_RESOLUTION_FOUND = -8,					// 不支持此格式
	STATUS_NO_CAM_INIT = -9									// 没有初始化
}CAMERA_STATUS;

// 颜色空间
typedef enum tagCOLORSPACE
{
	COLORSPACE_YUY2,											// YUV2
	COLORSPACE_MJPG,											// MJPEG
	COLORSPACE_RGB24,										// RGB24
	COLORSPACE_I420											// I420
}COLORSPACE;

// 录像格式
typedef enum tagVIDEOFORMAT
{
	VIDEOFORMAT_avi,											// AVI
	VIDEOFORMAT_asf											// ASF
}VIDEOFORMAT;

// 拍照格式
typedef enum tagPICTUREFOMAT
{
	PICTUREFORMAT_JPG,										// JPEG
	PICTUREFORMAT_BMP										// BMP
}PICTUREFORMAT;

// 属性项
typedef enum tagCAMERA_PROPERTY
{
	PROPERTY_Brightness = 0,								// 亮度
	PROPERTY_Contrast = 1,									// 对比度
	PROPERTY_Hue = 2,										// 色调
	PROPERTY_Saturation = 3,								// 饱和度
	PROPERTY_Sharpness = 4,								// 清晰度
	PROPERTY_Gamma = 5,									// 伽马
	PROPERTY_ColorEnable = 6,								// 黑白
	PROPERTY_WhiteBalance = 7,							// 白平衡
	PROPERTY_BacklightCompensation = 8,				// 逆光对比
	PROPERTY_Gain = 9										// 增益
} CAMERA_PROPERTY;

// 控制项
typedef enum tagCAMERA_CONTROL
{
	CONTROL_Pan = 0,											// 全景
	CONTROL_Tilt = 1,											// 倾斜
	CONTROL_Roll = 2,											// 镜像翻转
	CONTROL_Zoom = 3,										// 缩放
	CONTROL_Exposure = 4,									// 曝光
	CONTROL_Iris = 5,											// 光圈
	CONTROL_Focus = 6										// 焦点
} CAMERA_CONTROL;

// 是否自动设置
typedef enum tagPROPERTY_FLAGS
{
	PROPERTY_FLAGS_Auto = 1,								// 自动
	PROPERTY_FLAGS_Manual = 2								// 手动
} PROPERTY_FLAGS, CONTROL_FLAGS;

// 电源频率
typedef enum tagPOWER_LINE
{
	POWER_LINE_50Hz = 1,
	POWER_LINE_60Hz = 2
}POWER_LINE;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	回调函数
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		DS_SNAP_PROC
*	Description:		回调函数（必须定义）
*	Parameters:	每帧预览图像数据，数据长度
*	Return :			被动调用
*/
typedef int (CALLBACK* DS_SNAP_PROC)(BYTE *pImageBuffer, LONG BufferLength);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	设备信息
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		获取Camera数量（必须调用）
*	Parameters:	Camera数量
*/
EXTERN_C CAMERA_STATUS GetCameraCount(OUT LONG* CameraCout);

/*
*	Description:		获取Camera信息
*	Parameters:	相机编号，VID，PID，设备名称
*/
EXTERN_C CAMERA_STATUS GetCameraInfo(IN BYTE CamNum,
	OUT CHAR** VID, OUT CHAR** PID,
	OUT CHAR** DeviceName);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	设备初始化与释放
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		初始化Camera（必须调用）
*	Parameters:	相机编号，回调函数，预览窗口句柄（无需预览则NULL）
*/
EXTERN_C CAMERA_STATUS  CameraInit(BYTE CamNum,
	DS_SNAP_PROC pCallbackFunction,
	HWND hWndDisplay);

/*
*	Description:		释放Camera（必须调用）
*	Parameters:	相机编号
*/
EXTERN_C CAMERA_STATUS CameraUnInit(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	预览
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		获取Camera支持的预览格式数量
*	Parameters:	相机编号，格式数量
*/
EXTERN_C CAMERA_STATUS GetPreviewResolutionCount(IN BYTE CamNum,
	OUT LONG* ResolutionCount);

/*
*	Description:		获取相应预览格式信息
*	Parameters:	相机编号，格式编号，色彩空间，宽，高
*/
EXTERN_C CAMERA_STATUS GetPreviewResolutionInfo(IN BYTE CamNum,
	IN BYTE ResolutionNum,
	OUT COLORSPACE* piColorspace,
	OUT LONG* plWidth,
	OUT LONG* plHeight);

/*
*	Description:		开始预览
*	Parameters:	相机编号
*/
EXTERN_C CAMERA_STATUS CameraPlay(BYTE CamNum);

/*
*	Description:		停止预览
*	Parameters:	相机编号
*/
EXTERN_C CAMERA_STATUS CameraStop(BYTE CamNum);

/*
*	Description:		设置预览格式
*	Parameters:	相机编号，格式编号
*/
EXTERN_C CAMERA_STATUS CameraSetVideoFormat(BYTE CamNum,
	BYTE ResolutionNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	拍照
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		获取Camera支持的拍照格式数量
*	Parameters:	相机编号，格式数量
*/
EXTERN_C CAMERA_STATUS GetStillResolutionCount(IN BYTE CamNum,
	OUT LONG* ResolutionCount);

/*
*	Description:		获取相应拍照格式信息
*	Parameters:	相机编号，格式编号，颜色空间，宽，高
*/
EXTERN_C CAMERA_STATUS GetStillResolutionInfo(IN BYTE CamNum,
	IN BYTE ResolutionNum,
	OUT COLORSPACE* piColorspace,
	OUT LONG* plWidth,
	OUT LONG* plHeight);

/*
*	Description:		设置拍照格式
*	Parameters:	相机编号，格式编号
*/
EXTERN_C CAMERA_STATUS CameraSetStillFormat(BYTE CamNum,
	BYTE ResolutionNum);

/*
*	Description:		拍照
*	Parameters:	相机编号，BMPorJPEG，图片文件名称（包括图片路径、文件名）
*/
EXTERN_C CAMERA_STATUS CameraSnapShot(BYTE CamNum,
	PICTUREFORMAT uiformat,
	WCHAR* wszPictureFile
	);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	录像
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		开始录像
*	Parameters:	相机编号，AVIorASF，录像文件名称（包括图片路径、文件名）
*/
EXTERN_C CAMERA_STATUS CameraStartCapture(BYTE CamNum,
	VIDEOFORMAT uiformat,
	WCHAR* wszCaptureFile);
/*
*	Description:		停止录像
*	Parameters:	相机编号
*/
EXTERN_C CAMERA_STATUS CameraStopCapture(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	属性及控制
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		获取属性页项目范围、步进、默认值、是否自动
*	Parameters:	相机编号，属性值，最小值，最大值，步进，是否自动
*/
EXTERN_C CAMERA_STATUS CameraPropertyGetRange(IN BYTE CamNum,
	IN CAMERA_PROPERTY uiProperty,
	OUT LONG* pMin, OUT LONG* pMax,
	OUT LONG* pSteppingDelta,
	OUT LONG* pDefault,
	OUT PROPERTY_FLAGS* pCapsFlags
	);

/*
*	Description:		获取属性页项目设置值
*	Parameters:	相机编号，属性值，设置值，是否自动
*/
EXTERN_C CAMERA_STATUS CameraPropertyGet(BYTE CamNum,
	CAMERA_PROPERTY uiProperty,
	OUT LONG* lValue,
	OUT PROPERTY_FLAGS* Flags
	);

/*
*	Description:		设置属性页项目
*	Parameters:	相机编号，属性值，设置值，是否自动
*/
EXTERN_C CAMERA_STATUS CameraPropertySet(BYTE CamNum,
	CAMERA_PROPERTY uiProperty,
	IN LONG lValue,
	IN PROPERTY_FLAGS Flags
	);

/*
*	Description:		获取控制页项目范围、步进、默认值、是否自动
*	Parameters:	相机编号，控制值，最小值，最大值，步进，是否自动
*/
EXTERN_C CAMERA_STATUS CameraControlGetRange(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	OUT LONG* pMin, OUT LONG* pMax,
	OUT LONG* pSteppingDelta,
	OUT LONG* pDefault,
	OUT CONTROL_FLAGS* pCapsFlags
	);

/*
*	Description:		获取控制页项目设置值
*	Parameters:	相机编号，控制值，设置值，是否自动
*/
EXTERN_C CAMERA_STATUS CameraControlGet(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	OUT LONG* lValue,
	OUT CONTROL_FLAGS* Flags
	);

/*
*	Description:		设置控制页项目
*	Parameters:	相机编号，控制值，设置值，是否自动
*/
EXTERN_C CAMERA_STATUS CameraControlSet(BYTE CamNum,
	CAMERA_CONTROL uiControl,
	IN LONG lValue,
	IN CONTROL_FLAGS Flags
	);

/*
*	Description:		获取当前帧率
*	Parameters:	相机编号，帧率
*/
EXTERN_C CAMERA_STATUS CameraGetFrameSpeed(BYTE CamNum,
	OUT DOUBLE* dFramerate);

/*
*	Description:		设置帧率
*	Parameters:	相机编号，帧率
*/
EXTERN_C CAMERA_STATUS CameraSetFrameSpeed(BYTE CamNum,
	IN DOUBLE dFramerate);

/*
*	Description:		设置电源频率
*	Parameters:	相机编号，电源频率
*/
EXTERN_C CAMERA_STATUS CameraSetPowerLine(BYTE CamNum,
	IN POWER_LINE PowerLine
	);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	寄存器
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Description:		读寄存器
*	Parameters:	相机编号，寄存器地址，值
*/
EXTERN_C CAMERA_STATUS CameraReadDSP(BYTE CamNum,
	LONG laddress, OUT LONG* lData);

/*
*	Description:		写寄存器
*	Parameters:	相机编号，寄存器地址，值
*/
EXTERN_C CAMERA_STATUS CameraWriteDSP(BYTE CamNum,
	LONG laddress, IN LONG* lData);