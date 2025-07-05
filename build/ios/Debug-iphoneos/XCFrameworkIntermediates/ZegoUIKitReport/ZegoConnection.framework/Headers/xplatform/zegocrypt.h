/** 
@file 
@brief		加解密. 实现下列算法: Hash算法: MD5,已实现. 对称算法: DES,未实现. 非对称算法: RSA,未实现
*/
#if !defined(_ZEGOCRYPT_INC_)
#define _ZEGOCRYPT_INC_
#pragma once

#include "zegotypes.h"
#include "zegomd5.h"

#define MD5_DIGEST_LENGTH	16
#define MD5_LBLOCK			16
#define ENCRYPT_PADLEN		18
#define	CRYPT_KEY_SIZE		16

#ifdef __cplusplus
extern "C" {
#endif

	/************************************************************************************************
	对称加密底层函数
	************************************************************************************************/
	//pOutBuffer、pInBuffer均为8uint8, pKey为16uint8
	_ZEGO_API void TeaEncryptECB(const uint8 *pInBuf, const uint8 *pKey, uint8 *pOutBuf);
	_ZEGO_API void TeaDecryptECB(const uint8 *pInBuf, const uint8 *pKey, uint8 *pOutBuf);
	_ZEGO_API void TeaEncryptECB3(const uint8 *pInBuf, const uint8 *pKey, uint8 *pOutBuf);



	/// QQ对称加密第一代函数. (TEA加密算法,CBC模式). 密文格式:PadLen(1uint8)+Padding(var,0-7uint8)+Salt(2uint8)+Body(var uint8)+Zero(7uint8)
	/** @param pInBuf in,		需加密的明文部分(Body)
	@param nInBufLen in,	pInBuf长度
	@param pKey in,			加密Key, 长度固定为16uint8.
	@param pOutBuf out,		输出的密文
	@param pOutBufLen in out,	pOutBuf的长度. 长度是8uint8的倍数,至少应预留nInBufLen+17;
	*/
	_ZEGO_API void oi_symmetry_encrypt(const uint8* pInBuf, int32 nInBufLen, const uint8* pKey, uint8* pOutBuf, int32 *pOutBufLen);


	/// QQ对称解密第一代函数. (TEA加密算法,CBC模式). 密文格式:PadLen(1uint8)+Padding(var,0-7uint8)+Salt(2uint8)+Body(var uint8)+Zero(7uint8)
	/** @param pInBuf in,		需解密的密文.
	@param nInBufLen in,	pInBuf长度. 8uint8的倍数
	@param pKey in,			解密Key, 长度固定为16uint8.
	@param pOutBuf out,		输出的明文
	@param pOutBufLen in out,	pOutBuf的长度. 至少应预留nInBufLen-10
	@return boolean,			如果格式正确返回true
	*/
	_ZEGO_API boolean oi_symmetry_decrypt(const uint8* pInBuf, int32 nInBufLen, const uint8* pKey, uint8* pOutBuf, int32 *pOutBufLen);


	//////////////////////////////////////////////////////////////////////////


	/// QQ对称计算加密长度第二代函数. (TEA加密算法,CBC模式). 密文格式:PadLen(1uint8)+Padding(var,0-7uint8)+Salt(2uint8)+Body(var uint8)+Zero(7uint8)
	/** @param nInBufLen in,	nInBufLen为需加密的明文部分(Body)长度
	@return int,			返回为加密后的长度(是8uint8的倍数)
	*/
	_ZEGO_API int32 oi_symmetry_encrypt2_len(int32 nInBufLen);


	/// QQ对称加密第二代函数. (TEA加密算法,CBC模式). 密文格式:PadLen(1uint8)+Padding(var,0-7uint8)+Salt(2uint8)+Body(var uint8)+Zero(7uint8)
	/** @param pInBuf in,		需加密的明文部分(Body)
	@param nInBufLen in,	pInBuf长度
	@param pKey in,			加密Key, 长度固定为16uint8.
	@param pOutBuf out,		输出的密文
	@param pOutBufLen in out,	pOutBuf的长度. 长度是8uint8的倍数,至少应预留nInBufLen+17;
	*/
	_ZEGO_API void oi_symmetry_encrypt2(const uint8* pInBuf, int32 nInBufLen, const uint8* pKey, uint8* pOutBuf, int32 *pOutBufLen);

	/// QQ对称解密第二代函数. (TEA加密算法,CBC模式). 密文格式:PadLen(1uint8)+Padding(var,0-7uint8)+Salt(2uint8)+Body(var uint8)+Zero(7uint8)
	/** @param pInBuf in,		需解密的密文.
	@param nInBufLen in,	pInBuf长度. 8uint8的倍数
	@param pKey in,			解密Key, 长度固定为16uint8.
	@param pOutBuf out,		输出的明文
	@param pOutBufLen in out,	pOutBuf的长度. 至少应预留nInBufLen-10
	@return boolean,			如果格式正确返回true
	*/
	_ZEGO_API boolean oi_symmetry_decrypt2(const uint8* pInBuf, int32 nInBufLen, const uint8* pKey, uint8* pOutBuf, int32 *pOutBufLen);

	/// 4 bytes单位加密的tea
	/** @param v in,			data 4 bytes
	@param k in,			key 8 bytes
	*/
	_ZEGO_API void _4bytesEncryptAFrame(uint16 *v, uint16 *k);

	/// 4 bytes单位解密的tea
	/** @param v in,			data 4 bytes
	@param k in,			key 8 bytes
	*/
	_ZEGO_API void _4bytesDecryptAFrame(uint16 *v, uint16 *k);


	/// 可追加的CRC32校验，crc-->原有的crc校验值，buf-->待追加校验的缓冲，len-->缓冲长度
	_ZEGO_API uint32 CRC32(uint32 crc, const uint8* buf, int32 len);

	/**
	@}
	*/

#ifdef __cplusplus
};
#endif

#ifdef __cplusplus
#include "zegostream.h"
//　加密uin串
_ZEGO_API int32 store_encrypt_uin_new(const int8* encode_key, uint32 uin, zego::stream& outbuf);
#endif


#endif // !defined(_ZEGOCRYPT_INC_)
