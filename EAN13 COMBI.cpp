


 
// EAN13.cpp : fichier d'implémentationCode barre
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::GetBilletCode(CString base)
{
	/*Les chiffres sont numérotés de droite à gauche;
	Soit x, la somme des chiffres pairs et y la somme des chiffres impairs
	Calculons z = x +3*ySoit m le nombre divisible par 10 immédiatement supérieur à z
	La somme de contrôle est : m - z

	Exemple : 978020113447
	x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	z = 3 * 19 + 27 = 84
	m = 90
	Somme de contrôle = 90 - 84 = 6
	EAN13 ---> 9 780201 134476*/
	CString temp;
	CString	temp1;
	CString	temp2;
	int x;
	int y;
	int z;
	int m;
	int s;
	int i;
	if(base.GetLength()!=11)
		CodeBarre="";
	else
	{
		base="2"+base;//"3746364"+base;
		x=0;
		y=0;
		i=0;
		temp=base;
		do
		{
			y=y+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			x=x+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			i+=2;
		}
		while(i<base.GetLength());
		z = x +(3*y);
		m =	((z/10)+1)*10;
		s = m-z;
		if(s>9)
			s=0;
		temp.Format("%u",s);
		CodeBarre=base+temp;
	}
}

void CConcertoDlg::GetConsoCode(CString base)
{
	/*Les chiffres sont numérotés de droite à gauche;
	Soit x, la somme des chiffres pairs et y la somme des chiffres impairs
	Calculons z = x +3*ySoit m le nombre divisible par 10 immédiatement supérieur à z
	La somme de contrôle est : m - z

	Exemple : 978020113447
	x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	z = 3 * 19 + 27 = 84
	m = 90
	Somme de contrôle = 90 - 84 = 6
	EAN13 ---> 9 780201 134476*/
	CString temp;
	CString	temp1;
	CString	temp2;
	int x;
	int y;
	int z;
	int m;
	int s;
	int i;
	if(base.GetLength()!=5)
		CodeBarre="";
	else
	{
		base="2000000"+base;//"3746364"+base;
		x=0;
		y=0;
		i=0;
		temp=base;
		do
		{
			y=y+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			x=x+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			i+=2;
		}
		while(i<base.GetLength());
		z = x +(3*y);
		m =	((z/10)+1)*10;
		s = m-z;
		if(s>9)
			s=0;
		temp.Format("%u",s);
		CodeBarre=base+temp;
		
	}
}
void CConcertoDlg::GetUniqueConsoCode(CString base)
{
	/*Les chiffres sont numérotés de droite à gauche;
	Soit x, la somme des chiffres pairs et y la somme des chiffres impairs
	Calculons z = x +3*ySoit m le nombre divisible par 10 immédiatement supérieur à z
	La somme de contrôle est : m - z

	Exemple : 978020113447
	x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	z = 3 * 19 + 27 = 84
	m = 90
	Somme de contrôle = 90 - 84 = 6
	EAN13 ---> 9 780201 134476*/
	CString temp;
	CString	temp1;
	CString	temp2;
	int x;
	int y;
	int z;
	int m;
	int s;
	int i;
	if(base.GetLength()!=12)
		CodeBarre="";
	else
	{
		x=0;
		y=0;
		i=0;
		temp=base;
		do
		{
			y=y+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			x=x+atoi(temp.Right(1));
			temp.Truncate(temp.GetLength()-1);
			i+=2;
		}
		while(i<base.GetLength());
		z = x +(3*y);
		m =	((z/10)+1)*10;
		s = m-z;
		if(s>9)
			s=0;
		temp.Format("%u",s);
		CodeBarre=base+temp;		
	}
}
//**************** TABLE DES CODE DE CREATION DES CODES BARRE ***********
const BYTE TCONV[3][10] = {0x0d, 0x19, 0x13, 0x3d, 0x23, 0x31, 0x2f, 0x3b, 0x37, 0x0b,
                           0x27, 0x33, 0x1b, 0x21, 0x1d, 0x39, 0x05, 0x11, 0x09, 0x17,
                           0x72, 0x66, 0x6c, 0x42, 0x5c, 0x4e, 0x50, 0x44, 0x48, 0x74};
