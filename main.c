#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void AffichageStruct(Ouvriers *,short);

void InitIndex(Index *,short);

short RechercheOuvrier(Index *,short);

void LireChaine(char *,short);

void SaisiDate(Date *);

void SaisiSpecialite(char *);

void SaisiRue(char *,short);

int main()
{
    Ouvriers enregistrements[TAILLESTRUCT];

    Ouvriers *pEnregistrements;

    Index indexation[TAILLESTRUCT];

    Index *pIndexation;

    short choix=0;

    short continuer=0;

    pIndexation=&indexation[0];

    InitIndex(pIndexation,TAILLESTRUCT);

    do
    {
        do
        {
            printf("\nQuelle operation souhaitez-vous realiser?\n");

            printf("\nPour ajouter un ouvrier, tapez sur 1.\n");

            printf("\nPour modifier un ouvrier, tapez sur 2.\n");

            printf("\nPour supprimer un ouvrier, tapez sur 3.\n");

            printf("\nPour afficher vos ouvirers, tapez sur 4.\n");

            printf("\nPour afficher la structure, tapez sur 5.\n");

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
                AffichageStruct(pEnregistrements,TAILLESTRUCT);
            }
            break;
        }

        do
        {
            printf("\nSouhaitez-vous continuer les operations?\n");

            printf("\nSi vous souhaitez continuer, tapez sur 0.\n");

            printf("\nSi vous souhaitez arreter, tapez sur un autre chiffre.\n");

            printf("\nFaites votre choix :\n");

            fflush(stdin);

            scanf("%hd",&continuer);
        }
        while(continuer<0);
    }
    while(continuer==0 || continuer!=1);

    return 0;
}

/*

INPUT : Pointeurs des structures Index et Ouvriers + taille max de celles-ci

PROCESS : Ajout d'un client par l'utilisateur

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

            printf("\nVeuillez saisir l'identifiant de l'ouvrier :\n");

            fflush(stdin);

            scanf("%ld",(&pI->RegistreNational));

            pE=pE+pI->position;

            strcpy(pE->Nom,pI->Nom);

            strcpy(pE->Prenom,pI->Prenom);

            pE->NumRegistre=pI->RegistreNational;

            printf("\nVeuillez entrer la rue de l'ouvrier :\n");

            SaisiRue(chaine,TAILLERUE);

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


            do
            {
                printf("\nVeuillez entrer la date de naissance de l'ouvrier.\n");

                SaisiDate(&pE->DateNaissance);

                printf("\nVeuillez entrer la date d'engagement de l'ouvrier.\n");

                printf("\nDe plus, cette derniere doit etre posterieur a votre date de naissance.\n");

                SaisiDate(&pE->DateEngagement);
            }
            while(pE->DateNaissance.annee>=pE->DateEngagement.annee);

            saisi=1;

            printf("\nVotre patient a bien ete ajoute a notre index et notre structure!\n");
        }
        else
        {
            pI++;

            i++;
        }
    }
}

/*

INPUT : Pointeurs des structures Index et Ouvriers + taille max de celles-ci

PROCESS : Modification d'un client par l'utilisateur

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

        printf("\nVeuillez entrer la nouvelle rue de l'ouvrier :\n");

        SaisiRue(chaine,TAILLERUE);

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

        do
        {
            printf("\nVeuillez entrer la nouvelle date de naissance de l'ouvrier.\n");

            SaisiDate(&pE->DateNaissance);

            printf("\nVeuillez entrer la nouvelle date d'engagement de l'ouvrier.\n");

            printf("\nCette derniere doit etre posterieur a votre date de naissance.\n");

            SaisiDate(&pE->DateEngagement);
        }
        while(pE->DateNaissance.annee>=pE->DateEngagement.annee);

        printf("\nVotre ouvrier a bien ete modifie!\n");
    }
    else
    {
        printf("\nNous n'avons pas trouve votre ouvrier.\n");
    }
}

/*

INPUT : Pointeurs des structures Index et Ouvriers + taille max de celles-ci

PROCESS : Suppression d'un client par l'utilisateur

OUTPUT : /

*/

