/**
//  Class Logger pour Concerto
**/


#pragma once

#include "Singleton.h"
#include "ConcertoDlg.h"

class CConcertoDlg;

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

public :
	BOOL Log(CString szMessage);
	BOOL DeleteLog();

private:
	Logger(CConcertoDlg* pConcert = NULL);
	~Logger();

	CConcertoDlg* m_pConcert;
	CString m_szPath ;
	HANDLE m_hf; // handle file
	BOOL m_bIsLogFileOK ;
};
