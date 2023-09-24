
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
// structure pour representer le deadline d une tache
typedef struct{
    int j,m,a;
}date;
// structure pour representer une tache
typedef struct{
    int id;
    char titre[30],description[50],statut[20];
    date deadline;
}task;
task tache[100]; //tableau pour stocker les taches
int n=0;         //variable pour suivre le nombre des taches
int x = 0;       
// fonction pour ajouter une nouvelle tache
void add(){
    int choice;
    task newtodo;
     n++; //incrementer le nombre des taches
     printf ("veuillez saisir le titre de la tache\n");
     getchar();
    gets(newtodo.titre);
     printf ("veuillez saisir la description de la tache\n");
    getchar();
    gets(newtodo.description);
     printf ("veuillez saisir le deadline de la tache sous la forme : jj/mm/aaaa \n");
    scanf("%d/%d/%d",&newtodo.deadline.j,&newtodo.deadline.m,&newtodo.deadline.a);
    printf("[1]-- a realiser \n [2]--en cours de realisation \n [3]--finalisee \n ");
    printf("\n veuillez saisir le statut de la valeur : \n");
    scanf("%d",&choice);
    if(choice==1){
        strcpy(newtodo.statut,"a realiser");
    }
    else if(choice==2){
        strcpy(newtodo.statut,"en cours de realiser");
    }
    else if (choice==3){
        strcpy(newtodo.statut,"finalisee");
    }
    else{
        printf("choix non valide ! ");
        return ;
    }
     tache[n-1] = newtodo;//ajouter la tache au tableau 
    tache[n-1].id =n + x; //incrementer l id automatiquement

}   
//fonction pour ajouter plusieurs taches
void add_lot(){
    int choice;
    task newtodo;
    int x ;
     printf("veuillez saisir le nombre des taches a ajouter : ");
     scanf("%d",&x);
     for (int i=0; i<x; i++){
    n++; 
    printf ("veuillez saisir le titre de la tache\n");
      getchar();
    gets(newtodo.titre);
     printf ("veuillez saisir la description de la tache\n");
      getchar();
    gets(newtodo.description);
     printf ("veuillez saisir le deadline de la tache\n");
    scanf("%d/%d/%d",&newtodo.deadline.j,&newtodo.deadline.m,&newtodo.deadline.a);
    printf("[1]-- a realiser\n [2]--en cours de realisation \n [3]--finalisee ");
    printf(" veuillez saisir la statut de la valeur : \n");
    scanf("%d",&choice);
    if(choice==1){
        strcpy(newtodo.statut,"a realiser");
    }
    else if(choice==2){
        strcpy(newtodo.statut,"en cours de realiser");
    }
    else if (choice==3){
        strcpy(newtodo.statut,"finalisee");
    }
    else{
        printf("choix non valide ! ");
        return ;
    }
    tache[n-1] = newtodo;
    tache[n-1].id =n +x; 
     }
}
// fonction pour trier les taches par ordre alphabetique
void sort_by_title(){
    task temp;
    for(int i =0 ;i<n-1; i++){
        for(int j=0 ;j<n-i-1;i++){
            if(strcmp(tache[j].titre,tache[j+1].titre)>0){
            temp = tache[j];
            tache[j]=tache[j+1];
            tache[j+1]=temp;
            }
        }
    }

      
      for (int i = 0; i < n; i++) {
  printf("| %-2d | %-19s | %-20s | %-20s|\n", tache[i].id, tache[i].titre, tache[i].description, tache[i].statut);  
    }
}
    // fonction pour trier les taches par deadline
    void sort_by_dead(){
        task temp;
        for(int i = 0; i < n-1; i++){
            for(int j=0; j < n-i-1; i++){
                if (tache[j].deadline.a > tache[j + 1].deadline.a ||
                (tache[j].deadline.a == tache[j + 1].deadline.a && tache[j].deadline.m > tache[j + 1].deadline.m) ||
                (tache[j].deadline.a == tache[j + 1].deadline.a && tache[j].deadline.m == tache[j + 1].deadline.m && tache[j].deadline.j > tache[j + 1].deadline.j)) {
                temp = tache[j];
                tache[j] = tache[j + 1];
                tache[j + 1] = temp;

            }
        }
    }
    
    
    for (int i = 0; i < n; i++) {
        printf("| %-2d | %-19s | %-20s | %-20s|  %02d/%02d/%04d|\n", tache[i].id, tache[i].titre, tache[i].description, tache[i].statut, tache[i].deadline.j, tache[i].deadline.m, tache[i].deadline.a);
    }
}

  void task_soon() {
    time_t now;
    time(&now);

   

    for (int i = 0; i < n; i++) {
        struct tm dead = {0};
        dead.tm_year = tache[i].deadline.a - 1900;
        dead.tm_mon = tache[i].deadline.m - 1;
        dead.tm_mday = tache[i].deadline.j;

        time_t deadline = mktime(&dead);
        int jours_restants = (int)(difftime(deadline, now) / (60 * 60 * 24));

        if (jours_restants <= 3 && jours_restants >= 0) {
            printf("%d %s %s %s %d/%d/%d \n",
                   tache[i].id, tache[i].titre, tache[i].description,
                   tache[i].statut, tache[i].deadline.j, tache[i].deadline.m, tache[i].deadline.a);
        }
    }
     
}


