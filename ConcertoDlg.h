// ConcertoDlg.h : fichier d'en-tête
//
//  **********************************  VERSIONS  ******************************************
// Version 5.000 => Gestion impression ticket annulation avec type d'opétation X suivant recommandation Infocert | Modification traitement données ticket annulé dans FillTicketList | 
// Correction TVA globale | Modification gestion MAJ fichier controle esclave | Correction 8 chiffres clavier démarrage | Correction libération liste lnbp après passage en Maitre Auto | 
// Déplacement vérification de l'intégrité des fichiers pour éviter blocage au redémarrage | Passage en entrée immédiate d'office après prévente(bouton Mode entrée) | 
// Correction changement de langue dans les esclaves | Mise à 1 par défaut des items d'article même vide 

// Version 4.630 => Insertion code NAF | Impression TVA siret/naf extrait signature sur talon | modification logo NF525 | ajout transfert naf dans les articles | Copier/Coller article
// Blocage billetterie si naf, siret, nom ou adresse manquent | correction vidage buffer scan si pas en controle | affichage du code scanné en vert ou rouge suivant validité pendant 10 secondes
// Version 4.629 => Intégration gestion borne | correction longueur de champ texte config | correction gestion clavier | Insertion champ serveur WEB et afmode dans les fichiers articles transmis aux esclaves |
// Optimisation Changement de N° de poste | Correction nombre de chiffre digicode veille | Correction chargement des langues | TVA globale, horaire, page sur esclave après changement sur maitre |
// Pays dans prévente | Changement TVA globale interdite si vente en cours | transfert immédiat du nombre d'item sur esclave | traduction code revendeur en anglais | Suppression place dans prévente | 
// rajout délai de recopie fichier controle en esclave | inversion ordre TestClotureAnnuelle et TestClotureMensuelle | Correction validation champ date, guichet et libellé 2 au passage prévente/immédiat | 
// Limitation du nombre de poste à 1 chiffre dans clavier num | Insertion champ PREFIXE dans config | optimisation gestion mémoire logo
// Version 4.626 => Rechargement au démarrage signature piste d'audit et ticket | correction TVA absente en cloture auto dans ligne exercice | correction valeur GTZ dans le cas de plusieurs Items |
// Correction impression page journal sur pages suivantes
// Version 4.625 => Optimisation gestion Controle avec 9 billeteries | Agrandissement font ticket libelle 1(MACUMBA)
// Version 4.624 => Optimisation gestion réseau entre billetterie ( 8 threads) | Gestion scanner USB et gestion bluetooth tourniquet | correction controle scanner interne
// Version 4.623 => correction gestion bouton clôture | Item à 1 par défaut dans les paramètres article produit avec EXO
// Version 4.622 => Ajout listbox à la place de codebarre ETC | Gestion Nb item en mode exo(suppression éventuel du code barre) | affichage de la liste des codes barre | gestion pass |
// Correction hauteur fenêtre d'édition de l'extrait de signature sur le ticket faisant disparaitre le caractère _
// Version 4.621 => Correction auto du catalogue d'intégrité des fichiers marqués 0;0 | Modification validation license avec message d'avertissement 15 jours avant |
// possibilité de changer des parametres à distance par un fichier updater | prise en compte du digit de plus dans le N° de version et MAJ
// Version 4.620 => Pays et devise Maroc | Accès pavé numérique par le clavier | Rajout année d'exercice dans fichier catalogue d'intégrité après clôture(bug).
// Version 4.619 => Optimisation gestion thread réseau et affichage témoin réseau et prévente(erreurs d'application aléatoire sur esclave uniquement).
// Version 4.618 => Correction défaut windows ouverture après minuit jour du changement d'heure d'été ou d'hiver.
// Version 4.617 => Correction bug transmission paramètres prévente interne | fermeture clavier avec ENTREE.
// Version 4.616 => Correction affichage mode entree | optimisation texte de langue | blocage annulation ticket si non motif sélectionné
// Version 4.615 => ReCorrection SingleThreading pour éviter blocage de l'application sur clavier verrou
// Version 4.614 => Correction SingleThreading pour l'application | rajout nombre d'items pour Produit sans EXO
// Version 4.613 => Mise en mémoire Config du path logo en cours
// Version 4.612 => Correction bug gestion commande Atrium | inversion CDialog::OnPaint()(Défaut affichage avec Teamviewer)
// Version 4.611 => Insertion du N° de certification | correction bugs dans la prévente esclave | timer attente fenêtre réseau 2s à 5s | suppression annulation ticket pour code utilisateur
// Version 4.61 => Correction impression journal | signature 1024/2048 | affichage fenetres multiples sécurisée | gestion sécurité accès bureau | correction intégrité des fichiers
// avec heure d'été | modification enregistrement GTP en mode flottant texte GTT | correction affichage des articles vides au démarrage et à la bascule immédiat/prévente | implémentation |
// prévente NOCTIS et correction bug prévente BARMATIC avec test complet | suppression dans signature du O/N et rajout des secondes dans la date ticket | rajout du non affichage dans résultat des totaux tickets, bouton annulation et bouton lecture.
// Version 4.60 => Correction infocert logo | implémentation signature | impression ticket A 0000 version | rajout cumul précédent période et exercice | catalogue des fichiers intégrité
// Version 4.59 => Mise en place infocert, gestion prévente DIGITICK, gestion imprimante Citizen CL-S400DT et spooler, gestion réseau, code revendeur, inscription piste d'audit
// Version 4.55 => Mise en place cloture annuelle/mensuelle auto, piste d'audit, exercice annuel, restructuration archive annelle auto, article actif esclave
// implémentation Montant HT TVA montant TVA Nom et adresse société obligatoire sur ticket, implantation pays
// Version 4.51 => Correction initialisation du pack dans nouvel article, Correction bug dans titre de page
// Version 4.50 => Correction N° prevente, délai de transmission vers imprimante 750mS, validation touche article, gestion maitre autonome
// Version 4.40 => Mise en place importation commandes ATRIUM, mise en place fichier multilangue, implantation pack TVA 2/3 1/3, correction multiconso Arban;
// Version 4.31 => Correction Date répertoire du premier ticket à 0H00, correction écriture data des préventes;
// Version 4.30 => MAJ auto au démarrage si fichier Update présent dans Control;
// Version 4.20 => Correction bug N° de ticket non mémorisé dans la base de registre;
// Version 4.10 => Modification sauvegarde sur D et X;changement code RAZ (ETC);
// Version 4.00 => Validation cryptage des données vente;
// Version 3.50 => Correction nb conso à 0->Pas codebarre et prix non enregistré dans liste etc->Modification des message d'avertissement, correction RAZ a distance;
// Version 3.40 => Sécurisation RAZ avec backup des données sur D:, sauvegarde données registre à chaque sortie manager, sortie ticket et fermeture application;
// Version 3.30 => Mise en place code 65748392 et 29384756 dans Manager, correction bug blocage clavier à cause de target[], Fiabilisation Update ;
// Version 3.20 => Enregistrement forcé à non-crypté, date premier ticket géré la veille si après minuit  ;
// Version 3.10 => refiabilisation enregistrement préventes, lecture enregistrement cypté ou non ;
// Version 3.00 => Recadrage ticket prévente, fiabilisation enregistrement préventes, mise en place structure en vue d'utiliser l'enregistrement cryptée ;
// Version 2.20 => Ajout bouton effacement cb ETC, effacement fichier article pour la centrale des esclaves, correction TAB , cherche update sur Control ;
// Version 2.11 => Allongement du temps 1 seconde entre Reset et PrintIdent car blocage au démarrage de la KPSX.
// Version 2.10 => masquage de la barre de tâche,insertion check code barre ETC, fonction export fiscal auto pour la centrale.

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "atlimage.h"
#include "resource.h"
#include "Num.h"
#include "Message.h"
#include "Ident.h"
#include "SimPrint.h"
#include "Combo.h"
#include "Logger.h"