void SupprOuvriers(Index *pI,Ouvriers *pE)
{
    short retour=-1;

    retour=RechercheOuvrier(pI,TAILLESTRUCT);

    if(retour>=0)
    {
        pI=pI+retour;

        pI->RegistreNational=-1;

        pE=pE+pI->position;

        pE->NumRegistre=-1;

        printf("\nVotre ouvrier a bien ete supprime!\n");
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

/////////////////////////////////////////////////////////////////

void AffichageStruct(Ouvriers *pI,short limite)
{
    short i=0;

    while(i<limite)
    {

        printf("\nVoici votre ouvriers %hd :\n",(i+1));

        printf("\nVoici son nom :\n");

        printf("%s",(pI->Nom));

        printf("\nVoici son prenom :\n");

        printf("%s",(pI->Prenom));

        printf("\nVoici son identifiant :\n");

        printf("%ld",(pI->NumRegistre));

        printf("\nVoici sa specialite :\n");

        printf("%s",pI->Specialite);

        printf("\nVoici sa date de naissance :\n");

        printf("%d/%d/%d",pI->DateNaissance.jour,pI->DateNaissance.mois,pI->DateNaissance.annee);

        printf("\nVoici sa date d'engagement :\n");

        printf("%d/%d/%d",pI->DateEngagement.jour,pI->DateEngagement.mois,pI->DateEngagement.annee);

        i++;

        pI++;

    }
}

/////////////////////////////////////////////////////////////////////////////

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

INPUT : Pointeurs de la structure Index + taille max de celle-ci

PROCESS : Recherche d'un client sur base du nom et du prenom du client

OUTPUT : On renvoie la position à laquelle se trouve l'enregistrement

*/

short RechercheOuvrier(Index *pI,short limite)
{
    short i=0;

    short position=-1;

    char chaine[TAILLENOM];

    char nomTmp[TAILLENOM];

    printf("Entrez le nom de la personne a chercher :\n");

    LireChaine(chaine,TAILLENOM);

    strcpy(nomTmp,chaine);

    while(i<limite && position==-1)
    {
        if(strcmp(pI->Nom,nomTmp)==0)
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

PROCESS : Saisi d'une chaîne de caractères par l'utilisateur

OUTPUT : /

*/

void LireChaine(char *pSaisi,short limite)
{
    short i=0;

    fflush(stdin);

    (*pSaisi)=getchar();

    while(i<(limite-1) && (*pSaisi)!='\n')
    {
        pSaisi++;

        i++;

        (*pSaisi)=getchar();
    }
}

/*

INPUT : Pointeur de la date

PROCESS : Saisi de la date au format JJ/MM/AAAA par l'utilisateur

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

        printf("\nCelle-ci doit etre encodez sous le format suivant : JJ/MM/AAAA.\n");

        printf("\nVeuillez encoder la date.\n");

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

                    datevalide=0;
                }
                else
                {
                    printf("\nFormat du champ incorect...Le caractere '%c' doit etre un '/'", *(pSaisi+5));

                    datevalide=0;
                }

            }
        }
        else
        {
            printf("\nLa taille de votre chaine est trop petite, veuillez ressayer...\n");

            printf("\nElle doit comprendre 10 caracteres en tout.\n");

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

                            datevalide=0;
                        }
                    }
                    break;

                    default:
                    {
                        printf("\nLe mois que vous avez entre est invalide, veuillez reessayer.\n");

                        printf("Il doit etre compris entre 1 et 12.\n");

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
        printf("\nVeuillez entrer votre specialite de l'ouvrier :\n");

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

/*

INPUT : Pointeur pour la rue + taille maximale de celle-ci

PROCESS : Initialisation de la rue + du numéro de rue de l'ouvrier

OUTPUT : /

*/

void SaisiRue(char *pSaisi,short limite)
{
    short i=0;

    fflush(stdin);

    (*pSaisi)=getchar();

    while(i<(limite-1) && (*pSaisi)!='\n')
    {
        pSaisi++;

        i++;

        (*pSaisi)=getchar();
    }
}