// fonction pour le sous menu d affichage
void show(){
    int choice ;
    printf("[1]-tri par ordre alphabetique : \n");
    printf("[2]-tri par deadline :\n ");
    printf("[3]-afficher les taches dont le deadline est dans 3 jours ou moins :\n ");
    scanf("%d",&choice);
   
    switch(choice){
        case 1 :
            sort_by_title();
        break;
        case 2 :
            sort_by_dead();
        break;
        case 3 :
            task_soon();
        break;
        default:printf("choix non valide  ! ");
    }
}
void update() {
    int id_to_up;
    printf("Veuillez saisir l ID de la tache a modifier : ");
    scanf("%d", &id_to_up);

    int found = 0; // Variable pour indiquer si une correspondance est trouvée

    for (int i = 0; i < n; i++) {
        if (id_to_up == tache[i].id) {
            found = 1; // Une correspondance a été trouvée
            int choice;
            
            printf("Tache trouvee. Que voulez-vous modifier ?\n");
            printf("1. Modifier la description\n");
            printf("2. Modifier le statut\n");
            printf("3. Modifier la deadline\n");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Saisir la nouvelle description : \n");
                    getchar();
                    gets(tache[i].description);
                    printf("Tâche mise a jour avec succes !\n");
                    break;
                case 2:
                    printf("[1] ==> a realiser\n[2] ==> en cours de realisation\n[3] ==> finalisee\n");
                    printf("Choisissez votre choix :\n");
                    int st;
                    scanf("%d", &st);
    switch (st) {
                        case 1:
                            strcpy(tache[i].statut, "a realiser");
                            printf("Tache mise a jour avec succes !\n");
                            break;
                        case 2:
                            strcpy(tache[i].statut, "en cours de realisation");
                            printf("Tache mise a jour avec succws !\n");
                            break;
                        case 3:
                            strcpy(tache[i].statut, "finalisee");
                            printf("Tache mise a jour avec succes !\n");
                            break;
                        default:
                            printf("Choix non valide !!!\n");
                            break;
                    }
                    break;
                case 3:
                    printf("Saisir le nouveau delai de la tâche (jj/mm/aaaa) :\n");
                    scanf("%d/%d/%d", &tache[i].deadline.j, &tache[i].deadline.m, &tache[i].deadline.a);
                    printf("Tache mise a jour avec succes !\n");
                    break;
        default:
            printf("Choix non valide !\n");
      }
     }
  }
}
    // Fonction pour supprimer une tâche par ID