const BYTE TEST[7]= {0x40,0x20,0x10,0x08,0x04,0x02,0x01};
const int  TFP[10][6] = {0, 0, 0, 0, 0, 0,
                         0, 0, 1, 0, 1, 1,
                         0, 0, 1, 1, 0, 1,
                         0, 0, 1, 1, 1, 0,
                         0, 1, 0, 0, 1, 1,
                         0, 1, 1, 0, 0, 1,
                         0, 1, 1, 1, 0, 0,
                         0, 1, 0, 1, 0, 1,
                         0, 1, 0, 1, 1, 0,
                         0, 1, 1, 0, 1, 0};

void CConcertoDlg::PrintBarre(CDC* pdc,int x,int y,int cx,int cy)
{//x et y = origine du code cx et cy = dimension du code pdc = device context
	CString temp;
	CString cb=CodeBarre;
	//MessageBox(cb);
	int i;
	int j;
	int k;
	int idxt;
	int xt;
	float pas;
	BYTE mat;
	if(paravent)
		pas=2;
	else
		pas=(float)cx/136;
	CRect rct;
	CPen pen1(PS_SOLID,(int)pas,RGB(0,0,0));
	pdc->SelectObject(&pen1);
	temp=cb.Left(1);
	idxt=atoi(temp);
	rct.top=y+((cy-y)/5);//018
	rct.bottom=y+cy;//-cy/50;//5
	xt=x;//cx/13;//10;
	rct.left=xt;
	rct.right=xt+(cx/12);
	//pdc->DrawText(temp,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	//x=cx/7;//20;
	x=Draw101(pdc,x,y+((cy-y)/10),cy-((cy-y)/3),(int)pas);
	i=0;
	do
	{
		cb=cb.Right(cb.GetLength()-1);
		j=atoi(cb.Left(1));
		mat=TCONV[ TFP[idxt][i] ] [j];
		k=0;
		do
		{
			if((TEST[k]&mat))
			{
				pdc->MoveTo(x,y+((cy-y)/10));//10);
				pdc->LineTo(x,cy-((cy-y)/3));
			}
			x+=(int)pas;

			k++;
		}
		while(k<7);
		i++;
	}
	while(i<6);
	x=Draw01010(pdc,x,y+((cy-y)/10),cy-((cy-y)/3),(int)pas);
	i=0;
	do
	{
		cb=cb.Right(cb.GetLength()-1);
		j=atoi(cb.Left(1));
		mat=TCONV[ 2] [j];
		k=0;
		do
		{
			if((TEST[k]&mat))
			{
				pdc->MoveTo(x,y+((cy-y)/10));//10);
				pdc->LineTo(x,cy-((cy-y)/3));//20);
			}
			x+=(int)pas;

			k++;
		}
		while(k<7);
		i++;
	}
	while(i<6);
	x=Draw101(pdc,x,y+((cy-y)/10),cy-((cy-y)/3),(int)pas);//1010
}


int CConcertoDlg::Draw101(CDC* pdc,int x,int y,int h,int pas)
{
	pdc->MoveTo(x,y);
	pdc->LineTo(x,h);
	x+=2*pas;
	pdc->MoveTo(x,y);
	pdc->LineTo(x,h);
	return (x+pas);
}
int CConcertoDlg::Draw01010(CDC* pdc,int x,int y,int h,int pas)
{
	x+=pas;
	pdc->MoveTo(x,y);
	pdc->LineTo(x,h);
	x+=2*pas;
	pdc->MoveTo(x,y);
	pdc->LineTo(x,h);
	x+=2*pas;
	return x;
}