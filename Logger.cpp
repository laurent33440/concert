/**
//  Class Logger pour Concerto
**/

#include "stdafx.h"
#include "Logger.h"


Logger::Logger(CConcertoDlg* pConcert)
{
	m_pConcert = pConcert;
	m_szPath = m_pConcert->controldir+"\\ConcertoLog.log";
	
	if(m_pConcert != NULL)
	{
		m_bIsLogFileOK = TRUE;
	}else{
		m_bIsLogFileOK = TRUE;
	}
}

Logger::~Logger()
{
	if(m_hf != NULL)
	{
		CloseHandle(m_hf);
	}
	kill();
}

BOOL Logger::Log(CString szMessage)
{
	CTime tim=CTime::GetCurrentTime();
	DWORD len;
	
	CString temp=tim.Format("%d/%m/%Y %H:%M:%S -- ")+szMessage+"\r\n";
	m_hf=CreateFile(m_szPath,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(m_hf != NULL && m_bIsLogFileOK)
	{
		SetFilePointer(m_hf,NULL,NULL,FILE_END);
		WriteFile(m_hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
		CloseHandle(m_hf);
		return true;
	}
	return false;
}

BOOL Logger::DeleteLog()
{
	DeleteFile(m_szPath);
	return true;
}
