#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAILLESTRUCT 30
#define TAILLENOM 25
#define TAILLEPRENOM 30
#define AUTRETAILLE 20
#define TAILLEDATE 11
#define TAILLERUE 50

typedef struct
{
    short jour;
    short mois;
    short annee;
}Date;

typedef struct
{
    long NumRegistre;
    char Nom [TAILLENOM];
    char Prenom[TAILLEPRENOM];
    char Rue[TAILLERUE];
    int CodePostal;
    char Ville[AUTRETAILLE];
    char Specialite[AUTRETAILLE];
    Date DateNaissance;
    Date DateEngagement;
}Ouvriers;

typedef struct
{
    long RegistreNational;
    char Nom [TAILLENOM];
    char Prenom[TAILLEPRENOM];
    short position;
}Index;

void AjoutOuvriers(Index *,Ouvriers *,short);
void ModifOuvriers(Index *,Ouvriers *);
void SupprOuvriers(Index *,Ouvriers *);
void AffichageIndex(Index *,short);
void InitIndex(Index *,short);
void Tri_Index(Index *,short);
short RechercheOuvrier(Index *,short);
void LireChaine(char *,short);
void SaisiDate(Date *);
void SaisiSpecialite(char *);

int main()
{
    Ouvriers enregistrements[TAILLESTRUCT];
    Ouvriers *pEnregistrements;
    Index indexation[TAILLESTRUCT];
    Index *pIndexation;
    short choix=0;
    short continuer=1;
    pIndexation=&indexation[0];
    InitIndex(pIndexation,TAILLESTRUCT);

    while(continuer==1)
    {
        do
        {
            printf("\nQuelle operation souhaitez-vous realiser?\n");
            printf("\nPour ajouter un ouvrier, tapez sur 1.\n");
            printf("\nPour modifier un ouvrier, tapez sur 2.\n");
            printf("\nPour supprimer un ouvrier, tapez sur 3.\n");
            printf("\nPour afficher vos ouvirers, tapez sur 4.\n");
            printf("\nPour quitter le programme, tapez sur 5.\n");
            printf("\nFaites votre choix :\n");
            fflush(stdin);
            scanf("%hd",&choix);
        }
        while(choix<=0 || choix>5);

        switch(choix)
        {
            case 1:
            {
                pIndexation=&indexation[0];
                pEnregistrements=&enregistrements[0];
                AjoutOuvriers(pIndexation,pEnregistrements,TAILLESTRUCT);
            }
            break;

            case 2:
            {
                pIndexation=&indexation[0];
                pEnregistrements=&enregistrements[0];
                ModifOuvriers(pIndexation,pEnregistrements);
            }
            break;

            case 3:
            {
                pIndexation=&indexation[0];
                pEnregistrements=&enregistrements[0];
                SupprOuvriers(pIndexation,pEnregistrements);
            }
            break;

            case 4:
            {
                AffichageIndex(pIndexation,TAILLESTRUCT);
            }
            break;

            case 5:
            {
                continuer=0;
            }
            break;
        }
    }

    return 0;
}

/*

INPUT : Pointeurs des structures Index et Ouvriers + taille maximales de celles-ci

PROCESS : Ajout d'un ouvrier par l'utilisateur dans l'index puis dans la structure Ouvriers

OUTPUT : /

*/

