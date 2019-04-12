#include <iostream>
#include <stdio.h>
#include "modbustcp.h"
#include <string.h>
using namespace std;

/***********************************************************
* Function    : BuildSingleRequestPdu
* Description : 读或者写单个寄存器、线圈时数据整合为PDU
* Input       : unsigned char   ucfunction,功能码
*               unsigned short  unAddr,起始地址
*               unsigned short  unOutData,数值
* Output      : unsigned char   *pCPdu,打包好的PDU
* Return      : 0成功否则失败
* Author      :
* Date        :
* Others      : 暂无
***********************************************************/
int CModbusTCP::BuildSingleRequestPdu
(
    unsigned char  ucfunction,
    unsigned short  unAddr,
    unsigned short  unOutData,
    unsigned char  *pCPdu
)
{
    pCPdu[0] = ucfunction;
    pCPdu[1] = unAddr >> 8;
    pCPdu[2] = (unsigned char)unAddr;
    pCPdu[3] = unOutData >> 8;
    pCPdu[4] = (unsigned char)unOutData;
    return 0;
}
/***********************************************************
* Function    :WriteMutiplePdu
* Description :写多个的情况拼接PDU包
* Input       :
*               unsigned char   ucfunction,功能码
*               unsigned short  unAddr,起始地址
*               unsigned short  unNum,输出数量
*               unsigned char   ucbyteNum，字节数
*               unsigned char  *ucOutData,输出值
* Output      : unsigned char   *pCPdu,打包好的PDU
* Return      : 0成功否则失败
* Author      :
* Date        :
* Others      : 暂无
***********************************************************/
int CModbusTCP::WriteMutiplePdu
(
    unsigned char   ucfunction,
    unsigned short  unAddr,
    unsigned short  unNum,
    unsigned char   ucbyteNum,
    unsigned char  *ucOutData,
    unsigned char  *pCPdu
)
{
    pCPdu[0] = ucfunction;
    pCPdu[1] = unAddr >> 8;
    pCPdu[2] = (unsigned char)unAddr;
    pCPdu[3] = unNum >> 8;
    pCPdu[4] = (unsigned char)unNum;
    pCPdu[5] = ucbyteNum;

    memcpy(pCPdu+6,ucOutData,ucbyteNum);
    return 0;
}

/***********************************************************
* Function    :WriteMutiplePdu
* Description :屏蔽寄存器
* Input       :
*               unsigned char   ucfunction,功能码
*               unsigned short  unAddr,起始地址
*               unsigned short  unAnd_Mask,
*               unsigned short  unOr_Mask，
* Output      : unsigned char   *pCPdu,打包好的PDU
* Return      : 0成功否则失败
* Author      :
* Date        :
* Others      : 暂无
***********************************************************/
int CModbusTCP::MaskWriteRegister
(
    unsigned char   ucfunction,
    unsigned short  unAddr,
    unsigned short  unAnd_Mask,
    unsigned short  unOr_Mask,
    unsigned char  *pCPdu
)
{
    pCPdu[0] = ucfunction;
    pCPdu[1] = unAddr >> 8;
    pCPdu[2] = (unsigned char)unAddr;
    pCPdu[3] = unAnd_Mask >> 8;
    pCPdu[4] = (unsigned char)unAnd_Mask;
    pCPdu[5] = unOr_Mask >> 8;
    pCPdu[6] = (unsigned char)unOr_Mask;


    return 0;
}
/***********************************************************
* Function    :ReadWriteMutipleRegister
* Description :同时读、写多个寄存器的情况拼接PDU包
* Input       :
*               unsigned char   ucfunction,功能码
*               unsigned short  unReadAddr,读取起始地址
*               unsigned short  unReadNum,读取数量
*               unsigned short  unWriteAddr,写初始地址
*               unsigned short  unWriteNum,写入数量
*               unsigned char   ucWriteByte,写操纵总字节数 总数为2*N
*               unsigned char  *ucWriteRegData,写寄存器值  N*2个字节，即值为ushort型
* Output      : unsigned char   *pCPdu,打包好的PDU
* Return      : 0成功否则失败
* Author      :
* Date        :
* Others      : 暂无
***********************************************************/
int CModbusTCP::ReadWriteMutipleRegister
(
    unsigned char   ucfunction,
    unsigned short  unReadAddr,
    unsigned short  unReadNum,
    unsigned short  unWriteAddr,
    unsigned short  unWriteNum,
    unsigned char   ucWriteByte,
    unsigned char  *ucWriteRegData,
    unsigned char  *pCPdu
)
{
    pCPdu[0]  = ucfunction;
    pCPdu[1]  = unReadAddr >> 8;
    pCPdu[2]  = (unsigned char)unReadAddr;
    pCPdu[3]  = unReadNum >> 8;
    pCPdu[4]  = (unsigned char)unReadNum;
    pCPdu[5]  = unWriteAddr >> 8;
    pCPdu[6]  = (unsigned char)unWriteAddr;
    pCPdu[7]  = unWriteNum >> 8;
    pCPdu[8]  = (unsigned char)unWriteNum;
    pCPdu[9]  = ucWriteByte;

    memcpy(pCPdu+10,ucWriteRegData,ucWriteByte);
    return 0;
}
/***********************************************************
* Function    : CModbusTCP::ReadDeviceID
* Description : 读取设备ID
* Input       : unsigned char   ucfunction,功能码
*               unsigned char   ucMEIType,MEI类型
*               unsigned char   ucReadDevID,读取设备ID
*               unsigned char   ucObjectID, 对象ID
* Output      : unsigned char   *pCPdu,打包好的PDU
* Return      : 0成功否则失败
* Author      :
* Date        :
* Others      : 暂无
***********************************************************/
int CModbusTCP::ReadDeviceID
(
    unsigned char   ucfunction,
    unsigned char   ucMEIType,
    unsigned char   ucReadDevID,
    unsigned char   ucObjectID,
    unsigned char  *pCPdu
)
{
    pCPdu[0]  = ucfunction;
    pCPdu[1]  = ucMEIType;
    pCPdu[2]  = ucReadDevID;
    pCPdu[3]  = ucObjectID;

    return 0;
}
/***********************************************************
* Function    : CModbusTCP::BuildRequestHeader
* Description : MBAP+PDU打包为ADU
* Input       : unsigned short nTrans_Iden,事务元标识符
*			    unsigned short nProtocol_Iden,协议标识符
*			    unsigned short nData_Len, 以下数据字节长度
*			    unsigned char nUnit_Iden, 单元标识符(TCP中设置为0XFF,TCP/IP中通过IP地址寻址MODBUS服务器）)
*			    unsigned char   *pCPdu,打包好的PDU
* Output      : unsigned char   *pCAdu,打包好的ADU
* Return      : 0成功否则失败
* Author      : 
* Date        : 
* Others      : 暂无
***********************************************************/
int CModbusTCP::BuildRequestHeader
(
    unsigned short   nTrans_Iden,
    unsigned short   nProtocol_Iden,
    unsigned short   nData_Len,
    unsigned char    nUnit_Iden,
    unsigned char   *pCPdu,
    unsigned char   *pCAdu
)
{
	if(NULL == pCAdu || NULL == pCPdu)
	{
		printf("error,input null !");
		return -1;
	}
	pCAdu[0] = nTrans_Iden >> 8;
    pCAdu[1] = (unsigned char)nTrans_Iden;
	pCAdu[2] = nProtocol_Iden >> 8;
    pCAdu[3] = (unsigned char)nProtocol_Iden;
	pCAdu[4] = nData_Len >> 8;
    pCAdu[5] = (unsigned char)nData_Len;
	pCAdu[6] = nUnit_Iden;
    memcpy(pCAdu + 7,pCPdu,nData_Len - 1);   //拼接PDU
	return 0 ;
}