#define NBK 1				// NOMBRE DE CLE BLUETOOTH DANS LA MACHINE.
#define topline 20				// repère decoupe ticket.
#define midline 560+topline				// repère decoupe ticket.550
#define botline 782+topline					// repère bas ticket.
#define invxt 450				// repère bas ticket.
#define invyt 735				// repère bas ticket.
#define invxa 450				// repère bas ticket.
#define invya 800				// repère bas ticket.
#define crypted 0				// Version  fichier data non crypté
#define rarcrypt 65748392		
#define categorie "A"			// NF525	
#define ticimp 1				// impression extrait signature sur ticket
#define TXTC 162				// Nombre de textes max controle
#define TXTM 103				// Nombre de textes max message
// boîte de dialogue CConcertoDlg

typedef struct _FILEINFO
{	// structure de caractérisation d'un fichier pour la surveillance de l'intégrité
	ULONGLONG time;	// date de modification
	DWORD size;		// taille du fichier
}FILEINFO,*PFILEINFO;



class CConcertoDlg : public CDialog
{
// Construction
public:
	CConcertoDlg(CWnd* pParent = NULL);	// constructeur standard
// Fonctions
	void DrawWindowGeneral(CDC* pDC);	// Dessine le fond de la fenêtre suivant le mode wsel
	void DrawButtonManager();			// Dessine les boutons de service manager et quitter
	void DrawWindowConcert();			// Dessine la fenetre de vente 
	void DrawWindowArticle();			// Dessine la fenetre de paramétrage article
	void DrawWindowResultat();			// Dessine la fenetre de résultat
	void DrawWindowConfig();			// Dessine la fenetre de configuration du logiciel
	void DrawWindowControl();			// Dessine la fenetre de controle
	int InitUserVariable();				// Iniatialise les variables de fonctionnement du logiciel
	void SaveUserVariable();			// Sauvegarde certaines variables de fonctionnement du logiciel en sortie
	void DrawTicket();					// Dessine les colonnes et entête du panier
	void UpdatePageEntree();			// met à jour le texte du titre de page en fonction de artrange index du N° de page de 0 à x
	void DrawPageCom();					// Dessine les bouton de commande du N° de page
	void DrawBoutonQuitter(CString txt);// Dessine le bouton quitter, suivcant écran (wsel)
	void DrawBoutonArticle(int sel);	// Dessine les boutons de vente avec sel en paramètre soit 1 à 16 pour chaque bouton soit 17 pour tous
	void DrawBoutonQuitterBorne(CString txt); // Dessine le bouton quitter en mode borne
	void DrawFamilleArticle();			// Dessine les familles d'entree en mode borne
	void DrawBoutonGestion();			// Dessine les boutons d'onglet service
	void DrawBoutonResult();			// Dessine les controles d'onglet Résultat
	void DrawNumButton();				// Dessine les boutons numérique de quantité
	void DrawBoutonConfArticle();		// Dessine le bouton d'onglet Article
	void DrawBoutonConfig();			// Dessine le bouton d'onglet Config
	void DrawBoutonControl();			// Dessine le bouton d'onglet Controle
	void DrawStaticConfig();			// Dessine et positionne les static et edit de l'onglet de paramétrage logiciel
	void DrawStaticArticle();			// Dessine et positionne les static et edit de l'onglet de paramétrage article
	void DrawQRCode(CString);			// Envoi à QR.exe le paramètre du QRCode à afficher en mode borne
	void FillStat(int);					// Rempli les static de paramètre d'article avec le N° index fourni
	void ClearStat(int);				// Réinialise les statics de paramètre article vierge
	void UpdateEntreeListe(int num);	// Affichage des listes des ventes après appui sur une touche article(paramètre num = N° article)
	void UpdateDEntreeListe(int num);	// En fonction de afmode Affichage des listes des ventes ou association image/article après double click sur touche d'article(paramètre num = N° article)
	void UpdateFamListe(int num);		// Affichage des rubriques après avoir cliquer sur une famille
	void UpdateDFamListe(int num);		// Affichage des galeries d'images avoir double-cliquer sur une famille (paramétrage image)
	void UpdateRubListe(int num);		// Affichage des rubriques après avoir cliquer sur une rubrique
	void DisplayClavier();				// Gestion de l'entrée du nombre de ticket dans l'écran des ventes
	int PrintEntree(CDC*,int,CString,CString,CString,CString,CString,CString,CString,CString,int,CString,int);	// Imprime les tickets d'entrée immédiate
	int PrintPrevente(CDC*,int,CString,CString,CString,CString,CString,CString,CString,CString,CString);		// Imprime les tickets de prévente
	void PrintConso(CDC*,int,CString,CString,CString,CString,CString,CString,CBitmap*,int);	// Imprime le talon des tickets
	void PrintCaisse(CString,CString,CString ,CString);					// imprime le journal de clôture caisse 
	void PrintNews(CString,CString,CString,CString);					// imprime le journal des tickets 
	void PrintTicket(int,int,CString);									// Lance l'impression d'un ticket +talon
	void CloseKeyboard();				// Ferme le clavier tactile		
	int	ExportData(CString,CString);	// Exporte un fichier fiscal sur un an à partir du mois et de l'année sélectionnée
	void ImportArticle(CString);		// Importe des paramètres d'article à partir d'un fichier précisé dont la source est sur le maitre
	int ImportImage(CString);			// Importe des  paramètres d'images à partir d'un fichier précisé dont la source est sur le maitre
	void ImportTicketExterne();			// Recherche des fichiers de contrôle à importer (Maître uniquement)
	void ImportFichierExterne(CString);	// Importe des données de contrôle Concert à partir du fichier precisé
	void ImportFichierWeez(CString);	// Crée un fichier de controle avec des fichiers billetterie WEB de type WeezEvent à partir d'un fichier precisé
	int ImportFichierAtrium(CString);	// Crée un fichier de controle avec des fichiers billetterie WEB de type .csv Atrium ou boutique DINO à partir d'un fichier precisé
	int ImportFichierDigitick(CString);	// Crée un fichier de controle avec des fichiers billetterie WEB de type .csv DIGITICK à partir d'un fichier precisé
	void ImportFichierFil(CString);		// Crée un fichier de controle avec des fichiers billetterie WEB de type .fil  à partir d'un fichier precisé
	int SearchWEBFile();				// cherche des fichier csv sur le serveur WEB
	void FillTicketList(CString);		// Rempli la liste des résultats avec le contenu du fichier pécisé
	void FillCessionList();				// Rempli la liste des archives de clôtures suivant le filtre année/mois précisé en variable globale searchdir
	void GetConsoCode(CString base);	// Calcule la somme de contrôle du code barre EAN13 avec le N° de l'article
	void GetUniqueConsoCode(CString base);;// Calcule la somme de contrôle du code barre EAN13 avec un N° unique basé sur le N° BARMATIC
	void GetBilletCode(CString base);	// Calcule la somme de contrôle du code barre EAN13 avec un N° unique basé sur le N° de prévente
	int Draw101(CDC* pdc,int x,int y,int h,int pas);	// Fonction dessin code barre
	int Draw01010(CDC* pdc,int x,int y,int h,int pas);	// Fonction dessin code barre
	void PrintBarre(CDC* pdc,int x,int y,int cx,int cy);	// Fonction dessin code barre
	void DrawTotal();			// Dessine et positionne le total dans la fenetre de vente
	void DrawBoutonCloture();	// Dessine et positionne les bouton cloture lecture et annulation des résultats
	BOOL SystemShutdown();		// Arrête le systeme et éteint la machine
	BOOL SystemRestart();		// Redémarre le systeme
	void RecalcTotal();			// Recalcule le total affiché dans les ventes
	CTime DirToDate(CString);	//Converti le nom du répertoire en une date
	int InitCaisse(CTime);		// Initialise une ouverture avec son répertoire et son fichier avant d'y inscrire les données de vente
	int CloseCaisse(CTime);		// Fonction de clôture d'une caisse dans les résultats avec en paramètre la date de clôture
	void SaveStaticConfig();	// Sauvegarde le contenu de tous les static de configuration dans un fichier
	void SaveStaticArticle();	// Sauvegarde le contenu de tous les static de paramètre d'un article dans la base de registre
	int Klance();				// Lance le clavier tactile		
	void ValideControl();		// Bascule de commande de controle
	void DelSelEvt();			// Efface un élément et son fichier sélectionné dans la liste de controle
	void AddNewEvt(int);		// Ajoute un élément de controle dans la liste
	int Control(CString,int);	// Controle dans les fichiers de controle arban en cours 
	int ControlMoxity(CString,int);		// Controle  et MAJ dans les fichiers de controle Moxity en cours 
	int ControlTicketplace(CString,int);// Controle  et MAJ dans les fichiers de controle TicketPlace en cours
	int ControlWeezEvent(CString,int);	// Controle  et MAJ dans les fichiers de controle WeezEvent en cours
	void ClearControl(int);				// Supprime le controle de la base de registre
	void RefreshControlList();			// Met à jour la liste de controle
	DWORD GetNbPrinterByte(HANDLE,DWORD);// Récupère le nombre de byte à allouer pour la fonction Printer avec son Handle
	void PrintIdent();					// Imprime un ticket d'identification de la billetterie au démarrage à la mise à jour ou sur commande
	int WaitThread(int);				// Attente fin du thread d'impression suivant status
	void IncSpoolIndex(LONG*);			// Gestion du buffer tournant pour l'impression
	CString DiskSel();					// Recherche du disque d'une clé USB X:\\ de sauvegarde
	void OnSearchScanUSB();				// Recherche d'un scanner USB 
	void OnSearchScanBLUE();			// Recherche d'une clé Bluetooth
	void SetupComBlue();				// Ouvre un port COM sur une clé Bluetooth
	void SetupComUSB();			// Ouvre un port COM sur un scanner USB
	void SetupComGate();		// Ouvre un port COM sur interface bluetooth du tourniquet
	void GetTargetAdress();		// Inscrit l'adresse bluetooth du premier scanner trouvé dans la clé
	CString GetRetStat(int,CString,CString);	// Renvoi le status de retour du périphérique sollicité en comparant les paramètres fournis
	BOOL SendRS(CString);		// Envoi une chaine texte sur le port COM d'une clé
	void SendSpot(BYTE);		// Envoi la couleur du résultat du controle vers l'embase du scanner par la clé bluetooth
	void BlueReset();			// Envoi d'une commande stopant le mode configuration de la clé bluetooth
	void InitKey(int);		// Initialise une clé bluetooth en mode autoconnectée ou non pour pouvoir accèder au périphérique externe sui
	void GetTargetConnected();	// Cherche à savoir si le scanner est connecté sur la clé bluetooth résultat dans CONNECTED
	void ScanCode();				// Traitement du texte du code barre reçu
	void GetBlueRight();			// Vérifie que l'accès à la configuration de la clé bluetooth est possible
	void ReleaseBlueRight();		// Relache le flag d'accès à la configuration de la clé bluetooth
	void BlueSearch();			// Recherche d'un périphérique pour la clé
	void DeleteControleFile(CString);// Efface le fichier de controle path
	CString CheckCurDataFile(CString);// Test format des fichiers lu (inutilisé ?)
	int Scan128A(CDC* pdc,CString temp,int xt,int y,int h,int pas);	// Dessine les barres correspondantes à un caractère du code barre 128
	void PrintBarre128A(CDC* pdc,int x,int y,int cx,int cy,CString);// Dessine un code barre 128 complet
	CString GetCode128A(CString);				// récupère une chaine correspondant à un code barre unique basé sur la date
	int DrawLogo(CDC*,float);					// Dessine le logo sur le ticket avec une largeur xl1
	void FindTypeFile(CString dir,CString type);// Crée une liste (dirlist) de fichiers existant avec l'extension type
	int CashClose();	// Fonction de clôture de cession de vente
	void CashPrint();	// Fonction d'impression de la cession exposée dans la liste des résultats
	void PrinterCommande(BYTE*,DWORD);	// Envoi une commande d'impression dans les imprimantes KPSX et KMGA
	void StartSimulPrinter(int);		// passe l'impression en simulation si erreur d'imprimante
	void DrawLettre(CString temp,CRect rct,CDC* pdc,COLORREF col,CFont*,int);	//Dessine du texte dans des droplistes OwnerDraw
	void DrawQRPhone();
	int SimTicketRect(CDC* pdc,CRect rct);	// Dessine la forme d'un ticket de billetterie à l'écran en mode simulation
	void RefreshArticle();		// Crée des fichiers update d'article pour les esclaves
	void RefreshImage();		// Un maître crée 9 fichiers de configuration d'image borne pour les esclaves
	void RefreshControle();		// Un maître crée un nouveau fichier de configuration de controle pour les esclaves
	void InitFileArticle();		// Un maître crée un fichier article dans le répertoire Data pour la remontée Office
	void PrintCBList();			// Imprime la liste des prix affectés aux codes barre ETC
	void DisplayCBList();		// Affiche la liste des prix affectés aux codes barre ETC
	int CWrite(CString path,CString txt,int mode) ;	// Ecriture dans le fichier précisé, du texte précisé avec le mode 0 ou 1 pour indiquer un ecrasement ou un ajout
	CString CRead(CString path);	// Lecture d'un fichier précisé crypté ou non
	void BackupConcertRegistry();	// Backup du contenu du registre Concert sur D:\Secure  et X:
	void BackupConcertControl();	// Backup des fichiers de controle sur X:
	void InitOldExercice();			// Organise les fichiers d'ancienne version pour être compatibles avec la version NF525 
	void InitVariable();			// Initialise les variable avec le fichier de configuration crypté
	void ClearWindow();				// Masque tous les controles de l'écran
	CString GetConfigString(CString,CString,CString);	// lit une chaine dans le fichier de configuration crypté
	void WriteConfigString(CString,CString,CString);	// Ecrit une chaine dans le fichier de configuration crypté
	int SearchPlace(CString);							// Cherche si un N° de place a déjà été attribué
	void DeleteDirectory(CString path, int mode);		// Supprime le contenu du repertoire précisé dans le mode précisé
	void RedrawQteAdjust(); //Redessine les boutons + et - de la liste de vente borne
	void OpenTourniquet();	// déclenche l'ouverture du tourniquet
	void OnSearchGate();	// Cherche un tourniquet bluetooth
	void TestGateConnected();// teste la connection avec le tourniquet avec un echo RS