void delete_by_id() {
    int found = 0, id;
    printf("veuillez saisir l id de la tache a supprimer : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (tache[i].id == id) {
            for (int j = i; j < n - 1; j++) {
                tache[j] = tache[j + 1];
            }
            found = 1;
            n--;
            printf("tache supprimee avec succes !\n");
            break;
        }
    }
            x++;
    if (!found) {
        printf("id non valide !\n");
    }
}
void search_by_id() {
    int found = 0 , x ; 
    printf("veuillez saisir l id de la tache a rechercher  : ");
    scanf("%d",&x);
    for (int i = 0; i < n; i++) {
        if (tache[i].id == x) {
            found = 1; 
            printf("tache :\n");
            printf("id : %d\n", tache[i].id);
            printf("titre: %s\n", tache[i].titre);
            printf("description : %s\n", tache[i].description);
            printf("statut : %s\n", tache[i].statut);
            printf("deadline : %02d/%02d/%04d\n", tache[i].deadline.j, tache[i].deadline.m, tache[i].deadline.a);
            break; 
        }
    }

    if (!found) {
        printf("aucune tache trouvee avec cet id %d.\n", x);
    }
}
// Fonction pour rechercher une tâche par titre
void search_by_title() {
    char x[30];
    printf("veuillez saisir le titre a rechercher :\n ");
    getchar();
    gets(x);

    for (int i = 0; i < n; i++) {
        if (strcmp(tache[i].titre, x) == 0) {
            printf("tache trouvee :\n");
            printf("| %-2d | %-19s | %-20s | %-20s|\n", tache[i].id, tache[i].titre, tache[i].description, tache[i].statut);
            return;
        }
    }

    printf(" tache non trouvee !\n");
}
// fonction globale de recherche 
void search (){
    int choice;
    printf("[1]-rechercher une tache par son id  : \n");
    printf("[1]-rechercher une tache par son titre : \n");
    scanf("%d",&choice);
    switch(choice){
        case 1 : search_by_id();
        break;
        case 2 : search_by_title();
        break;
        default : ("choix non valide : ");
    }
}
// Fonction pour le temps restant jusqu'à la deadline
void time_rs() {
    time_t now; 
    time(&now); 

    for (int i = 0; i < n; i++) {
         
    struct tm dead = {0}; 
dead.tm_year = tache[i].deadline.a - 1900; 
dead.tm_mon = tache[i].deadline.m - 1;     
dead.tm_mday = tache[i].deadline.j;

time_t deadline = mktime(&dead);

int jours_restants = (int)(difftime(deadline, now) / (60 * 60 * 24));
printf("tache %d - jours restants jusqu'au deadline : %d jours\n", tache[i].id, jours_restants);
    }
}


// Fonction pour afficher le nombre total de tâches
int total_t() {
    return n;
}
// Fonction pour afficher le nombre de tâches complètes et incomplètes
void done() {
    int complet = 0;
    int incomplet = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(tache[i].statut, "finalisee") == 0) {
            complet++;
        } else {
            incomplet++;
        }
    }

    printf("taches completes : %d\n", complet);
    printf("taches incompletes : %d\n", incomplet);
}
// Fonction pour afficher le menu statistique
void menu_statistique() {
    int choice;
    printf("[1] - Afficher le nombre total de taches\n");
    printf("[2] - Afficher le nombre total de taches complete et incompletes\n");
    printf("[3] - Ajouter le nombre restant de jours pour chaque tache\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("nombre total des taches : %d\n", total_t());
            break;
        case 2:
            done();
            break;
        case 3:
            time_rs();
            break;
        default:
            printf("choix non valide\n");
            break;
    }
}
int main() {
    int choice;

    do {
        printf("\t\t\t_____________________________________________________________________________\n");
        printf("\t\t\t==========================to do list =============================\t\t\t\t \n");
        printf("\t\t\t||***[1]ajouter une nouvelle tache :                                     ***||   \n");
        printf("\t\t\t||***[2]ajouter plusieurs taches :                                       ***||   \n");
        printf("\t\t\t||***[3]afficher les taches :                                            ***||   \n");
        printf("\t\t\t||***[4]modifier une tache :                                             ***||  \n");
        printf("\t\t\t||***[5] supprimer une tache :                                           ***||   \n");
        printf("\t\t\t||***[6] rechercher les taches :                                         ***||  \n");
        printf("\t\t\t||***[7] statistiques :                                                  ***||   \n");
        printf("\t\t\t||***[8] Quitter :                                                       ***||  \n");
        printf("\t\t\t||***___________________________________________________________________ ***|| \n");
        printf("Saisir votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                add_lot();
                break;
            case 3:
                show();
                break;
            case 4:
                update();
        
                break;
            case 5:
                delete_by_id();
                break;
            case 6:
                search();
                break;
            case 7:
                menu_statistique();
                break;
            case 8:
                printf("soyez les bienvenus\n");
                break;
            default:
                printf("choix non valide\n");
                break;
        }
    } while (choice != 8); 

    return 0;
}