/***********************************************************
* Function    : ResponseAdu
* Description : 处理响应ADU
* Input       : 
*			    unsigned char *pCResAdu 收到的响应ADU包
*
* Output      : unsigned char *pCResPdu 去掉MBAP头的PDU包
* Return      : PDU长度,返回值为-1则指针为空，返回值为-2 则Server返回异常
* Author      : 
* Date        : 
* Others      : 暂无
***********************************************************/
int CModbusTCP::ResponseAdu
(
    char *pCResAdu,
    char *pCResPdu
)
{
    short length = ((short)pCResAdu[4] <<8 | (short)pCResAdu[5]);
    memcpy(pCResPdu,pCResAdu+7,length - 1);
    return length - 1;
}



/***********************************************************
* Function    : ResponsePdu
* Description : 处理响应PDU
* Input       : 
*			    char *pCRes 收到的响应PDU包
*               int nPduLen PDU包的长度
*
* Output      : char  *pCResData 响应包数据部分
* Return      : 0成功否则失败
* Author      : 
* Date        : 
* Others      : 暂无
***********************************************************/
int CModbusTCP::ResponsePdu
(	
    int   nPduLen,
    char  *pCRes,
    char  *pCResData
)
{

    unsigned char ucfunction;
	ucfunction = pCRes[0];
    int nReturnType;

    switch (ucfunction)
    {
        //0x01 读线圈
        case MODBUS_FC_READ_COILS:
            memcpy(pCResData,pCRes+2,nPduLen-2);//数据类型为char
            nReturnType = 2;
            break;
        //0x02;
        case MODBUS_FC_READ_DISCRETE_INPUTS:
            memcpy(pCResData,pCRes+2,nPduLen-2);//数据类型为char
            nReturnType = 2;
            break;
        //0x03
        case MODBUS_FC_READ_HOLDING_REGISTERS:
            memcpy(pCResData,pCRes+2,nPduLen-2);//数据类型为short
            nReturnType = 4;
            break;
        //0x04
        case MODBUS_FC_READ_INPUT_REGISTERS:
            memcpy(pCResData,pCRes+2,nPduLen-2);//数据类型为short
            nReturnType = 4;
            break;
        //0x05
        case MODBUS_FC_WRITE_SINGLE_COIL:
            //写操作，表示成功，返回一个TRUE信号
            memcpy(pCResData,pCRes+1,nPduLen-1);
            nReturnType = 0;
            break;
        //0x06
        case MODBUS_FC_WRITE_SINGLE_REGISTER:
            //写操作，表示成功，返回一个TRUE信号
            memcpy(pCResData,pCRes+1,nPduLen-1);
            nReturnType = 0;
            break;
        //0x0F
        case MODBUS_FC_WRITE_MULTIPLE_COILS:
            //写操作，表示成功，返回一个TRUE信号
            memcpy(pCResData,pCRes+1,nPduLen-1);
            nReturnType = 0;
            break;
        //0x10
        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
            //写操作，表示成功，返回一个TRUE信号
            memcpy(pCResData,pCRes+1,nPduLen-1);
            nReturnType = 0;
            break;
        default:
            nReturnType = -1;//收到异常
            //若服务器返回有异常的情况
            if( ucfunction >> 4 == 0x08 ||
                ucfunction >> 4  == 0x09)
            {
                memcpy(pCResData, pCRes+1, nPduLen - 1);
                printf("modbusServer return something error");
            }
            break;
    }
    return nReturnType ;
}