	void SendAtriumSpooler(int touche,int ntouche,int cindex);// Imprime une commande d'article provenant d'un site WEB ATRIUM ou DINO
	void PrintAtriumList();	// impression du rapport ATRIUM ou DINO après effacement d'un fichier de controle
	int ControlAtrium(CString,int);// Controle un scan provenant d'un QR ATRIUM ou DINO
	void SendBarmaticSpooler(int idx);

	void SendDigitickSpooler();			// Imprime une commande d'article provenant d'un site WEB DIGITICK
	void PrintDigitickList();			// impression du rapport DIGITICK après effacement d'un fichier de controle
	int ControlDigitick(CString,int);	// Controle un scan provenant d'un QR ou code-barre DIGITICK
	void UpgradeETC();
	void FindArchData(CTime startdate,CTime stopdate,CString path);// Recherche les données d'archivage -> liste dirlist et tl
	void InitMachineName();
		//************************ Fonction Infocert *************************
		// ******* PISTE D'AUDIT ***********
	void TestClotureAnnuelle();				// Génère la clôture annuelle si date arrive à expiration
	void TestClotureMensuelle();			// Génère la clôture mensuelle si date arrive à expiration
	CString GetExtrait(CString signature);	// Renvoi l'extrait NF525 de la signature ticket
	int ExportArchData(CString, CString);// Export Archive fiscale
	int WriteAudit(int idx,CString info);	// Ecrit l'évement info  avec le code idx dans la piste d'audit
						// START *****************  ENUMERATION FONCTION CODE AUDIT ***************
	int AccesAudit();
	int StartTerminal();
	int StopTerminal();
	int AnnuleTicket(CString);
	int VersionLogiciel();
	int Maintenance(CString);
	int InitialisationDonnee();
	int DefautIntegrite(CString);
	int Habilitation(CString);
	int FonctionEditeur(CString);
	int ImprimanteIndisponible(CString);
	int CloturePeriode();
	int ClotureExercice();
	int Sauvegarde(CString);
	int Exportation(CString);
	int ArchivePeriode();
	int ArchiveExercice();
						// END *****************  ENUMERATION FONCTION CODE AUDIT ***************

