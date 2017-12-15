#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct noeud{
    char* instruction;
    int parametre;
    struct noeud* sousprog;
    struct noeud* suivant;
}NOEUD;

typedef NOEUD* PROGRAMME;

/*
ajoutNoeud permet d'ajouter tableau de noeuds à la fin d'un programme
@param pprog pointeur vers programme
@param noeud un tableau de noeuds
**/
PROGRAMME ajoutNoeud(PROGRAMME* pprog, NOEUD* noeud){
    if(noeud->parametre == 0){
        printf("ajoutNoeud -- noeud NULL\n");
        return *pprog;
    }
    if((*pprog)->suivant!=NULL)
    {
        return ajoutNoeud( &( (*pprog)->suivant ) , noeud );   
    }else{
        (*pprog)->suivant=noeud;
        return *pprog;
    }

}

/*
newNoeud permet de créer un nouveau noeud
@param instruction
@param parametre
@param suivant pointeur vers autre noeud
**/
NOEUD newNoeud(char* instruction, int parametre,NOEUD* sousprog, NOEUD* suivant){
    NOEUD noeud;
    noeud.instruction=instruction;
    noeud.parametre=parametre;
    noeud.suivant=suivant;
    noeud.sousprog=sousprog;
    return noeud;
}



/*
newProgramme permet d'initialiser un programme
@param noeud le premier noeud
**/
PROGRAMME newProgramme(){
    PROGRAMME prog = (PROGRAMME)malloc(sizeof(NOEUD));
    prog->instruction=NULL;
    prog->parametre=NULL;
    prog->sousprog=NULL;
    prog->suivant=NULL;
    return prog;
}




/*
afficheProg affiche l'instruction et le parametre d'un noeud dans une programme
@param prog un programme
**/
void afficheProg(PROGRAMME prog){
    if(prog != NULL)
    {
        if(prog->instruction !=NULL && prog->parametre>-1){
            printf("%s ",prog->instruction);
            printf("%d\n",prog->parametre);
        }
        if(prog->sousprog!=NULL){
            afficheProg(prog->sousprog);
        }
        if(prog->suivant!=NULL)
        {
            afficheProg(prog->suivant);
        }
    }
}

int main() {
    //création de noeuds
    NOEUD noeuda = newNoeud("FORWARD",15,NULL,NULL);
    NOEUD noeudb = newNoeud("BACKWARD",50,NULL,NULL);
    
    //création programme 
    PROGRAMME prog = newProgramme();

    prog=ajoutNoeud(&prog,&noeudb);
    prog=ajoutNoeud(&prog,&noeuda);

    //problème boucle lors de 2 ajouts
    //problème création sousprog dans newnoeud

    afficheProg(prog);
    //free malloc
    //free(prog);

    return 1;
}