void AjoutOuvriers(Index *pI,Ouvriers *pE,short limite)
{
    short i=0;
    short saisi=0;
    char chaine[TAILLENOM];

    while(i<limite && saisi==0)
    {
        if(pI->RegistreNational==-1)
        {
            printf("\nVeuillez saisir le nom de l'ouvrier.\n");
            printf("\nCe dernier doit etre compose seulement de lettres et sa taille maximale doit etre de 29 :\n");
            LireChaine(chaine,TAILLENOM);
            strcpy(pI->Nom,chaine);

            printf("\nVeuillez saisir le prenom de l'ouvrier.\n");
            printf("\nCe dernier doit etre compose seulement de lettres et sa taille maximale doit etre de 24 :\n");
            LireChaine(chaine,TAILLEPRENOM);
            strcpy(pI->Prenom,chaine);

            printf("\nVeuillez saisir le numero de registre national de l'ouvrier :\n");
            fflush(stdin);
            scanf("%ld",(&pI->RegistreNational));

            pE=pE+pI->position;
            strcpy(pE->Nom,pI->Nom);
            strcpy(pE->Prenom,pI->Prenom);
            pE->NumRegistre=pI->RegistreNational;

            printf("\nVeuillez entrer la rue de l'ouvrier.\n");
            printf("\nCette derniere doit seulement contenir des lettres et sa taille maximale vaut 49 :\n");
            LireChaine(chaine,TAILLERUE);
            strcpy(pE->Rue,chaine);

            do
            {
                printf("\nVeuillez entrer le code postal de l'ouvrier.\n");
                printf("\nCe dernier doit etre compose de quatre chiffre :\n");
                fflush(stdin);
                scanf("%d",(&pE->CodePostal));
            }
            while(pE->CodePostal<1000 || pE->CodePostal>9999);

            printf("\nVeuillez saisir la localite de l'ouvrier.\n");

            printf("\nCette derniere doit etre compose seulement de lettres et sa taille maximale doit etre de 19 :\n");

            LireChaine(chaine,AUTRETAILLE);

            strcpy(pE->Ville,chaine);

            printf("\nVeuillez entrer la specialite de l'ouvrier :\n");

            SaisiSpecialite(pE->Specialite);

            printf("\nVeuillez entrer la date de naissance de l'ouvrier.\n");

            printf("\nLa saisi doit se faire sous le format suivant : JJ/MM/AAAA.\n");

            SaisiDate(&pE->DateNaissance);

            do
            {
                printf("\nVeuillez entrer la date d'engagement de l'ouvrier.\n");

                printf("\nLa saisi doit se faire sous le format suivant : JJ/MM/AAAA.\n");

                printf("\nDe plus, cette derniere doit etre posterieur a votre date de naissance d'au moins 18 ans.\n");

                SaisiDate(&pE->DateEngagement);
            }
            while((pE->DateNaissance.annee+18)>pE->DateEngagement.annee);

            saisi=1;

            printf("\nVotre ouvrier a bien ete ajoute a notre index et notre structure!\n");
        }
        else
        {
            pI++;
            i++;
        }
    }

    if(i==limite)
    {
        printf("\nNous ne pouvons plus ajouter d'utilisateur. La taille maximale a ete atteinte.\n");
    }
}

/*

INPUT : Pointeurs des structures Index et Ouvriers

PROCESS : Modification d'un ouvrier par l'utilisateur dans l'index puis dans la structure Ouvriers

OUTPUT : /

*/