	void VerifyFileIntegrity();				// Vérifie l'intégrité des fichiers de données au démarrage de l'application
	FILEINFO GetFileInfo(CString path);		// récupére les infos de fichier time et size avec un path
	FILEINFO GetTimeSizeInfo(HANDLE hf);	// récupére les infos de fichier time et size avec un handle de fichier

	// ******* SIGNATURE ***********
	void InitCrypto(int mode);	// initialise la crypto pour la signature électronique
	CString Sign(int type);// type = document à signer le texte étant dans spart[0 à 9]
	CString GetDocSignature(CString,int);// Récupère la signature document avec signature précédente et catégorie signature
	CString GetFileSignature(CString,int);// Récupère la signature fichier avec signature précédente et catégorie signature
	void DeleteCrypto();	// ferme la crypto pour la signature électronique

	//************** COMMUNICATIONS AVEC LOOTY ***********************************************
	void SearchWEBShop();
	BOOL ImportArticlesFromLooty(BOOL bIsUpdate, BOOL bIsPendingSales);
	BOOL CConcertoDlg::UpdateArticlesFromLooty();

	
	//********************************************************************
	// Variables  globales
	
	CString tadress;// Adresse du port du tourniquet sur tiroir caisse 0x480 ->480
	CCombo* pcombo;	// pointeur sur un Combo utilisé dans la fenêtre principale 
	CSimPrint sp;	// Fenetre de simulation ticket sur ecran
	CString edate;	// Date du premier ticket édité après une cloture de periode  (Référence de date des code barre pour caisse ETC)
	LONG PRMODE;	// paramètre d'impresssion autre que ticket
	int fldraw;		// Flag autorisant ou non le rafraichissement du dessin de la liste des résultats entre topindex et topindex+15
	int fclot;		// Flag renseignant sur lr type d'impression de RAZ en cours 1= clôture de caisse 2= historique déjà clôturé
	int veille;     // Flag indiquant mode veille autorisé ou non
	int valpwd;		// Paramètre instituant ou non un clavier de mot de passe au démarrage de l'application 0= pas de clavier 1= clavier
	int valpage;	// Paramètre autorisant ou non une personnalisation du nom des pages et reconnaissance du jour de la semaine 0= pas de perso 1= perso
	int econt;		// N° unique pendant une période pour code barre ETC (RAZ à la cloture)incrémenté par l'impression de chaque code barre ETC
	int acont[100];	// N° unique de codebarre BARMATIC par touche (RAZ à la cloture)incrémenté par l'impression de chaque code barre BARMATIC
	int eflag;		// Paramètre indiquent le type de code barre qui doit être généré sur un ticket 0=Code barre générique du N° de touche 1=Code barre unique ETC 2=Code barre unique BARMATIC
	int exoflag;	// Paramètre autorisant ou non la sortie d'un ticket EXO avec une commande scanner DIGITICK 0= Pas de ticket EXO imprimé 1 = Ticket imprimé
	int echeck;		// Checksumm du code barre 128 calculé avant impression
	int noprint;	// Flag indiquant une simulation ou non d'impression 0=impression 1= impression à l'écran uniquement pour test sans imprimante
	int nbillet;	// N° de billet unique incrémenté à chaque impression de ticket
	int tsorg;		// Origine en y dans les routines d'impression 
	int logo;		// Paramètre idiquant la présence du logo sur les tickets 0= pas de logo 1=logo
	int NART;		// Nombre d'article total utilisés suivant nombre d'articles par page
	int NAPP;		// Nombre d'articles par page;
	int infocert;	// si mode infocert
	int catidx;		// index du fichier du catalogue d'intégrité des fichiers de vente
	int fgate;		// Flag indiquant l'affichage de l'état du tourniqet
	int selfam;		// sélection famille borne
	int selrub;		// sélection rubrique borne
	int afmode;		// mode billetterie/borne
	int memafmode;	// mémoire mode billetterie/borne
	int etb;		//étape borne dans l'affichage
	int etc;		//étape config/resultat borne après mot de passe
	int idxcopy;	// index de l'article qu'on vient de copier 0 si vide
	BYTE* Printer;  // pointeur sur un buffer alloué par GetPrinter
	HANDLE hrun;    // Handle ouvert sur run.dat ((singleton)
	HCRYPTPROV hProv2048; // handle sur crypto 2048
	HCRYPTPROV hProv1024; // handle sur crypto 1024


	HANDLE hwpt;	// HANDLE du thread d'impression  ticket
	HANDLE hsjt;	// HANDLE du thread de scan du spooler
	HANDLE hpjt;	// HANDLE du thread d'impression autre que ticket
	HANDLE HRS;		// HANDLE RS232 du scanner
	HANDLE HRSG;	// HANDLE RS232 du tourniquet
	LONG CONNECTED; // etat de connexion de la clé bluetooth sur le scanner
	HANDLE hRNThread[9] ;      // Handle du Thread de recherche des postes sur ethernet dans liste lmac
	DWORD RNThreadID[9] ;      //ID du Thread de recherche des postes sur ethernet dans liste lmac
	HANDLE hRSGateReadThread ; //Handle du thread traitant les messages de retour (echo) du tourniquet
	DWORD RSGateReadThreadID ; //ID du Thread traitant les messages de retour (echo) du tourniquet
	HANDLE hRSReadThread ;     //Handle du thread traitant les messages de retour de la clé bluetooth
	HANDLE hRSSearchThread ;   //Handle du thread vérifiant les connexions bluetooth avec le scanner et le tourniquet
	DWORD RSReadThreadID ;     //ID du Thread traitant les messages de retour des scanners (USB ou bluetooth) 
	DWORD RSSearchThreadID ;   //ID du Thread vérifiant les connexions bluetooth avec le scanner et le tourniquet
	HANDLE hRSScanThread ;     // Handle du Thread gérant le témoin du scanner et la recherche auto d'un scanner bluetooth
	HANDLE hArticleScanThread ;// Handle du Thread gérant raz.dat, fiscal.dat, updater.dat, récupération article.dat sur maitre et lancement importation
	HANDLE hImageScanThread ;	// Handle du thread récupérant les nouvelles images de la borne sur le maitre
	HANDLE hControlFileThread ;	// Handle du thread master gérant les changement de fichier de controle génère si necessaire un nouveau fichier control.cfg pour les esclaves
	HANDLE hBackupControlFileThread ;// Handle du thread esclave recopiant les nouveaux ficiers de controle à partir du maitre et selon control.cfg et gérant la sortie du rapport atrium digitick
	HANDLE hGetMCIModeThread ;	//Handle du thresd d'affichage des avi duscren saver en borne	
	HANDLE hScanNetThread ;		// Gère les temoins de réseau en fonction de la liste des machines trouvées
	HWND SCR;					// Handle de la fenêtre d'animation avi veille

