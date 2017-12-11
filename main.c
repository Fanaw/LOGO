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

NOEUD newNoeud(char* instruction, int parametre, NOEUD* suivant)
{
    NOEUD noeud;
    noeud.instruction=instruction;
    noeud.parametre=parametre;
    noeud.suivant=suivant;
    return noeud;
}



PROGRAMME newProgramme(NOEUD noeud)
{
    PROGRAMME prog = (PROGRAMME)malloc(sizeof(NOEUD));
    prog->instruction=noeud.instruction;
    prog->parametre=noeud.parametre;
    prog->suivant=noeud.suivant;
    return prog;
}

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
    NOEUD noeuda = newNoeud("FORWARD",15,NULL);
    NOEUD noeudb = newNoeud("BACKWARD",50,NULL);
    PROGRAMME prog = newProgramme(noeuda);
    prog = ajoutNoeud(&prog, &noeudb);
    afficheProg(prog);
    PROGRAMME repeat = newNoeudRepeat("REPEAT",2,prog);
    prog=ajoutProgramme(&prog,repeat);
    free(prog);
    return 1;
}