void ModifOuvriers(Index *pI,Ouvriers *pE)
{
    short retour=-1;

    char chaine[TAILLENOM];

    retour=RechercheOuvrier(pI,TAILLESTRUCT);

    if(retour>=0)
    {
        pI=pI+retour;

        printf("\nVeuillez entrer le nouveau nom de l'ouvrier.\n");

        printf("\nCe dernier doit etre compose seulement de lettres et sa taille maximale doit etre de 29 :\n");

        LireChaine(chaine,TAILLENOM);

        strcpy(pI->Nom,chaine);

        printf("\nVeuillez entrer le nouveau prenom de l'ouvrier.\n");

        printf("\nCe dernier doit etre compose seulement de lettres et sa taille maximale doit etre de 24 :\n");

        LireChaine(chaine,TAILLEPRENOM);

        strcpy(pI->Prenom,chaine);

        printf("\nVeuillez entrer le nouveau numero de registre national de l'ouvrier :\n");

        fflush(stdin);

        scanf("%ld",&pI->RegistreNational);

        pE=pE+pI->position;

        strcpy(pE->Nom,pI->Nom);

        strcpy(pE->Prenom,pI->Prenom);

        pE->NumRegistre=pI->RegistreNational;

        printf("\nVeuillez entrer la nouvelle rue de l'ouvrier\n");

        printf("\nCette derniere doit seulement contenir des lettres et sa taille maximale vaut 49 :\n");

        LireChaine(chaine,TAILLERUE);

        strcpy(pE->Rue,chaine);

        do
        {
            printf("\nVeuillez entrer le nouveau code postal de l'ouvrier.\n");

            printf("\nCe dernier doit etre compose de quatre chiffre :\n");

            fflush(stdin);

            scanf("%d",(&pE->CodePostal));
        }
        while(pE->CodePostal<1000 || pE->CodePostal>9999);

        printf("\nVeuillez saisir la nouvelle localite de l'ouvrier.\n");

        printf("\nCette derniere doit etre compose seulement de lettres et sa taille maximale doit etre de 19 :\n");

        LireChaine(chaine,AUTRETAILLE);

        strcpy(pE->Ville,chaine);

        printf("\nVeuillez entrer la nouvelle specialite de l'ouvrier :\n");

        SaisiSpecialite(pE->Specialite);

        printf("\nVeuillez entrer la nouvelle date de naissance de l'ouvrier.\n");

        printf("\nLa saisi doit se faire sous le format suivant : JJ/MM/AAAA :\n");

        SaisiDate(&pE->DateNaissance);

        do
        {
            printf("\nVeuillez entrer la nouvelle date d'engagement de l'ouvrier.\n");

            printf("\nLa saisi doit se faire sous le format suivant : JJ/MM/AAAA.\n");

            printf("\nCette derniere doit etre posterieur a votre date de naissance d'au moins 18 ans.\n");

            SaisiDate(&pE->DateEngagement);
        }
        while((pE->DateNaissance.annee+18)>=pE->DateEngagement.annee);

        printf("\nVotre ouvrier a bien ete modifie!\n");
    }
    else
    {
        printf("\nNous n'avons pas trouve votre ouvrier.\n");
    }
}

/*

INPUT : Pointeurs des structures Index et Ouvriers

PROCESS : Suppression d'un ouvrier par l'utilisateur

OUTPUT : /

*/

void SupprOuvriers(Index *pI,Ouvriers *pE)
{
    short retour=-1;

    short confirmation=0;

    retour=RechercheOuvrier(pI,TAILLESTRUCT);

    if(retour>=0)
    {
        pI=pI+retour;

        pE=pE+pI->position;

        printf("\nVoici votre ouvrier :\n");

        printf("\nVoici son nom :\n");

        printf("%s",(pI->Nom));

        printf("\nVoici son prenom :\n");

        printf("%s",(pI->Prenom));

        printf("\nVoici son identifiant :\n");

        printf("%ld",(pE->NumRegistre));

        printf("\nVoici sa specialite :\n");

        printf("%s",pE->Specialite);

        printf("\nVoici sa rue :\n");

        printf("%s",(pE->Rue));

        printf("\nVoici sa localite :\n");

        printf("%s",(pE->Ville));

        printf("\nVoici sa date de naissance :\n");

        printf("%d/%d/%d",pE->DateNaissance.jour,pE->DateNaissance.mois,pE->DateNaissance.annee);

        printf("\nVoici sa date d'engagement :\n");

        printf("%d/%d/%d",pE->DateEngagement.jour,pE->DateEngagement.mois,pE->DateEngagement.annee);

        do
        {
            printf("\nEtes-vous sur de vouloir de supprimer?\n");

            printf("\nSi vous ne voulez pas le supprimer, tapez sur 0.\n");

            printf("\nSi vous voulez le supprimer, tapez sur 1.\n");

            printf("\nFaites votre choix :\n");

            fflush(stdin);

            scanf("%hd",&confirmation);
        }
        while(confirmation!=0 && confirmation!=1);

        switch(confirmation)
        {
            case 0 :
            {
                printf("\nNous n'avons pas supprimer votre ouvrier.\n");
            }
            break;

            case 1 :
            {
                pI->RegistreNational=-1;

                pE->NumRegistre=-1;

                printf("\nVotre ouvrier a bien ete supprime!\n");
            }
            break;
        }
    }
    else
    {
        printf("\nNous n'avons pas trouve votre ouvrier.\n");
    }
}