	PROCESS_INFORMATION kpri;	// Process fenetre réseau
	STARTUPINFO ksui;	// Process fenetre réseau
	PROCESS_INFORMATION netcpi;	// Process fenetre réseau
	PROCESS_INFORMATION datecpi;// Process fenetre date
	PROCESS_INFORMATION printcpi;// Process fenetre périphérique (imprimante)

	CString txtc[TXTC];	// texte controles langue
	CString txtm[TXTM];	// texte messages langue
	CString bufin;		// buffer de texte réception RS232 scanner
	CString bufingate;	// buffer de texte réception RS232 portillon
	CString COMWL;		// nom du port COM scanner
	CString COMG;		// nom du port COM portillon ouvert
	CString COMGATE;	// nom du port COM portillon trouvé
	CString scaninter;	// type de scanner connecté
	CString blueadress;	// Nom de l'adresse MAC bluetooth
	CString initavert1;	// texte de message de fond d'écran
	CString initavert2;	// texte de message de fond d'écran
	CString initavert0;	// texte de message de fond d'écran
	CString configpath;	// path du fichier crypté de paramètres
	CString printername;// Nom de l'mprimante
	CString logopath;	// Path du logo choisi
	CString scrpath;	// Path du scr choisi
	CString qrtext;		// Texte du qr affiché dans la borne
	CString printsigtxt;// Texte de l'extrait de signature sur ticket
	int auditfile;		// N° d'index

	CNum* pinum;		// pointeur sur fenetre de pin code
	CString pcode;		// mémoire du code pin de paiement borne

	LONG FWEB;		// Flag indiquant l'etat de la connexion internet 0= pas de con 1= shop a répondu
	LONG FTEM;	// Flag autorisant l'affichage des témoin
	LONG FLMAC;	// Flag ecriture des thread dans la liste des machines préeente sur le réseau
	LONG END;	// Flag terminant le thread spooler de surveillance du spooler
	LONG SPOOL;	// Flag bloquant l'mpression pendant un manque de papier
	LONG SEARCH;// Etape de recherche de scanner bluetooth
	LONG FART;	// Flag indiquant une modif d'article ou config effacé par RefreshArticle dans un maitre
	LONG FIM;	// Flag indiquant une modif d'image d'article rubrique ou famille
	LONG ABORT;	// FLAG stoppant l'activité RS232 sur port COM scanner bluetooth
	LONG BLUERIGHT;// Demande de droit d'accès RS232 sur com scanner Bluetooth
	LONG GATECON;	// Flag spécifiant l'état de connexion du tourniquet HF
	LONG GATERIGHT;// Demande de droit d'accès RS232 sur com gate Bluetooth
	LONG BASCULE;	// Flag autorisant la reception RS scanner bluetooth pour le fichier de controle
	LONG STOP;		// Arrête le thread d'impression
	LONG RUNRSG;// Flag de lecture de scan dans RSReadThread ; init dans SetupComUSB et OnInitDialog;  Mis à 3 dans RSReadThread pour rien
	LONG STOPRSG;// Flag d'arret du thread RSGateReadThread 
	LONG STOPRS;// Flag d'arret des threads RSReadThread, RSSearchThread, RSScanThread
	LONG RUNRS;// Flag de lecture de scan dans RSReadThread ; init dans SetupComUSB et OnInitDialog;  Mis à 3 dans RSReadThread pour rien
	LONG PAUSERS;// Flag en conjonction avec SEARCH pour gérer la découverte de scanner bluetooth
	LONG QUIT;// Flag indiquant l'arret de la billeterie, chgt n° poste et  force arret impression ticket
	LONG RESTE;// Entier indiquant le nb ticket restant à imprimer (utilisé chgt de mode/utilisateur) 
	LONG READY;// Flag indiquant qu'une impression par le spooler est possible
	LONG SPX[10000];//File du nombre de ticket à imprimer
	LONG SPT[10000];// File du N° article à imprimer
	CString STT[10000];// File de nom place à imprimer
	LONG SPN;// Nb de tickets à imprimer
	LONG SPR;// Index de lecture du fifo du SPOOLER d'impression
	LONG SPW;// index d'écriture du fifo du SPOOLER d'impression
	LONG CONTROL;// Flag mode "controle" de la billeterie
	PRINTER_DEFAULTS pd;//specifies the default data type, environment, initialization data, and access rights for a printer. (voir OnInitDialog)
	UINT memmes;//Valeurs du message de commande provenant du scanner ou du clavier (voir PreTranslateMessage) avec : 
	LPARAM meml;// - parametre long
	WPARAM memw;// - parametre word --> transfert message de la premiere partie du libelle 1 vers la deuxieme partie du libelle 1 
	LONG FREFCONTROL;//Flag demandant de rafraichir la liste de controle avec timer 13

	CRect rctver;	// Rectangle version résultat
	CRect rctdate;	// Rectangle date
	CRect rctpage;	// N° page
	CRect rctinf;	// bouton <
	CRect rctsup;	// bouton >
	CRect rctscan;	// rectangle papier epuise

	Image* pnf525;
	Image* pbsinf;
	Image* pbninf;
	Image* pbssup;
	Image* pbnsup;
	Image* pbsman;
	Image* pbnman;
	Image* pbsquit;
	Image* pbnquit;
	Image* pbsenc;
	Image* pbnenc;
	Image* pbsartac;
	Image* pbnartac;
	Image* pbsartbo;
	Image* pbnartbo;

	Image* pbspaste;
	Image* pbnpaste;

	Image* pbscopy;
	Image* pbncopy;

	Image* pbsresbar;
	Image* pbnresbar;


	Image* pbsnum;
	Image* pbnnum;

	Image* pbsplum;
	Image* pbnplum;

	Image* pbnret;
	Image* pbsret;

	Image* pbnnav;
	Image* pbsnav;

	Image* pbnpomo;
	Image* pbspomo;

	Image* pbsclr;
	Image* pbnclr;

	Image* pbsdel;
	Image* pbndel;

	Image* pecrac;
	Image* pspage;
	Image* parcdc;
	Image* pbur;
	Image* pprint;
	Image* pnet;

	Image* pcheck;
	Image* pncheck;

	Image* part[100];

	HBITMAP pfam[3];
	Bitmap* pbfam[3];

	HBITMAP prub[9];
	Bitmap* pbrub[9];

	Image* pqr;

	HBITMAP hr;

	CMessage* pwjob; 
	CMessage* pwlog;
	CIdent* pwidt;


