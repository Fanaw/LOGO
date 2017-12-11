#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct noeud
{
    char* instruction;
    int parametre;
    struct noeud* suivant;
}NOEUD;

typedef NOEUD* PROGRAMME;
/*
newNoeud permet de créer un nouveau noeud
@param instruction
@param parametre
@param suivant pointeur vers autre noeud
**/
NOEUD newNoeud(char* instruction, int parametre, NOEUD* suivant)
{
    NOEUD noeud;
    noeud.instruction=instruction;
    noeud.parametre=parametre;
    noeud.suivant=suivant;
    return noeud;
}


/*
newProgramme permet d'initialiser un programme
@param noeud le premier noeud
**/
PROGRAMME newProgramme(NOEUD noeud)
{
    PROGRAMME prog = (PROGRAMME)malloc(sizeof(NOEUD));
    prog->instruction=noeud.instruction;
    prog->parametre=noeud.parametre;
    prog->suivant=noeud.suivant;
    return prog;
}

/*
ajoutNoeud permet d'ajouter tableau de noeuds à la fin d'un programme
@param pprog pointeur vers programme
@param noeud un tableau de noeuds
**/
PROGRAMME ajoutNoeud(PROGRAMME* pprog, NOEUD* noeud)
{
    if(*pprog==NULL)
    {
        return NULL;
    }
    if((*pprog)->suivant!=NULL)
    {
        printf("yo\n");
        return ajoutNoeud(&((*pprog)->suivant),noeud);   
    }else{
        printf("yep\n");
        (*pprog)->suivant=noeud;
        return *pprog;
    }

}
/*
newNoeudRepeat permet de créer un noeud REPEAT (suite de noeuds)
@param instruction 
@param parametre
@param tabNoeud tableau de noeuds 
**/
PROGRAMME newNoeudRepeat(char* instruction, int parametre, NOEUD* tabNoeud){
    if(strcmp(instruction,"REPEAT")!=0)
    {
    perror("Instruction n'est pas \"REPEAT\" \n");
    return NULL;
    }

    PROGRAMME prog;
    if(tabNoeud!=NULL)
    {
        prog = newProgramme(tabNoeud[0]);
        int i=1;
        for(i;i<parametre;i++)
        {
            printf("%d\n",i);
            prog=ajoutNoeud(&prog,tabNoeud+i);
            
        }
    }
    return prog;
}

/*
ajoutProgramme permet de fusionner le programme b à la suite du programme a
@param pproga pointeur vers programme a
@param progb programme b
**/
PROGRAMME ajoutProgramme(PROGRAMME* pproga, PROGRAMME progb)
{
    if(*pproga==NULL || progb==NULL)
    {
        perror("Erreur fusion programme");
        return NULL;
    }

    if((*pproga)->suivant!=NULL)
    {
        perror("hello");
        return ajoutProgramme(&(*pproga)->suivant,progb);
    }else
    {
        (*pproga)->suivant=progb;
        return *pproga;
    }
}
/*
afficheProg affiche l'instruction et le parametre d'un noeud dans une programme
@param prog un programme
**/
void afficheProg(PROGRAMME prog)
{
    if(prog != NULL)
    {
        printf("%s ",prog->instruction);
        printf("%d\n",prog->parametre);
        if(prog->suivant!=NULL)
        {
            afficheProg(prog->suivant);
        }
    }
}

int main() 
{
    //création de noeuds
    NOEUD noeuda = newNoeud("FORWARD",15,NULL);
    NOEUD noeudb = newNoeud("BACKWARD",50,NULL);
    
    //création du programme
    PROGRAMME prog = newProgramme(noeuda);
    
    //ajout noeud
    prog = ajoutNoeud(&prog, &noeudb);
    
    //affichage
    afficheProg(prog);
    
    //création noeud REPEAT
    PROGRAMME repeat = newNoeudRepeat("REPEAT",2,prog);
    
    //ajout noeud REPEAT
    prog=ajoutProgramme(&prog,repeat);
    
    //affiche
    afficheProg(prog);
    
    //free malloc
    free(prog);

    return 1;
}