/*

INPUT : Pointeur de la structure Index + taille max de celle-ci

PROCESS : Affichage de l'index

OUTPUT : /

*/

void AffichageIndex(Index *pI,short limite)
{
    short i=0;

    Tri_Index(pI,TAILLESTRUCT);

    while(i<limite)
    {

        printf("\nVoici votre ouvriers %hd :\n",(i+1));

        printf("\nVoici son nom :\n");

        printf("%s",(pI->Nom));

        printf("\nVoici son prenom :\n");

        printf("%s",(pI->Prenom));

        printf("\nVoici son identifiant :\n");

        printf("%ld",(pI->RegistreNational));

        printf("\nVoici sa position dans la structure :\n");

        printf("%hd",pI->position);

        i++;

        pI++;
    }
}

/*

INPUT : Pointeur de la structure Index + taille max de celle-ci

PROCESS : Initialisation de la structure Index avec les différentes positions de la structure Ouvriers +

on met l'identifiant à -1

OUTPUT : /

*/

void InitIndex(Index *pI,short limite)
{
    short i=0;

    while(i<limite)
    {
        pI->RegistreNational=-1;

        pI->position=i;

        i++;

        pI++;
    }
}

/*

INPUT : Pointeur de la structure Index + taille maximale de celle-ci

PROCESS : Tri l'index par ordre croissant sur le nom et le prénom de l'ouvrier

OUTPUT : /

*/

void Tri_Index(Index *pI, short limite)
{
    Index temp;

    short i,j;

    for(i = 0; i < limite-1; i++)
    {
        for(j = 0; j < limite-i-1 && pI[j+1].RegistreNational!=-1; j++)
        {
            if(strcmp(pI[j].Nom, pI[j+1].Nom) > 0 || (strcmp(pI[j].Nom, pI[j+1].Nom) == 0 && strcmp(pI[j].Prenom, pI[j+1].Prenom) > 0))
            {
                temp = pI[j];
                pI[j] = pI[j+1];
                pI[j+1] = temp;
            }
        }
    }
}

/*

INPUT : Pointeur de la structure Index + taille max de celle-ci

PROCESS : Recherche d'un ouvrier lient sur base du nom et du prenom de ce dernier

OUTPUT : On renvoie la position à laquelle se trouve l'enregistrement sinon on renvoie -1

*/

short RechercheOuvrier(Index *pI,short limite)
{
    short i=0;

    short position=-1;

    char nomTmp[TAILLENOM],prenomTmp[TAILLEPRENOM];

    printf("Entrez le nom de la personne a rechercher :\n");

    LireChaine(nomTmp,TAILLENOM);

    printf("Entrez le prenom de la personne a rechercher :\n");

    LireChaine(prenomTmp,TAILLEPRENOM);

    while(i<limite && position==-1)
    {
        if(strcmp(pI->Nom,nomTmp)==0 && strcmp(pI->Prenom,prenomTmp)==0)
        {
            position=i;
        }

        pI++;

        i++;
    }

    return(position);
}

/*

INPUT : Pointeur de la chaîne de caractères + taille max de celle-ci

PROCESS : Saisi d'une chaîne de caractères par l'utilisateur + mises en majuscules des bonnes lettres

OUTPUT : /

*/

