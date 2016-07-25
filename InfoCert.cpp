// InfoCert.cpp : fichier d'implémentation norme NF525

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ******************** GESTION DE LA PISTE D'AUDIT ***************************************
int CConcertoDlg::AccesAudit()
{
	if(WriteAudit(10,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::StartTerminal()
{
	if(WriteAudit(80,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::StopTerminal()
{
	if(WriteAudit(40,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::VersionLogiciel()
{
	CString temp;
	temp.Format("%.3f",fversion/1000);
	if(WriteAudit(250,temp)==0)
		return 0;
	return 1;
}
int CConcertoDlg::Maintenance(CString info)
{
	if(WriteAudit(240,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::DefautIntegrite(CString info)
{
	if(WriteAudit(90,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::FonctionEditeur(CString info)
{
	if(WriteAudit(999,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::ImprimanteIndisponible(CString info)
{
	if(WriteAudit(150,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::CloturePeriode()
{
	if(WriteAudit(50,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::ClotureExercice()
{
	if(WriteAudit(60,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::InitialisationDonnee()
{
	if(WriteAudit(260,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::AnnuleTicket(CString info)
{
	if(WriteAudit(190,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::Habilitation(CString info)
{
	if(WriteAudit(130,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::Sauvegarde(CString info)
{
	if(WriteAudit(230,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::Exportation(CString info)
{
	if(WriteAudit(110,info)==0)
		return 0;
	return 1;
}
int CConcertoDlg::ArchivePeriode()
{
	if(WriteAudit(20,"")==0)
		return 0;
	return 1;
}
int CConcertoDlg::ArchiveExercice()
{
	if(WriteAudit(30,"")==0)
		return 0;
	return 1;
}

CString CConcertoDlg::Sign(int type)
{
	CString signature="";;
	CString temp;
	CString titre;
	int i;
	switch(type)
	{
	case 1://piste d'auditaudit
		{//txt=Identifiant continu, identifiant opération audit, Descriptif si besoin, Date, Code utilisateur, code terminal, report, O/N
			for(i=0;i<7;i++)
			{
				signature+=spart[i];
				if(i<6)
					signature+=",";
			}
			titre="Signature piste d'audit";
		}
		break;
	case 2://signature ticket
		{//txt=Montant TTC par TVA, date, Cumul grand total période en cours, cumul perpétuel, report, O/N
			for(i=0;i<6;i++)
			{
				signature+=spart[i];
				if(i<5)
				{
					signature+=",";
				}
			}
			titre="Signature ticket";
		}
		break;
	case 3://signature grand total ticket ?
		{//txt=Montant TTC par TVA, date, Cumul grand total période en cours, cumul perpétuel, report, O/N
			for(i=0;i<5;i++)
			{
				signature+=spart[i];
				if(i<4)
				{
					signature+=",";
				}
			}
			titre="Signature grand total ticket";
		}
		break;
	case 4://signature grand total période
		{//txt=Cumul grand total période, cumul perpétuel, Montant TTC par TVA, report, O/N
			for(i=0;i<5;i++)
			{
				signature+=spart[i];
				if(i<4)
				{
					signature+=",";
				}
			}
			titre="Signature grand total période";
		}
		break;
	case 5://signature grand total exercice
		{//txt=Cumul grand total exercice, cumul perpétuel, Montant TTC par TVA, report, O/N
			for(i=0;i<5;i++)
			{
				signature+=spart[i];
				if(i<4)
				{
					signature+=",";
				}
			}
			titre="Signature grand total exercice";
		}
		break;
	case 6://signature archive période
		{ //txt= Montant TTC par TVA, grand total période, date, N° du terminal, type d'opération, report, O/N
			for(i=0;i<6;i++)
			{
				signature+=spart[i];
				if(i<5)
				{
					signature+=",";
				}
			}
			titre="Signature archive période";
		}
		break;
	case 7://signature archive exercice
		{ //txt= Montant TTC par TVA, grand total période, date, N° du terminal, type d'opération, report, O/N
			for(i=0;i<6;i++)
			{
				signature+=spart[i];
				if(i<5)
				{
					signature+=",";
				}
			}
			titre="Signature archive exercice";
		}
		break;
	case 8://signature archive export
		{ //txt= Montant TTC par TVA, grand total période, date, N° du terminal, type d'opération, report, O/N
			for(i=0;i<6;i++)
			{
				signature+=spart[i];
				if(i<5)
				{
					signature+=",";
				}
			}
			titre="Signature archive export";
		}
		break;
	default:
		{
			signature="ERREURSIGNATUREELECTRONIQUE";
		}
	}
	//Visualisation composant signature
	if(faudit==type)
	{
		/*if(wsel==1)
		{
			scan=signature;
			nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
			SCANMODE=DT_LEFT|DT_END_ELLIPSIS|DT_NOPREFIX;
			SCANCOLOR=0;
			nscan.ShowWindow(0);
			nscan.SetWindowTextA(signature);
			nscan.ShowWindow(1);
			Sleep(1000);
		}
		else*/
		SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);   
		this->MessageBox(signature,titre);
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);   
	}
	if(ticimp==0)
		return "";
	else
		if(type>=6)
			return GetFileSignature(signature,type);
		else
			return GetDocSignature(signature,type);
}

int CConcertoDlg::WriteAudit(int idx,CString info)
{
	//DWORD len; 
	HANDLE haudit;
	CString temp;
	CString sign;
	CString buf;
	CString signbuf;
	CString DHC;
	CString txtsign;
	CString txtnaudit;
	CString txtoperation;
	CString txtoperator;
	CString txtterminal;
	CString txtop;
	CString txtinfo=info;
	CString txtindicator;
	CString auditfileindex;
retry:;
	auditfileindex.Format("%u",auditfile);
	if((haudit=CreateFile(auditinfopath,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
	{// ouverture piste d'audit si inexistante création du fichier
		CloseHandle(haudit);
		auditfile++;
		auditfileindex.Format("%u",auditfile);
		WriteConfigString("Infocert","Auditfile",auditfileindex);
		auditinfopath=workdir+"\\Auditinfo"+auditfileindex+".dat";
		//auditfileindex.Format("%u",auditfile);
		CWrite(auditinfopath,"Audit file\r\n",0);
		initavert1="Fichier d'évènement indisponible !";
		initavert2="Réinitialisation des données";
		av1.SetWindowText("");
		av2.SetWindowText(initavert1);
		av3.SetWindowText(initavert2);
		Sleep(3000);
		InitialisationDonnee();
		goto retry;
	}
	CloseHandle(haudit);
	CTime tim=CTime::GetCurrentTime();
	if(infocert)
	{
		spart[0].Format("%u",naudit);
		spart[1].Format("%u",idx);
		temp=info;
		temp.Replace(" ","");
		spart[2]=temp;
		spart[3]=tim.Format("%Y%m%d%H%M%S");
		spart[4]=poste;
		spart[5]=poste;
		spart[6]=saudit;
		txtsign=spart[0]+";"+spart[1]+";"+info+";"+spart[3]+";"+poste+";"+poste;
		sign=Sign(1);
		saudit=sign;
		WriteConfigString("Infocert","SignAudit",saudit);
		naudit++;
		temp.Format("%u",naudit);
		WriteConfigString("Infocert","Naudit",temp);
		temp=txtsign+"|"+sign+"\r\n";
	}
	else
		temp=tim.Format("%Y%m%d%H%M%S")+"\r\n";
	CWrite(auditinfopath,temp,1);
	return 1;
}
CString CConcertoDlg::GetExtrait(CString signature)
{
	CString extrait="";
	if(signature.GetLength()>19)
	{
		extrait.AppendChar(signature.GetAt(2));
		extrait.AppendChar(signature.GetAt(6));
		extrait.AppendChar(signature.GetAt(12));
		extrait.AppendChar(signature.GetAt(18));
	}
	return extrait;
}