	int ngopen;	// nombre d'ouverture en cours du tourniquet suite à des impressions d'entrée
	int ngpass;	// nombre de passage dans le tourniquet
	int fraz;	// Flag indiquant qu'on vient de faire une RAZ
	LONG PJOB;// normalement inutile - Mise en mémoire de l'ID job d'impression Windows
	int MAJ;//Flag indiquant qu'une mise à jour vient d'être faite
	int fexermois;	// Flag indiquant cloture mensuelle en cours (Timer de temps)
	LONG fexeran;	// Flag indiquant cloture annuelle en cours (Timer de temps)
	int valexo;	// Flag de la coche EXO de l'IHM	
	int valpass;// Flag de la coche PASS de l'IHM
	int alone;// FLag indiquant une billeterie autonome (et maitre ?) 
	int fart;	// Flag fart à 1 pour indiquer la présence d'un fichier article// flag
	int fartaf;//Flag de clignotement du symbole réseau sur l'esclave en cas de modification article requise par la maître si la clôture n'a pas été faite
	int fsecur;// 0,1,3 : 
			   // 0 : Le logiciel est marqué invalide et les résultats ne seront plus visibles
			   // 1 : Le logiciel est marqué valide
			   // 3 : Le logiciel est marqué en préparation de renouvellement license avec message à chaque résultat
	int fsave;// flag statics marquées sauvegardées
	int contfile;//nb fichier controle,
	int memcontfile;//sauvegarde temp de contfile
	int paravent;//Flag paravant type de rouleau impression
	int simul;// Flag de simulation d'impression de ticket
	int start;// Nombre de démarrage de l'application
	int resultexport;// nb erreur exportation exportData
	CString targetexport;// path de la source transfert pour Exportdata
	LONG artro;// Flag vente d'au moins un article
	int wlargeur;// largeur fenetre
	int whauteur;// hauteur fenetre
	int wsel;// n° de l'écran de l'appli 1= vente, ..., 5 = config
	int artrange;//index du N° de page de 0 à x
	int barre[256]; // Lecture code barres (décodage)
	int	artnum;// numero de l'article dans la page 1 à 16
	int	trackosk;// Flag track clavier voir TIMER
	int flagraz; // flag demande de cloture à distance si fichier raz.dat existe
	int lsel;// selection dans la liste (synchro entre listes écran vente)
	int nbticktot;// nb tickets total
	int nbtickan;// nb tickets annulés
	int autonews; // coche de la case journal automatique après cloture (écran config)
	int autoprint;// coche de la case impression automatique après cloture (écran config)
	int	kid;// id du ctrl static dans lequel on est en train d'ecrire avec le clavier - pour redonner le focus au demandeur
	int seltouche;// n° touche sélectionne 0...x
	int hist;//=0 peridode non cloturée, =1 periode archivée utilisé
	int	fadmin;	// flag adminn
	int	fdev;	// flag dev -- fichier config
	int fupdate;// flag update présent
	int master;// flag master
	//cases à cocher
	int valplace; //est placé 
	int valmix; // 
	int valscr;
	int valentry; // est une entree
	int valactif; // est actif
	int cbx; // n° code barre 
	int nvalmix;//Validation des packs à 2 TVA
	int cvalpass;// validation config du pass
	int nvalplace;// Validation du N° de place
	int viewscan; //bascule M/A affichage du code QR à l'écran (borne)
	int horaire;// Case à cocher présente dans la config
	int valhor;// Etat de la Validation de l'horaire en prévente
	int flagnot; //lié à l'importationd'articles à voir.****************************************************
	int fprev; // flag prevente (ecran config)
	int fpage;		//première page valide (paramètrée en config)
	int shopidx; //N° index mémoire controle (atrium)
	int digidx;//N° index mémoire controle (digitix)
	int rndray;//***************Inutile code à supprimer
	int RAZ; //N° de GTZ en cours
	int HRAZ; // n° de la cloture de l'archive selectionnée
	int nbctc;//compteur d'animation de l'antenne du récepteur radio de contrôle des tickets a supprimer -  timer n°7
	int valid; // flag de retour utilisé pour les fct controles atrium et digitix et concert -- voir utilité ????? ********************************
	int global; // flag TVA globale utilisée
	int SCANMODE; // mode dessin text dans controlcolor IDC_NSCAN 
	int SCANCOLOR; // inutile code àà supprimer ******************************************************************************
	int nc;//compteur de conso...
	int naudit;	// N° piste d'audit
	int cesver; //Info version période 
	int faudit; // flag accès auditeur NF525 piste d'audit-- voir CommandConcert ...
	int qteplu[100]; // nb d'articles vendus pour un un article donné
	float lmarge; //marge à 0 plus utilisé
	float rmarge;//marge à 0 plus utilisé
	double ca; // chiffre d'affaire ... sur quelle periode????
	double catva[10];//montant differentes tva cumulées
	double tvaca[10];//taux des différentes tva
	double tvacumul; // tva cumulée - calculée mais non utilisée --- a supprimer *****************************************
	double valplu[100];// total des ventes pour un article donné (voir qteplu) 
	double can;// qté ca annulé
	double cof;// qté ca offert
	double GTA; //Grand total période précédente mensuelle
	double GTE; // Grand total période précédente annuelle
	double GTP;	// Ancien Grand total perpétuel
	double GTZ;	// Grand total période en cours
	double GTX; // =(GTZ / 100) voir OnInitDialog ...utile dans la maj du GTP sur les anciennes versions
	double HGTZ;// GTZ de la periode issu de l'archive
	int etdate; // Flag de Dessin la date dans le demi cercle du bas sauf en écran config
/************ Variable billetterie  *********/

	int Nb_GTP;
	CTime Date_O;

/************ Variable billetterie  *********/
	DWORD ntou[100];
	double cas[100];
	double prix[100];
	double tva1[100];
	double tva2[100];
	double val1[100];
	double val2[100];
	int cscan[100]; //nb de scan
	int conso[100]; // nb item
	int perso[100]; // paramètres de l'article : perso[idx]=valentry+(valplace*2)+(valmix*4)+(valactif*8)+(valexo*0x10)+(valpass*0x1000)+ (cbx*0xff0000);
	int target[100]; // correspondance article <-> article ds fichier controle. Index n° touche ( voir ThreadEthernet)  
	int spectsel[100]; // 
	int choraire[100]; // horaire ou pas sur l'article
	int entrymode[100]; //  0=entree immédiate,1=prévente sans horaire,2=prévente avec horaire
	int ne[17]; // nb entrees scannees

	float oltou;
	float ltou;
	float eltou;
	float htou;
	float ehtou;
	float ohnum;

	float khto;
	float klto;
	float olto;
	float lto;
	float elto;
	float hto;
	float ohto;
	float ehto;
	float klnu;
	float khnu;
	float lnu;
	float elnu;
	float hnu;
	float ehnu;
	float olnu;
	float ohnu;
	float fversion;



	CString famim[3];	
	CString rubim[9];	
	CString certnum;	
	CString impmes;
	CString qtotal;
	CString serial;
	CString prefix;
	CString user;
	CString searchan;
	CString searchmois;
	CString	langue;
	CString	pays;
	CString pagejour;
	CString pag[20];
	CString jour[20];
	CString jourtxt[7];
	CString txtpage;
	CString licstat;
	CString licdate;
	CString licper;
	CString cash1;
	CString cash2;
	CString cash3;
	CString cash4;
	CString cash5; //valeur du total de la précédente période
	CString fileversion;
	CString workdir;
	CString archdir;
	CString placepath;
	CString driverfile;
	CString outpath;
	CString histpath;
	CString	codemanager;
	CString	codeadmin;
	CString	codeuser;
	CString	coderazadmin;
	CString	codereseller;
	CString	codeaudit;
	CString	configtext;
	CString	code;// dernier code utilisé
	CString dopen;		// date d'ouverture période
	CString dexer;		// date d'ouverture exercice
	CString exermois;		// date d'exercice
	CString appdir;
	CString appdirname;
	CString sysdir;
	CString opendir;// nom du repertoire de la periode en cours
	CString scantxt;
	CString datadir;
	CString backupdir;
	CString	securedir;
	CString skindir;
	CString updatedir;
	CString controldir;
	CString copyupdate;
	CString netcontdir;
	CString searchdir;
	CString langfile;
	CString cession;
	CString artim[100];
	CString	libel1[100];
	CString	libel2[100];
	CString	libelcons[100];
	CString	libelspect[100];
	CString	cdate[100];// date du controle 
	CString	cheure[100];// heure du controle
	CString scantemp;
	CString tempscan;
	CString scan;// pour affichage ligne sous le nom de la société (ecran de vente)
	CString	clibel1[100];
	CString	clibel2[100];
	CString	hlibel1[100];
	CString	hlibel2[100];
	CString	cfrom[100];
	CString cur;
	CString mentiont;
	CString mentionp;
	CString saudit;
	CString sticket;
	CString sgtticket;
	CString sgtpz;
	CString sgtpa;
	CString sarche;
	CString sarchp;
	CString sarchd;
	CString catfile;
	CString spart[10];// table des composants de la signature
	int ctot[100];// nombre de fichier Controle.dat par n° control
	int cselevt[100];

	int cdcmem;	// N° de sauvegarde du CDC printer

	CBrush ticketbrush;
	CBrush pagebrush;
	CBrush ntotalbrush;
	CBrush totalbrush;
	CBrush ticktitrebrush;
	CBrush backrefcolorbr;
	CBrush datebrush;
	CBrush groupbrush;
	CBrush lartbrush;

