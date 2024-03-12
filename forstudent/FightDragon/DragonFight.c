    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    
    #define BUFLEN 32 
    
     int max(int num1, int num2)
    {
        return (num1 > num2 ) ? num1 : num2;
    }

    
    struct Character {
        char name[18];
        char configStatus[6];
        int LifePoints;
        int attack;
        int defense;
    };
     
    struct Adversary{
        char name[24];
        int LifePoints;
        int attack;
        int defense;
    };
     
    int cleanLine(char* line){
        for(;*line != '\n'; line++);
        *line = 0;
        return 0;
    }
     
    void DeleteCharacter(struct Character* character){
        printf("You delete your character, bye %s ! One day, you will beat this dragon but not with %s ...\n", character->name, character->name);
    	strcpy(character->configStatus,"KILL\0");
    	free(character);
    }
    
    void EndingCredits(){
        printf("Congratulations, you become really strong!\n");
        printf("You beat the White Dragon!\n");
        exit(0);
    }
     
    void assign_characteristics(struct Character* character, int totalPoints)
    {
      char line[BUFLEN] = {0};
      int HP = 0;
      int ATCK=0;
      int DEF = 0;
    
      if (strncmp(character->configStatus,"READY",5)==0)
        {
           return;
        }
      printf("You have %d points available.\n",totalPoints);
      do {
        printf("Enter value for Life points (positive integer): ");
        
        fgets(line, BUFLEN, stdin);
        HP = atoi(line);
        cleanLine(line);

        if (HP < 0 || HP > totalPoints) {
            printf("Value must be a positive integer and not exceed total points available.\n");
        }
      } while (HP < 0 || HP > totalPoints);
      character->LifePoints = HP + 10;
      
      totalPoints -= HP;
      do {
        printf("Enter points for Attack (positive integer): ");
        fgets(line, BUFLEN, stdin);
        ATCK = atoi(line);
        cleanLine(line);

        if (ATCK < 0 || ATCK > totalPoints) {
            printf("Attack must be a positive integer and not exceed total points.\n");
        }
      } while (ATCK < 0 || ATCK > totalPoints);

      character->attack = ATCK + 1;
      // Update the remaining points
      totalPoints -= ATCK;

      // Assign the remaining points to Defense
      character->defense = totalPoints;
      
      strcpy(character->configStatus,"READY\0");    
    }
    
     
    struct Character* newCharacter(char* name){
        printf("You create a new character : %s\n", name);
        struct Character* character = malloc(sizeof(struct Character));
        strncpy(character->name, name, 18);
        assign_characteristics(character,100);
        return character;
    }
    

    
    
    
    int fight(struct Character* character,struct Adversary* adversary)
    {
        int lifePoints = character->LifePoints;
        int advLifePoints = adversary->LifePoints;
        int powAttack = max(0, character->attack - adversary->defense);
        int powInjury = max(1, adversary->attack - character->defense);
        printf("\n\n\nLet's the fight begins ! %s versus %s\n",character->name,adversary->name);
        while (lifePoints > 0)
        {
            advLifePoints -= powAttack;
            
            if (advLifePoints <=0)
            {
                sleep(2);
                printf("\n\nYou Win !! \n");
                return 1;
            }
            
            lifePoints -= powInjury;
        
           printf("Status --> %s : %d life points and %s : %d life points\n",character->name,max(0,lifePoints),adversary->name,advLifePoints); 
        }
    
        printf("You loose :/ \n");
        return 0;
    }
     
     
    void removeFakeAdversary(struct Adversary* adversary){
        if(adversary){
            puts("You remove the fake adversary.\n");
            free(adversary);
        }
        else
            puts("You do not have a fake adversary to remove.\n");
    }
     
    struct Adversary* newAdversary(){
        char line[BUFLEN] = {0};
        int HP = 0;
        int ATCK=0;
        int DEF = 0;     
        
        struct Adversary* adversary = malloc(sizeof(struct Adversary));
        
        puts("Give a name to your adversary:\n");
        fgets(line, BUFLEN, stdin);
        strncpy(adversary->name, line, 24);
        cleanLine(line); 
        
        int totalPoints = 600;
        puts("You have 600 points to assign for this adversary!\n");

        do {
        printf("Enter value for Life points (positive integer): ");
        fgets(line, BUFLEN, stdin);
        HP = atoi(line);
        cleanLine(line);

        if (HP < 0 || HP > totalPoints) {
            printf("Value must be a positive integer and not exceed total points available.\n");
        }
        } while (HP < 0 || HP > totalPoints);
        adversary->LifePoints = HP + 10;

        totalPoints -= HP;
        do {
        printf("Enter points for Attack (positive integer): ");
        fgets(line, BUFLEN, stdin);
        ATCK = atoi(line);
        cleanLine(line);

        if (ATCK < 0 || ATCK > totalPoints) {
            printf("Attack must be a positive integer and not exceed total points.\n");
        }
        } while (ATCK < 0 || ATCK > totalPoints);

        adversary->attack = ATCK + 1;
        // Update the remaining points
        totalPoints -= ATCK;

        // Assign the remaining points to Defense
        adversary->defense = totalPoints;       

       
        puts("You build a new fake adversary !\n");
       
        return adversary;
    }
     
    int main(){
        int end = 0;
        char order = -1;
        char nl = -1;
        char line[BUFLEN] = {0};
        struct Character* character = NULL;
        struct Adversary* adversary = NULL;
        struct Adversary* WhiteDragon = malloc(sizeof(struct Adversary));
        strcpy(WhiteDragon->name, "White Dragon");
        WhiteDragon->LifePoints=1000;
        WhiteDragon->attack=90;
        WhiteDragon->defense=60;
        
        while(!end){
            puts("1: Create a new character\n2: Fight the White Dragon\n3: Delete your character\n4: Create a fake adversary for training\n5: Go training\n6: Remove the fake adversary\n7: Show characteristics points\n0: Quit");
            order = getc(stdin);
            nl = getc(stdin);
            if(nl != '\n'){
                printf("Bad command, program will exit.\n");
                exit(0);
            }
            fseek(stdin,0,SEEK_END);
            switch(order){
            case '1':
                puts("Give a name to your character for this adventure :\n");
                fgets(line, BUFLEN, stdin);
                cleanLine(line);
                character = newCharacter(line);
                break;
            case '2':
                if(!character){
                    puts("You do not have a character.\n");
                    break;
                }
                if (fight(character,WhiteDragon))
                {
                   EndingCredits(); 
                }
                else
                {
                   printf("You loose against the terrible White Dragon !\nTry again by taking advantage of the knowledge of past fighters.\n\n\n");   
                
                }
                break;
            case '3':
                if(!character){
                    puts("You do not have a character.\n");
                    break;
                }
                DeleteCharacter(character);
		character= NULL;
                break;
            case '4':
                adversary = newAdversary();
                break;
            case '5':
                if(!character){
                    puts("You do not have a character.\n");
                    break;
                }
                if(!adversary){
                    puts("You do not have a fake adversary to train with.\n");
                    break;
                }
                fight(character, adversary);
                break;
            case '6':
                if(!adversary){
                    puts("You do not have a fake adversary.\n");
                    break;
                }
                removeFakeAdversary(adversary);
                adversary= NULL;
		break;
            case '7':
                if(!character){
                    puts("You need to create a character to see its characteristics !\n");
                }
                else
                {
                    printf("\nHere are the characteristics of your character\n");
                    printf("Life points: %d\n",character->LifePoints);
                    printf("Attack points: %d\n",character->attack);
                    printf("Defense points: %d\n\n",character->defense);
 
                }
                break;
            case '0':
            default:
                end = 1;
            }
        }
        return 0;
    }

