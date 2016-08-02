#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void CConcertoDlg::ImportArticle(CString source)
{
	int i;
	int idx;
	int j;
	int k;
	int l;
	double impprix;
	double imptva;
	double imptva2;
	double impval1;
	double impval2;
	int impperso;
	int impconso;
	int impvconso;
	int fsirnaf;
	CString implibel1;
	CString implibel2;
	CString implibelspect;
	CString implibelcons;
	CString couleur;
	CString col;
	CString temp;
	CString art;
	CString article;
	CString client;
	CString page;
	CString TVAMEM;
	CString prx;
	CString buf;
	CString disk;
	CString memlangue;
	CString imptarget;
	DWORD ln;
	DWORD rln;
	CMessage msd;
	HANDLE hf;
	if(siret==""||naf==""||nom==""||(adresse1==""&&adresse2==""))
		fsirnaf=1;
	else
		fsirnaf=0;
	if((hf=CreateFile(source+"Article.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
	{
		goto fin;
	}
	ln=64000;
retry:;
	if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,0)),GetFileSize(hf,0),&rln,NULL))
		CloseHandle(hf);
	else
		goto retry;
	buf.ReleaseBuffer(rln);
	i=buf.Find("*ARTICLE*");
	j=buf.Find("*CLIENT*");
	k=buf.Find("*PAGE*");
	l=buf.Find("*PRIX*");
	article=buf.Mid(i+11,j-i-11);
	client=buf.Mid(j+10,k-j-10);
	page=buf.Mid(k+8,buf.GetLength()-k-8);
	prx=buf.Mid(l+8,buf.GetLength()-l-8);
	CWinApp* pa=AfxGetApp();
	idx=0;
	lna.ResetContent();
	idx=0;
	i=1;
	while(i<=NART)
	{
		art.Format("%u",i);
		if((j=article.Find(";",idx))==-1)
			break;
		implibel1=article.Mid(idx,j-idx);
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		implibel2=article.Mid(idx,j-idx);
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		implibelcons=article.Mid(idx,j-idx);
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		implibelspect=article.Mid(idx,j-idx);
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		impprix=atof(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		imptva=atof(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		impval1=atof(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		imptva2=atof(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		impval2=atof(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		if(serveur!=""&&i>81)
		{
			impperso=atoi(article.Mid(idx,j-idx));
		}
		else
		{
			//impperso=(DWORD)atoi(article.Mid(idx,j-idx))&0xFFFFFFF7;//valactif ignoré...
			impperso=(DWORD)atoi(article.Mid(idx,j-idx));

		}

		idx=j+1;
		if((j=article.Find(";",idx))==-1)
			break;
		impconso=atoi(article.Mid(idx,j-idx));
		idx=j+1;
		if((j=article.Find("\r\n",idx))==-1)
			break;
		impvconso=atoi(article.Mid(idx,1));
		if(impvconso>2)
			impvconso=0;
		idx=j+2;
		if(libel1[i]==implibel1&&libel2[i]==implibel2&&libelcons[i]==implibelcons&&libelspect[i]==implibelspect
			&&prix[i]==impprix&&tva1[i]==imptva&&perso[i]==impperso&&conso[i]==impconso&&entrymode[i]==impvconso&&tva2[i]==imptva2&&val1[i]==impval1&&val2[i]==impval2)
		{
			;
		}
		else
		{
			lna.SetItemData(lna.AddString("article"),i);
		}
		libel1[i]=implibel1;
		pa->WriteProfileString(art,"LIBELLE1",libel1[i]);
		libel2[i]=implibel2;
		pa->WriteProfileString(art,"LIBELLE2",libel2[i]);
		libelcons[i]=implibelcons;
		pa->WriteProfileString(art,"LIBELCONS",libelcons[i]);
		libelspect[i]=implibelspect;
		pa->WriteProfileString(art,"LIBELSPECT",libelspect[i]);
		prix[i]=impprix;
		pa->WriteProfileInt(art,"PRIX",(int)(prix[i]*100));
		tva1[i]=imptva;
		pa->WriteProfileInt(art,"TVA",(int)(tva1[i]*100));
		//Définition du DWORD perso[idx]=valentry+(valplace*2)+(valmix*4)+(valactif*8)+(valexo*0x10)+(valpass*0x1000);
		perso[i]=impperso;
		pa->WriteProfileInt(art,"PERSO",perso[i]);
		conso[i]=impconso;
		pa->WriteProfileInt(art,"CONSO",conso[i]);
		entrymode[i]=impvconso;
		pa->WriteProfileInt(art,"VCONSO",entrymode[i]);
		pa->WriteProfileInt(art,"VALCONSO",entrymode[i]);
		tva2[i]=imptva2;
		pa->WriteProfileInt(art,"TVA2",(int)(tva2[i]*100));
		val1[i]=impval1;
		pa->WriteProfileInt(art,"VAL1",(int)(val1[i]*100));
		val2[i]=impval2;
		pa->WriteProfileInt(art,"VAL2",(int)(val2[i]*100));
		i++;
	}
	idx=0;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	memnom=nom;
	nom=client.Mid(idx,j-idx);
	WriteConfigString("Client","Nom",nom);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	adresse1=client.Mid(idx,j-idx);
	WriteConfigString("Client","Adresse1",adresse1);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	adresse2=client.Mid(idx,j-idx);
	WriteConfigString("Client","Adresse2",adresse2);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	siret=client.Mid(idx,j-idx);
	WriteConfigString("Client","Siret",siret);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	temp=client.Mid(idx,j-idx);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	temp=client.Mid(idx,j-idx);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	TVAMEM=TVA;
	TVA=client.Mid(idx,j-idx);
	tva1[0]=atof(TVA);
	WriteConfigString("Client","TVA",TVA);
	if(TVA=="")
	{
		global=0;
	}
	else
	{
		global=1;
		tva1[0]=atof(TVA);
	}
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	cur=client.Mid(idx,j-idx);
	WriteConfigString("Client","Devise",cur);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[0]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 0",lic[0]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[1]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 1",lic[1]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[2]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 2",lic[2]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[3]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 3",lic[3]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[4]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 4",lic[4]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[5]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 5",lic[5]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	lic[6]=client.Mid(idx,j-idx);
	WriteConfigString("Client","License 6",lic[6]);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	mentiont=client.Mid(idx,j-idx);
	WriteConfigString("Client","MentionT",mentiont);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	mentionp=client.Mid(idx,j-idx);
	WriteConfigString("Client","MentionP",mentionp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	fprev=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",fprev);
	WriteConfigString("Client","Prevente",temp);
	if(fprev==0)
	{
		for(int i=0;i<100;i++)
		{
			temp.Format("%u",i);
			target[i]=0;
			AfxGetApp()->WriteProfileInt(temp,"TARGET",0);
			entrymode[i]=0;
			AfxGetApp()->WriteProfileInt(temp,"VALCONSO",entrymode[i]);
			AfxGetApp()->WriteProfileInt(temp,"VCONSO",entrymode[i]);
		}
	}
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	nvalplace=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",nvalplace);
	WriteConfigString("Client","ValPlace",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	valpwd=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",valpwd);
	WriteConfigString("Client","ValPwd",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	valpage=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",valpage);
	WriteConfigString("Client","ValPage",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	NART=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",NART);
	WriteConfigString("Client","NART",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	NAPP=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",NAPP);
	WriteConfigString("Client","NAPP",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	eflag=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",eflag);
	WriteConfigString("Client","Eflag",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	nvalmix=atoi(client.Mid(idx,j-idx));
	temp.Format("%u",nvalmix);
	WriteConfigString("Client","ValMix",temp);
	idx=j+1;
	if((j=client.Find(";",idx))==-1)
		goto fin;
	memlangue=langue;
	langue=client.Mid(idx,j-idx);
	WriteConfigString("Client","Langue",langue);
	if(memlangue!=langue)
	{
		langfile=workdir+"\\"+langue+".lng";
		for(int i=1;i<TXTC;i++)
		{
			temp.Format("%u",i);
			txtc[i].ReleaseBuffer(GetPrivateProfileString("Controle",temp,"",txtc[i].GetBuffer(100),100,langfile));
		}
		for(int i=1;i<8;i++)
		{
			temp.Format("%u",i);
			jourtxt[i-1].ReleaseBuffer(GetPrivateProfileString("Jour",temp,"",jourtxt[i-1].GetBuffer(100),100,langfile));
		}
		for(int i=1;i<TXTM;i++)
		{
			temp.Format("%u",i);
			txtm[i].ReleaseBuffer(GetPrivateProfileString("Message",temp,"",txtm[i].GetBuffer(100),100,langfile));
		}
		Table[11]=txtc[1];//ENCAISSER
		lcb.ResetContent();
		lcb.AddString(txtc[155]+" "+txtc[154]);
		lcb.AddString(txtc[155]+" "+"ETC");
		lcb.AddString(txtc[155]+" "+"ARBAN");

		ltype.ResetContent();
		ltype.AddString(txtc[144]);
		ltype.AddString(txtc[55]);
		ltype.AddString(txtc[145]);
		if(wsel==1)
		{
			GetDlgItem(IDC_11)->RedrawWindow();
			ent1.RedrawWindow();
			ent2.RedrawWindow();
			ent3.RedrawWindow();
			ntotal.RedrawWindow();
		}
		else
		{
			bconfig.SetWindowText("");
			bresult.SetWindowText("");
			bcontrol.SetWindowText("");
			bart.SetWindowText("");
			if(wsel==2)
			{
				DrawBoutonCloture();
				ent1.RedrawWindow();
				ent2.RedrawWindow();
				ent3.RedrawWindow();
				ent4.RedrawWindow();
				sca.RedrawWindow();
				sda.RedrawWindow();
				sntt.RedrawWindow();
				snta.RedrawWindow();
				bcancel.RedrawWindow();
				DrawBoutonCloture();
			}
			if(wsel==3)
				DrawStaticArticle();
			if(wsel==4)
			{
				GetDlgItem(IDC_11)->RedrawWindow();
			}
		}

	}
	idx=j+1;
	if(client.Find(";",idx)==-1)// teste si serveur, afmode et horaire doivent être pris en compte selon version
	{
		if((j=client.Find("\r\n",idx))==-1)// a cause du \r\n
			goto fin;
		pays=client.Mid(idx,j-idx);
		WriteConfigString("Client","Pays",pays);
		if(pays=="FR")
			infocert=1;
		else
			infocert=0;
	}
	else
	{
		if((j=client.Find(";",idx))==-1)
			goto fin;
		pays=client.Mid(idx,j-idx);
		WriteConfigString("Client","Pays",pays);
		if(pays=="FR")
			infocert=1;
		else
			infocert=0;
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		serveur=client.Mid(idx,j-idx);
		WriteConfigString("Client","Serveur",serveur);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		memafmode=afmode;
		afmode=atoi(client.Mid(idx,j-idx));
		temp.Format("%u",afmode);
		WriteConfigString("Param","AfMode",temp);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		horaire=atoi(client.Mid(idx,j-idx));
		temp.Format("%u",horaire);
		WriteConfigString("Client","Horaire",temp);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		valhor=atoi(client.Mid(idx,j-idx));
		temp.Format("%u",valhor);
		WriteConfigString("Client","ValHor",temp);
		idx=j+1;
		if((j=client.Find("\r\n",idx))==-1)
			goto fin;
		naf=client.Mid(idx,j-idx);
		WriteConfigString("Client","Naf",naf);
	}
	if(TVA!=TVAMEM&&global)
	{	
		i=1;
		while(i<=NART)
		{
			if((idx<82&&serveur!="")||serveur=="")
				tva1[i]=atof(TVA);
			i++;
		}
	}
	if(wsel==5)
		DrawWindowConfig();
	idx=j+1;
	if(page!="")
	{
		i=0;
		idx=0;
		while(i<20)
		{
			if((j=page.Find(";",idx))==-1)
				goto fin;
			if(pag[i]!=page.Mid(idx,j-idx))
			{
				lna.SetItemData(lna.AddString("page"),i);		
				pag[i]=page.Mid(idx,j-idx);
				temp.Format("P%u",i+1);
				pa->WriteProfileString(temp,"Titre",pag[i]);
			}
			idx=j+1;
			if((j=page.Find("\r\n",idx))==-1)
				goto fin;
			if(jour[i]!=page.Mid(idx,j-idx))
			{
				lna.SetItemData(lna.AddString("page"),i);		
				jour[i]=page.Mid(idx,j-idx);
				pa->WriteProfileString(temp,"Jour",jour[i]);
			}
			idx=j+2;
			i++;
		}
	}
	/*if(prx!="")
	{
		i=0;
		idx=0;
		pl.ResetContent();
		while(i<prx.GetLength())
		{
			if((j=prx.Find("\r\n",idx))==-1)
				goto fin;
			if((j-idx)>0)
			{
				temp.Format("%u",i);
				pa->WriteProfileString("Prix",temp,prx.Mid(idx,j-idx));
				pl.AddString(prx.Mid(idx,j-idx));
			}
			idx=j+2;
			i++;
		}
	}
	else
	{
		pl.ResetContent();
	}*/
fin:;
	if(wsel==1)
		if(siret==""||naf==""||nom==""||(adresse1==""&&adresse2==""||fsirnaf))
			DrawWindowConcert();
}

int CConcertoDlg::ImportImage(CString source)
{// Importe des  paramètres d'images à partir d'un fichier précisé dont la source est sur le maitre
	int ret;
	int i;
	int idx;
	int j;
	int k;
	CString temp;
	CString art;
	CString article;
	CString famille;
	CString rubrique;
	CString buf;
	CString im;
	CString imptarget;
	DWORD ln;
	DWORD rln;
	CMessage msd;
	HANDLE hf;
	CStringW wstr;

	if((hf=CreateFile(source+"Borne.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
	{
		msd.mes3=" ";
		msd.mes1="Aucun fichier images trouvé !";
		msd.mes2="Veuillez recommencer.";
		msd.mode=1;
		//msd.DoModal();
		goto fin;
	}
	ln=64000;
retry:;
	if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,0)),GetFileSize(hf,0),&rln,NULL))
		CloseHandle(hf);
	else
		goto retry;
	buf.ReleaseBuffer(rln);
	i=buf.Find("*ARTICLE*",0);
	j=buf.Find("*FAMILLE*",0);
	k=buf.Find("*RUBRIQUE*",0);
	article=buf.Mid(i+11,j-i-11);
	famille=buf.Mid(j+11,k-j-11);
	rubrique=buf.Mid(k+12);
	ret=0;
	idx=0;
	i=1;
	while(i<=NART)
	{
		art.Format("%u",i);
		if((j=article.Find("\r\n",idx))==-1)
			break;
		if(artim[i]!=article.Mid(idx,j-idx))
		{
			artim[i]=article.Mid(idx,j-idx);
			AfxGetApp()->WriteProfileString(art,"IMAGE",artim[i]);
			delete part[i];
			wstr=workdir+artim[i];
			part[i]=new Image(wstr,0);
		}
		idx=j+2;
		i++;
	}
	idx=0;
	i=0;
	while(i<3)
	{
		art.Format("%u",i+1);
		if((j=famille.Find("\r\n",idx))==-1)
			break;
		if((famim[i]!=famille.Mid(idx,j-idx))||famim[i].GetAt(0)=='?')
		{
			famim[i]=famille.Mid(idx,j-idx);
			wstr=workdir+famim[i];
			delete pbfam[i];
			DeleteObject( pfam[i]);
			Bitmap* pbmp= new Bitmap(wstr,0);
			if(pbmp->GetHBITMAP(0xffffff,&pfam[i])==Ok)
			{
				pbfam[i]=new Bitmap(pfam[i],0);
			}
			else
			{
				if(famim[i]!="")
				{
					delete pbmp;
					temp=skindir+"\\Famille\\Image new.jpg";
					wstr=temp;
					pbmp= new Bitmap(wstr,0);
					pbmp->GetHBITMAP(0xffffff,&pfam[i]);
					pbfam[i]=new Bitmap(pfam[i],0);
					if(famim[i].GetAt(0)!='?')
						famim[i]="?"+famim[i];
					ret=1;
				}
				else
				{
					wstr=famim[i];
					pbfam[i]=new Bitmap(wstr,0);
				}
			}
			if(pbmp)
				delete pbmp;
			AfxGetApp()->WriteProfileString("Famille",art,famim[i]);
		}
		idx=j+2;
		i++;
	}
	idx=0;
	i=0;
	while(i<9)
	{
		art.Format("%u",i+1);
		if((j=rubrique.Find("\r\n",idx))==-1)
			break;
		if(rubim[i]!=rubrique.Mid(idx,j-idx))
		{
			rubim[i]=rubrique.Mid(idx,j-idx);
			temp=rubim[i];
			wstr=workdir+temp;
			delete pbrub[i];
			DeleteObject( prub[i]);
			Bitmap* pbmp;
			pbmp=new Bitmap(wstr,0);
			if(pbmp->GetHBITMAP(0xffffff,&prub[i])==Ok)
			{	
				pbrub[i]=new Bitmap(prub[i],0);
			}
			else
			{
				if(rubim[i]!="")
				{
					delete pbmp;
					temp=skindir+"\\Rubrique\\Image new.jpg";
					wstr=temp;
					pbmp= new Bitmap(wstr,0);
					pbmp->GetHBITMAP(0xffffff,&prub[i]);
					pbrub[i]=new Bitmap(prub[i],0);
					if(rubim[i].GetAt(0)!='?')
						rubim[i]="?"+rubim[i];
					ret=1;
				}
				else
				{
					wstr=rubim[i];
					pbrub [i]=new Bitmap(wstr,0);
				}
			}
			if(pbmp)
				delete pbmp;
			AfxGetApp()->WriteProfileString("Rubrique",art,rubim[i]);
		}
		idx=j+2;
		i++;
	}
	if(wsel==1)
		DrawFamilleArticle();
	else
		DrawBoutonArticle(17);
fin:;
	return ret;
}