	CBitmap	titlebitmap;
	CBitmap	bmpimport;
	CBitmap	bmpexport;
	CBitmap	bmpquit;
	CBitmap	bmpraz;
	CBitmap	bmpprint;
	CBitmap	bmpinf;
	CBitmap	bmpsup;
	CBitmap	bmpdel;
	CBitmap	bmpart[15];
	CBitmap	bmpnum[14];
	CBitmap	bmparticle;
	CBitmap	bmpconfig;
	CBitmap	bmpcontrol;
	CBitmap	bmpresult;
	CBitmap	bmpcancel;
	CBitmap	bmpbur;
	CBitmap	bmpcashview;
	CBitmap	bmpcashclose;
	CBitmap	bmpimage;
	CBitmap	bmpmanager;
	CBitmap	bmpoffert;
	CBitmap	bmpmode;
	CBitmap* pcodebarre;
	CBitmap hphqr;
	CBitmap hctn;
	CBitmap hrdb;
	CBitmap hrdr;
	CBitmap hrdv;
	CBitmap hrdc;
	CBitmap hrgate;
	CBitmap hscanblue;
	CBitmap hscanusb;
	CBitmap hrdvert;
	CBitmap hrdred;
	CBitmap bmplogo;
	CBitmap bmpman;
	CBitmap hrnet;
	CBitmap hser;
	CBitmap haut;
	CBitmap hweb;

	COLORREF controlcolor;

	CString titretext;
	CString libelle;
	CString hcloture;
	CString hraz;
	CString houverture;
	CString codearticle;
	CString auditinfopath;
	CString tmpcb;
	CString libelsave;
	CString codartsave;
	CString savetxt;
	CString Table[14];
	CString calc;
	CString CodeBarre;
	CString nom;		// Nom du poste
	CString  memnom;	// Mémoire du nom du poste(sert sur esclave au changement par fichier article pris sur le maitre)
	CString adresse1;
	CString adresse2;
	CString siret;
	CString naf;
	CString poste;
	CString serveur;
	CString lic[7];
	CString fileupdate;
	CString TVA;
	CString cript[10];
	CString txtsntt;
	CString txtsnta;
	CString txtsca;
	CString txtsda;

	CFont hatart;
	CFont hatprxart;
	CFont geostat;
	CFont geotitre;
	CFont geodate;
	CFont geodateoc;
	CFont geoent;
	CFont geonum;
	CFont geopage;
	CFont ticketfont;
	CFont ticketentreefont;
	CFont combfont;
	CFont pagefont;
	CFont controlfont;
	CFont buttonfont;
	CFont buttoncontrolfont;
	CFont butcdefont;
	CFont titlefont;
	CFont butnumfont;
	CFont totalfont;
	CFont totaltitrefont;
	CFont scanfont;
	CFont boutnumfont;
// Données de boîte de dialogue
	enum { IDD = IDD_CONCERT_DIALOG };

// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV
public:
	CButton butentree;
	CButton butmanager;
	CButton butinf;
	CButton butsup;
	CButton butquitter;
	CButton breturn;
	CButton butraz;
	CButton b0;
	CButton bcancel;
	CButton butprint;
	CButton bcashview;
	CButton bcashclose;
	CButton bresult;
	CButton bart;
	CButton bconfig;
	CButton bcontrol;
	CButton bbur;
	CButton bplus;
	CButton bminus;
	CButton bpoub;
	CButton bimport;
	CButton boffert;
	CButton bdel;
	CButton bman;
	CButton buser;
	CButton blogo;
	CButton bprinter;
	CButton bnet;
	CButton bentrymode;
	CButton bcopy;
	CButton bpaste;

	CEdit slibel1;
	CEdit slibel2;
	CEdit slibelcons;
	CEdit snom;
	CEdit sserveur;
	CEdit sprefix;
	CEdit sad1;
	CEdit sad2;
	CEdit ssir;
	CEdit snaf;
	CEdit spect;
	CEdit guichet;
	CEdit slic0;
	CEdit slic1;
	CEdit slic2;
	CEdit slic3;
	CEdit slic4;
	CEdit slic5;
	CEdit slic6;
	CEdit smentiont;
	CEdit smentionp;
	CEdit sdum;

	CStatic sexer;
	CStatic nexer;
	CStatic wpage;
	CStatic nlibel;
	CStatic nlibelcons;
	CStatic ncons;
	CStatic npage;
	CStatic ndate;
	CStatic nprix;
	CStatic sprix;
	CStatic total;
	CStatic ntotal;
	CStatic ent1;
	CStatic ent2;
	CStatic ent3;
	CStatic ent4;
	CStatic sca;
	CStatic sda;
	CStatic sntt;
	CStatic snta;
	CStatic nposte;
	CStatic nserveur;
	CStatic nprefix;
	CStatic nnom;
	CStatic nad1;
	CStatic nad2;
	CStatic sposte;
	CStatic nlangue;
	CStatic npays;
	CStatic ndevise;
	CStatic nsir;
	CStatic nnaf;
	CStatic esea;
	CStatic sgl;
	CStatic sgc;
	CStatic sgs;
	CStatic sge;
	CStatic nnauto;
	CStatic npauto;
	CStatic nan;
	CStatic nmois;
	CStatic san;
	CStatic smois;
	CStatic scons;
	CStatic version;
	CStatic ntva1;
	CStatic stva1;
	CStatic sval1;
	CStatic ntva2;
	CStatic stva2;
	CStatic sval2;
	CStatic nspect;
	CStatic netc;
	CStatic nvhor;
	CStatic nvplace;
	CStatic nvmix;
	CStatic vplace;
	CStatic ventry;
	CStatic vexo;
	CStatic vcbx;
	CStatic vpass;
	CStatic vmix;
	CStatic vactif;
	//CStatic ctt;
	CStatic nvcontrol;
	CStatic tgate;		// Témoin connexion tourniquet bluetooth
	CStatic tcontrol;
	CStatic tnet;
	CStatic tweb;
	CStatic slangue;
	CStatic spays;
	CStatic sdevise;
	CStatic nlic;
	CStatic nmentiont;
	CStatic nmentionp;
	CStatic nscan;
	CStatic nvpwd;
	CStatic nvpage;
	CStatic av1;
	CStatic av2;
	CStatic av3;
	CStatic wqr;
	CStatic phqr;
	CStatic wtqr;