void LireChaine(char *pSaisi,short limite)
{
    short i=0;

    short chainevalide=0;

    char *pTmp=pSaisi;

    while(chainevalide==0)
    {

        pSaisi=pTmp;

        fflush(stdin);

        (*pSaisi)=getchar();

        while(i<(limite-1) && (*pSaisi)!='\n')
        {
            pSaisi++;

            i++;

            (*pSaisi)=getchar();
        }

        (*pSaisi)='\0';

        pSaisi=pTmp;

        chainevalide=1;

        while((*pSaisi)!='\0' && chainevalide==1)
        {
            if(((*pSaisi)<'A' || (*pSaisi)>'Z') && ((*pSaisi)<'a' || (*pSaisi)>'z') && (*pSaisi)!=' ')
            {
                chainevalide=0;

                printf("\nNous avons trouve un caractere non accepte!\n");

                printf("\nVeuillez recommencer la saisi :\n");
            }
            else
            {
                pSaisi++;
            }
        }
    }

    if(chainevalide!=0)
    {
        pSaisi=pTmp;

        (*pSaisi)=toupper(*pSaisi);

        pSaisi++;

        while((*pSaisi)!='\0')
        {
            if((*pSaisi)==' ')
            {
                (*(pSaisi+1))=toupper((*(pSaisi+1)));

                pSaisi++;
            }
            else
            {
                (*pSaisi)=tolower(*pSaisi);
            }

            pSaisi++;

        }
    }
}

/*

INPUT : Pointeur de la date
PROCESS : Saisi de la date au format JJ/MM/AAAA par l'utilisateur + vérification de la validité de celle-ci
OUTPUT : /
*/
void SaisiDate(Date *pD)
{
    char Saisi[TAILLEDATE];

    char *pSaisi;

    char *token;

    short i;

    short datevalide=0;

    while(datevalide==0)
    {
        pSaisi=&Saisi[0];

        i=0;

        fflush(stdin);

        (*pSaisi)=getchar();

        while(i<(TAILLEDATE-1) && (*pSaisi)!='\n')
        {
            pSaisi++;

            i++;

            (*pSaisi)=getchar();
        }

        (*pSaisi)='\0';

        pSaisi=&Saisi[0];

        if(strlen(pSaisi)==10)
        {
            if(*(pSaisi+2)=='/' && *(pSaisi+5)=='/')
            {
                pSaisi=&Saisi[0];

                token = strtok(pSaisi,"/");

                i = 0;

                while(token!=NULL)
                {
                    if(i==0)
                    {
                        pD->jour = atoi(token);
                    }

                    if(i==1)
                    {
                       pD->mois = atoi(token);
                    }
                    if(i==2)
                    {
                       pD->annee = atoi(token);
                    }

                    token = strtok (NULL,"/");

                    i++;
                }
            }
            else
            {
                if(*(pSaisi+2) != '/')
                {
                    printf("\nFormat du champ incorect...Le caractere '%c' doit etre un '/'", *(pSaisi+2));

                    printf("\nVeuillez recommencer la saisi :\n");

                    datevalide=0;
                }
                else
                {
                    printf("\nFormat du champ incorect...Le caractere '%c' doit etre un '/'", *(pSaisi+5));

                    printf("\nVeuillez recommencer la saisi :\n");

                    datevalide=0;
                }
            }
        }
        else
        {
            printf("\nLa taille de votre chaine est trop petite, veuillez ressayer...\n");

            printf("\nElle doit comprendre 10 caracteres en tout.\n");

            printf("\nVeuillez recommencer la saisi :\n");

            datevalide=0;
        }

        if (pD->annee>=1957 && pD->annee<=2022)
        {
            switch (pD->mois)
            {
                case 4: case 6: case 9: case 11:
                {
                    if ((pD->jour>=1)&&(pD->jour<=30))
                    {
                        datevalide=1;
                    }
                    else
                    {
                        printf("\nLe jour que vous avez entre est invalide, veuillez reessayer.\n");

                        printf("Il doit etre compris entre 1 et 31.\n");

                        printf("\nVeuillez recommencer la saisi :\n");

                        datevalide=0;
                    }
                }
                break;

                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                {
                    if ((pD->jour>=1)&&(pD->jour<=31))
                    {
                        datevalide=1;
                    }
                    else
                    {
                        printf("\nLe jour que vous avez entre est invalide, veuillez reessayer.\n");

                        printf("Il doit etre compris entre 1 et 31.\n");

                        printf("\nVeuillez recommencer la saisi :\n");

                        datevalide=0;
                    }
                }
                break;

                case 2:
                {
                    if (pD->annee%4==0)
                    {
                        if(pD->annee%400==0)
                        {
                            if((pD->jour>=1)&&(pD->jour<=29))
                            {
                                datevalide=1;
                            }
                            else
                            {
                                printf("\nLe jour que vous avez entre est invalide, veuillez reessayer.\n");

                                printf("Il doit etre compris entre 1 et 29.\n");

                                printf("\nVeuillez recommencer la saisi :\n");

                                datevalide=0;
                            }
                        }
                        else
                        {
                            if((pD->jour>=1)&&(pD->jour<=28))
                            {
                                datevalide=1;
                            }
                            else
                            {
                                printf("\nLe jour que vous avez entre est invalide, veuillez reessayer.\n");

                                printf("Il doit etre compris entre 1 et 28.\n");

                                printf("\nVeuillez recommencer la saisi :\n");

                                datevalide=0;
                            }
                        }
                    }
                    else
                    {
                        if((pD->jour>=1)&&(pD->jour<=28))
                        {
                            datevalide=1;
                        }
                        else
                        {
                            printf("\nLe jour que vous avez entre est invalide, veuillez reessayer.\n");

                            printf("Il doit etre compris entre 1 et 28.\n");

                            printf("\nVeuillez recommencer la saisi :\n");

                            datevalide=0;
                        }
                    }
                    break;

                    default:
                    {
                        printf("\nLe mois que vous avez entre est invalide, veuillez reessayer.\n");

                        printf("Il doit etre compris entre 1 et 12.\n");

                        printf("\nVeuillez recommencer la saisi :\n");

                        datevalide=0;
                    }
                    break;
                }
            }
        }
        else
        {
            printf("\nL'annee que vous avez entree est invalide, veuillez reessayer.\n");

            printf("Elle doit etre comprise entre 1957 et 2022.\n");

            printf("\nVeuillez recommencer la saisi :\n");

            datevalide=0;
        }
    }
}

