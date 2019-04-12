#ifndef MODBUSCOMMON_H
#define MODBUSCOMMON_H
/*
*********************************************************************************
*                             Modbus-tcp协议配置项                                  *
*********************************************************************************
*/

/*Modbus功能码*/
#define MODBUS_FC_READ_COILS                0x01    /*读线圈状态       */
#define MODBUS_FC_READ_DISCRETE_INPUTS      0x02    /*读离散输入状态    */
#define MODBUS_FC_READ_HOLDING_REGISTERS    0x03    /*读保持寄存器      */
#define MODBUS_FC_READ_INPUT_REGISTERS      0x04    /*读输入寄存器      */
#define MODBUS_FC_WRITE_SINGLE_COIL         0x05    /*写单个线圈        */
#define MODBUS_FC_WRITE_SINGLE_REGISTER     0x06    /*写单个寄存器      */
#define MODBUS_FC_WRITE_MULTIPLE_COILS      0x0F    /*写多个线圈        */
#define MODBUS_FC_WRITE_MULTIPLE_REGISTERS  0x10    /*写多个寄存器      */
#define MODBUS_FC_READ_FILE                 0x14    /*读文件记录        */
#define MODBUS_FC_WRITE_FILE                0x15    /*写文件记录        */
#define MODBUS_FC_MASK_WRITE_REGISTER       0x16    /*屏蔽写寄存器      */
#define MODBUS_FC_WRITE_AND_READ_REGISTERS  0x17    /*读/写多个寄存器   */
#define MODBUS_FC_DEVICE_ID                 0x2B    /*读设备识别码      */

//#pragma pack(1)//设置结构体指针不对齐


class CModbusTCP
{

	public:
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
		int BuildRequestHeader
		(
            unsigned short nTrans_Iden,
            unsigned short nProtocol_Iden,
            unsigned short nData_Len,
            unsigned char  nUnit_Iden,
            unsigned char   *pCPdu,
            unsigned char   *pCAdu
        );
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
        int BuildSingleRequestPdu
        (
            unsigned char  ucfunction,
            unsigned short unAddr,
            unsigned short unOutData,
            unsigned char *pCPdu
        );
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
        int WriteMutiplePdu
        (
            unsigned char  ucfunction,
            unsigned short unAddr,
            unsigned short unNum,
            unsigned char  ucbyteNum,
            unsigned char *ucOutData,
            unsigned char *pCPdu
        );
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
        int MaskWriteRegister
        (
            unsigned char   ucfunction,
            unsigned short  unAddr,
            unsigned short  unAnd_Mask,
            unsigned short  unOr_Mask,
            unsigned char  *pCPdu
        );
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
        int ReadWriteMutipleRegister
        (
            unsigned char   ucfunction,
            unsigned short  unReadAddr,
            unsigned short  unReadNum,
            unsigned short  unWriteAddr,
            unsigned short  unWriteNum,
            unsigned char   ucWriteByte,
            unsigned char  *ucWriteRegData,
            unsigned char  *pCPdu
        );
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
        int ReadDeviceID
        (
            unsigned char   ucfunction,
            unsigned char   ucMEIType,
            unsigned char   ucReadDevID,
            unsigned char   ucObjectID,
            unsigned char  *pCPdu
        );
        /***********************************************************
        * Function    : ResponseAdu
        * Description : 处理响应ADU
        * Input       :
        *			    unsigned char *pCResAdu 收到的响应ADU包
        *
        * Output      : unsigned char *pCResPdu 去掉MBAP头的PDU包
        * Return      : 正常情况PDU长度,返回值为-1则指针为空，返回值为-2 则Server返回异常
        * Author      :
        * Date        :
        * Others      : 暂无
        ***********************************************************/
        int ResponseAdu
        (
            char *pCResAdu,
            char *pCResPdu
        );
        /***********************************************************
        * Function    : ResponsePdu
        * Description : 处理响应PDU
        * Input       :
        *			    unsigned char *pCRes 收到的响应PDU包
        * Output      :
        * Return      : 0成功否则失败
        * Author      :
        * Date        :
        * Others      : 暂无
        ***********************************************************/
        int ResponsePdu
        (
            int   nPduLen,
            char  *pCRes,
            char  *pCResData
        );


};

#endif // MODBUSCOMMON_H