	CListBox ltva;
	CListBox sdl;
	CListBox rl;
	CListBox tl;
	CListBox sl;
	CListBox dl;
	CListBox pl;		// liste cachée code barre ETC
	CListBox llangue;	// liste chargé avec les langues
	CListBox lpays;		// liste chargé avec les pays
	CListBox lmois;		// liste chargé avec les mois
	CListBox ldevise;	// liste chargé avec les devises
	CListBox lmac;		// liste des billetteries en réseau
	CListBox lcode;		// liste de vente avec libellé article
	CListBox lqte;		// liste de vente avec quantité a vendre ou vendue
	CListBox lptot;		// liste de vente avec prix total de la ligne
	CListBox lntick;	// liste résultat N° du ticket
	CListBox ldate;		// liste résultat date de vente
	CListBox lprix;		// liste résultat prix de vente
	CListBox lcancel;	// liste résultat status annulé ou non
	CListBox lselevt;	// liste de controle
	CListBox dirlist;
	CListBox lna;
	CListBox ltmp;
	CListBox ltctl;
	CProgressCtrl pimp;
	CComboBox lnbap;	// Config nombre article/page
	CComboBox lcb;		// type code barre 
	CComboBox ltype;	// liste mode maitre/exclave/auto

public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnDClickedFam1();
	afx_msg void OnBnDClickedFam2();
	afx_msg void OnBnDClickedFam3();
	afx_msg void OnBnClickedFam1();
	afx_msg void OnBnClickedFam2();
	afx_msg void OnBnClickedFam3();
	afx_msg void OnBnClickedRub1();
	afx_msg void OnBnClickedRub2();
	afx_msg void OnBnClickedRub3();
	afx_msg void OnBnClickedArt1();
	afx_msg void OnBnClickedArt2();
	afx_msg void OnBnClickedArt3();
	afx_msg void OnBnClickedArt4();
	afx_msg void OnBnClickedArt5();
	afx_msg void OnBnClickedArt6();
	afx_msg void OnBnClickedArt7();
	afx_msg void OnBnClickedArt8();
	afx_msg void OnBnClickedArt9();
	afx_msg void OnBnClickedArt10();
	afx_msg void OnBnClickedArt11();
	afx_msg void OnBnClickedArt12();
	afx_msg void OnBnClickedArt13();
	afx_msg void OnBnClickedArt14();
	afx_msg void OnBnClickedArt15();
	afx_msg void OnBnClickedArt16();
	afx_msg void OnBnDClickedArt1();
	afx_msg void OnBnDClickedArt2();
	afx_msg void OnBnDClickedArt3();
	afx_msg void OnBnDClickedArt4();
	afx_msg void OnBnDClickedArt5();
	afx_msg void OnBnDClickedArt6();
	afx_msg void OnBnDClickedArt7();
	afx_msg void OnBnDClickedArt8();
	afx_msg void OnBnDClickedArt9();
	afx_msg void OnBnDClickedArt10();
	afx_msg void OnBnDClickedArt11();
	afx_msg void OnBnDClickedArt12();
	afx_msg void OnBnDClickedArt13();
	afx_msg void OnBnDClickedArt14();
	afx_msg void OnBnDClickedArt15();
	afx_msg void OnBnDClickedArt16();
	afx_msg void OnBnClickedManager();
	afx_msg void OnBnClickedTable();
	afx_msg void OnBnClickedMan();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedQuitter();
	afx_msg void OnBnClickedRetour();
	afx_msg void OnBnClickedInf();
	afx_msg void OnBnClickedSup();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClickedPM();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedEncaisser();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedLogo();
	afx_msg void OnBnClickedBcode();
	afx_msg void OnBnClickedBuser();
	afx_msg void OnBnClickedEntryMode();
	afx_msg void OnBnClickedControl();
	afx_msg void OnBnClickedRaz();
	afx_msg void OnStnClickedNdate();
	afx_msg void OnBnClickedCashClose();
	afx_msg void OnBnClickedCashView();
	afx_msg void OnBnClickedBilprint();
	afx_msg void OnBnClickedBilcancel();
	afx_msg void OnBnClickedBureau();
	afx_msg void OnBnClickedResult();
	afx_msg void OnBnClickedArticle();
	afx_msg void OnBnClickedConfig();
	afx_msg void OnBnClickedGlog();
	afx_msg void OnBnClickedBnet();
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedBprinter();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMoins();
	afx_msg void OnBnClickedPoubelle();
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedPaste();

	afx_msg void OnStnClickedVersion();
	afx_msg void OnStnClickedSearch();
	afx_msg void OnStnClickedSposte();
	afx_msg void OnStnClickedSan();
	afx_msg void OnStnClickedSmois();
	afx_msg void OnStnClickedPrix();
	afx_msg void OnStnClickedScons();
	afx_msg void OnStnClickedTva1();
	afx_msg void OnStnClickedTva2();
	afx_msg void OnStnClickedVal1();
	afx_msg void OnStnClickedVal2();
	afx_msg void OnStnClickedNvalcolor();
	afx_msg void OnStnClickedNpauto();
	afx_msg void OnStnClickedNnauto();
	afx_msg void OnStnClickedTemradio();
	afx_msg void OnStnClickedTemcontrol();
	afx_msg void OnStnClickedNvalhor();
	afx_msg void OnStnDblclickNan();
	afx_msg void OnStnClickedNvalplace();
	afx_msg void OnStnClickedValplace();
	afx_msg void OnStnClickedValmix();
	afx_msg void OnStnClickedValactif();
	afx_msg void OnStnClickedVexo();
	afx_msg void OnStnClickedVcbx();
	afx_msg void OnStnClickedVpass();
	afx_msg void OnStnClickedVentry();
	afx_msg void OnStnClickedPage();
	afx_msg void OnStnClickedNvalpwd();
	afx_msg void OnStnClickedNvalpage();
	afx_msg void OnStnClickedNvalmix();
	afx_msg void OnStnClickedNetc();
	afx_msg void OnStnClickedTotal();
	afx_msg void OnStnClickedSlangue();
	afx_msg void OnStnClickedSpays();
	afx_msg void OnStnClickedSdevise();
	afx_msg void OnStnClickedSexer();
	afx_msg void OnStnDblclickNdate();

	afx_msg void OnEnSetfocusSnom();
	afx_msg void OnEnSetfocusSserveur();
	afx_msg void OnEnSetfocusSprefix();
	afx_msg void OnEnSetfocusSad1();
	afx_msg void OnEnSetfocusSad2();
	afx_msg void OnEnSetfocusSsiret();
	afx_msg void OnEnSetfocusSnaf();
	afx_msg void OnEnSetfocusNlibel1();
	afx_msg void OnEnSetfocusLibelspect();
	afx_msg void OnEnSetfocusLibelcons();
	afx_msg void OnEnSetfocusSlicense0();
	afx_msg void OnEnSetfocusSlicense1();
	afx_msg void OnEnSetfocusSlicense2();
	afx_msg void OnEnSetfocusSlicense3();
	afx_msg void OnEnSetfocusSlicense4();
	afx_msg void OnEnSetfocusSlicense5();
	afx_msg void OnEnSetfocusSlicense6();
	afx_msg void OnEnSetfocusLibelguichet();
	afx_msg void OnEnSetfocusLibel1();
	afx_msg void OnEnSetfocusLibel2();
	afx_msg void OnEnSetfocusSmentiont();
	afx_msg void OnEnSetfocusSmentionp();
	afx_msg void OnEnMaxtextLibel1();

	afx_msg void OnLbnSelchangeCode();
	afx_msg void OnLbnSelchangeQte();
	afx_msg void OnLbnSelchangePtot();
	afx_msg void OnLbnKillfocusPtot();
	afx_msg void OnLbnSelchangeSelspect();
	afx_msg void OnLbnSelchangeLntick();
	afx_msg void OnLbnSelchangeLprix();
	afx_msg void OnLbnSelchangeLcancel();
	afx_msg void OnLbnSelchangeLdate();

	afx_msg void OnCbnSelchangeLnbap();
	afx_msg void OnCbnSelchangeLcb();
	afx_msg void OnCbnSelchangeLtype();

	afx_msg void OnClose();
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
unsigned __stdcall  WritePrinterThread(LPVOID lpParameter) ;  
unsigned __stdcall  ScanJobThread(LPVOID lpParameter) ;  
unsigned __stdcall  PrintJobThread(LPVOID lpParameter) ;  
DWORD WINAPI  RSGateReadThread(LPVOID lpParameter) ; 
DWORD WINAPI  RSReadThread(LPVOID lpParameter) ; 
DWORD WINAPI  RSSearchThread(LPVOID lpParameter) ;
unsigned __stdcall  RSScanThread(LPVOID lpParameter) ;
DWORD WINAPI  ImageScanThread(LPVOID lpParameter) ;
DWORD WINAPI  ArticleScanThread(LPVOID lpParameter) ;
DWORD WINAPI  ScanNetThread(LPVOID lpParameter) ;
DWORD WINAPI  ControlFileThread(LPVOID lpParameter) ;
DWORD WINAPI  BackupControlFileThread(LPVOID lpParameter) ;
DWORD WINAPI  RNThread(LPVOID lpParameter) ;
DWORD WINAPI  GetMCIModeThread(LPVOID lpParameter) ;// gére écran de veille et animation