/*

INPUT : Pointeur pour la spécialité de l'ouvrier

PROCESS : Initialisation de la spécialité par l'utilisateur

OUTPUT : /

*/

void SaisiSpecialite(char *pSaisi)
{
    short choix=0;

    do
    {

        printf("\nTapez sur 1, s'il est coffreur.\n");

        printf("\nTapez sur 2, s'il est couvreur.\n");

        printf("\nTapez sur 3, s'il est ferrailleur.\n");

        printf("\nTapez sur 4, s'il est grutier.\n");

        printf("\nTapez sur 5, s'il est macon.\n");

        printf("\nTapez sur 6, s'il s'occupe des manoeuvres.\n");

        printf("\nTapez sur 7, s'il est menusier.\n");

        fflush(stdin);

        scanf("%hd",&choix);

    }
    while(choix<=0 || choix>7);

    switch(choix)
    {
        case 1:
        {
            strcpy(pSaisi,"Coffreur");
        }
        break;

        case 2:
        {
            strcpy(pSaisi,"Couvreur");
        }
        break;

        case 3:
        {
            strcpy(pSaisi,"Ferrailleur");
        }
        break;

        case 4:
        {
            strcpy(pSaisi,"Grutier");
        }
        break;

        case 5:
        {
            strcpy(pSaisi,"Macon");
        }
        break;

        case 6:
        {
            strcpy(pSaisi,"Manoeuvre");
        }
        break;

        case 7:
        {
            strcpy(pSaisi,"Menusier");
        }
        break;
    }
}
