// Des.h: interface for the CDes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__DCF11C69_C01C_43CB_8C20_EF9D7C4CC6E3__INCLUDED_)
#define AFX_DES_H__DCF11C69_C01C_43CB_8C20_EF9D7C4CC6E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DES_ENCRYPT 1
#define DES_DECRYPT 0

#define ROUNDS 16

typedef struct
{
    unsigned long half[2];
}des_keys[16];

class CDes  
{
public:
	CDes();
	virtual ~CDes();

    CString DesCrypteString(CString strPass,CString str,int nFlag);

	void EnCrypteFile(CString password,CString ming,CString mi);
	void DeCrypteFile(CString password,CString mi,CString ming);
private:
	int set_key(unsigned char * key);
	void SetKey(CString strPass);	
	void DesCrypte(unsigned char * data_in,unsigned char * data_out,int encrypt_flag);

	des_keys m_keys;
};

#endif // !defined(AFX_DES_H__DCF11C69_C01C_43CB_8C20_EF9D7C4CC6E3__INCLUDED_)
