#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define deck_size 52 


int deck[52];
int closedDeck = 27;
int isGameOver = 0;

typedef struct Node
{   
   // int deck[52];
    int  data;
    char suit;
    struct Node* next;
}N;

//stack pointer 

N *stack=NULL;

char  whose_turn = 'A' ; 



//prototype DEclaration 




N* sort_list(N* start) ;
N *createnode(char rank,char s);
N *add_to_new_list(N *start,int  rank,char s);
void initialize_deck();
void suffle();
N *assign_cards(N *head);
N *assign_cards_to_B(N *head);
void display(N *A);
char get_suit(int i);
char get_rank(int i);
int game_over(N *A);
N *userTurn(N *A);
void show_hand (N *A);
N *deleteany(N *start,int no); //delete from user and store it in open deck
void push(int data,char s);
N *manuual_sorting(N *head,int r,char r2);
N* popFromOpenDeck();
N* addCardToUserHand(N*,N*);
void moveOpenDeckToClosedDeck();
void displayOpenDeck();



//Main Function 


int main(){
    N *A = NULL,*B=NULL,*stack=NULL;
    initialize_deck();
    suffle();

    A=assign_cards(A);
    B=assign_cards_to_B(B);
   

 

    printf("\n");

    while(!isGameOver){
        printf("\n------------------------------------------------------------------------------------\n");
        printf("\nUser A's Turn \n");
        A = userTurn(A);
        if(game_over(A) == 4){
        	printf("User A have Won");
        	break;
   		}
        printf("\n------------------------------------------------------------------------------------\n");
        printf("\nUser B's Turn \n");
        B = userTurn(B);
        if(game_over(B) == 4){
        	printf("User B have Won");
        	break;
    	}
    }
    return 0;
}





//Mannual Sorting of Linked list 

N *manuual_sorting(N *head,int r,char r2){
    N *temp1=head,*temp2=head;
    int x;
    char y;
   // printf("yes");
    while(temp1 && temp1->data!=r){
        temp1 = temp1->next;
    }
    if(!temp1 ){
        printf("\nCArd not exist\n");
        return head;
    }

    while(temp2 && temp2->data!=r2){
        temp2 = temp2->next;
    }
    if(!temp2 ){
        printf("\nCArd not exist\n");
        return head;
    }


        x = temp1->data; 
          y = temp1->suit;
        temp1->data = temp2->data; 
        temp1->suit=temp2->suit;
        temp2->data = x;
        temp2->suit=y;

    return head;
}








//Node creation 


N *createnode(char rank,char s){
    N *newp = (N*)malloc(sizeof(N));
    newp->data=rank;
    newp->suit = s;
    newp->next=NULL;
    return newp;
}










N *add_to_new_list(N *start,int rank,char s){
    N *newp = createnode(rank,s),*temp3=NULL;
            if(start==NULL){
                start=newp;
            }else if(newp){
                temp3=start;
                while (temp3->next)
                    temp3=temp3->next;
                temp3->next=newp;
            }
            return start;
}




//Deck initialize

void initialize_deck(){
     for(int i=1;i<=52;i++){
         deck[i]=i;
     }
}








//Suffle program 

void suffle()
{
    int i,t;
    time_t p;
    
    if (deck_size > 1) 
    {
        size_t i;
         srand((unsigned) time(&p));
        for (i = 1; i < deck_size ; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (deck_size- i) + 1);
          int t = deck[j];
          deck[j] = deck[i];
          deck[i] = t;
        }
    }
}




//Giving cards to user A

N *assign_cards(N *head){
    int i;
    for ( i = 1; i <=13; i++)
    {
        head = add_to_new_list(head,(deck[i]),get_suit(deck[i]));
    }
    return head;
    
}




//Giving cards to user B

N *assign_cards_to_B(N *head){
    int i;
    for ( i = 14; i <=26; i++)
    {
        head = add_to_new_list(head,(deck[i]),get_suit(deck[i]));
    }
    return head;
    
}



//Get Suit 


char get_suit(int i){
if (i <= 13)
		return 'C';
	else if  (i <= 26)
		return 'D';
	else if (i <= 39)
		return 'H';
	else
		return 'S';
}

//Get rank 

char get_rank(int i){
    int rank = i % 13;
	if (rank == 1)
		return 'A';
	if (rank == 2)
		return '2';
	if (rank == 3)
		return '3';
	if (rank == 4)
		return '4';
	if (rank == 5)
		return '5';
	if (rank == 6)
		return '6';
	if (rank == 7)
		return '7';
	if (rank == 8)
		return '8';
	if (rank == 9)
		return '9';
	if (rank == 10)
		return 'T';
	if (rank == 11)
		return 'J';
	if (rank == 12)
		return 'Q';
	return 'K';
}

int game_over(N *userHand){
    N *temp1 = userHand;
    char suit;
    char nextCardSuit;
    int i=1,j=0,count =0;
  //  printf("#####################       %d      ####################",j);
    /*
    while(j<2){
        i=1;
        if(temp1->data %13 < 10 & (temp1->next->data) == (temp1->data)+1 && (temp1->next->next->data) == (temp1->data)+2){
          //  printf(" ...........I have Crossed the 1st if statement ........\n");
            printf("...Loop outer ..");
            while(i < 3){
                suit = temp1->suit;
                printf("  innter loop suit 1 %c",suit);
                nextCardSuit = temp1->next->suit;
                if(suit != nextCardSuit)
                    break;
                temp1=temp1->next;
                 i++;
            }
        }
            if(i == 3){
                printf("i == 3");
                temp1= temp1->next->next; //goto 4th card
                j++; //to count successfull seq/set
                count++;
            }
        
        if(i!=3)
        break; 
    }
    */

    while(j<2){
        i = 1;
     //   printf("#####################       %d      ####################",j+1);

        if(temp1->data %13 < 10 && temp1->next->data == temp1->data+1 && temp1->next->next->data == temp1->data+2){
            
                while(i < 3){
                  //  printf("Inner Loop ");
                     suit = temp1->suit;
                     nextCardSuit = temp1->next->suit;
                    if(suit != nextCardSuit)
                        break;
                    temp1=temp1->next;
                    i++;
                }
        }
            
            if(i == 3){
                temp1= temp1->next;
                j++;
          //      printf("#####################       %d      ####################",j);

                count++;
               // count = 2;
            }
            
        
        
         if(i!=3){
              break;
         } 
            
    }

    /*
    if(count==2){
        return 1;
    }
    */
    /*
    i=1;
    j=0;
    count=0;
    while(j<2){
    if(temp2->data %13 < 10 && get_rank(temp2->next->data) == get_rank(temp2->data)+1 && get_rank(temp2->next->next->data) == get_rank(temp2->data+2)){
         while(i < 3){
                suit = temp2->suit;
                nextCardSuit =   temp2->next->suit;
                if(suit != nextCardSuit)
                    break;
                temp2=temp2->next;
                i++;
            }
            if(i == 3){
                temp2= temp2->next;
                j++;
                count++;
            }
        }
        if(i!=3)
            break; 
    }
    */
    if(count==2){
        if(temp1->data %13 < 10 && (temp1->next->data == temp1->data) && (temp1->next->next->data) == (temp1->data)+2){
            i = 1; 
            while(i < 3){
                suit = temp1->suit;
                nextCardSuit = temp1->next->suit;
                if(suit != nextCardSuit)
                    break;
                temp1=temp1->next;
                i++;
            }
            if(i == 3){
                temp1= temp1->next;
               j++;
                count++;
            }
        }else if(get_rank(temp1->data) == get_rank(temp1->next->data) && get_rank(temp1->next->data) == get_rank(temp1->next->next->data)){
            //if 7,8,9th card is a set
            j++;
            count++;
            temp1 = temp1->next->next->next; //goto 10th card
        }
    }
    if(j == 3){ //if first 9(3,3,3) card are matched
        if(get_rank(temp1->data) == get_rank(temp1->next->data) && get_rank(temp1->next->data) == get_rank(temp1->next->next->data) && get_rank(temp1->next->next->data) == get_rank(temp1->next->next->next->data)){
            //if 10,11,12,13 is same
            j++;
            count++;
            isGameOver = 1; //game is over
            return j;
        }
        }
    return 0;
}




N *userTurn(N *userHand){    
    int no,no2,f=1;
    int choice;
    N* card;
     printf("\nCards of User %c is \n",whose_turn);
    show_hand(userHand);
    displayOpenDeck();
    if(stack == NULL){
        printf("\nEnter \'1\' to draw card from closed deck : ");
    }else{
        printf("\nEnter \'1\' to draw card from closed deck : ");
        printf("\nEnter \'2\' to draw card from open deck : ");  
    }
    scanf("%d",&choice);
    switch (choice){
     case 1:
        if(closedDeck > deck_size){
            //assign 26card to closed deck from open deck
            moveOpenDeckToClosedDeck();
        }else{
            //add card to userHand
         //   card = createnode(deck[closedDeck] ,get_suit(deck[closedDeck]));

            userHand = add_to_new_list(userHand,deck[closedDeck] ,get_suit(deck[closedDeck]));

            //increase closedDesk
            closedDeck++;
        }

        break;
     case 2:
         if(stack == NULL){
            printf("Open deck is empty !");
         }else{
            N* popped_card = popFromOpenDeck();
            userHand = add_to_new_list(userHand,popped_card->data,popped_card->suit);
         }
        break;

     default:
        printf("\nPlease Give correct Choice : \n");
         break;
     
    }
    display(userHand);
    

    while(f){
        printf("\nEnter \'1\' to drop card: ");
        printf("\nEnter \'2\' to rearrange card : ");
        scanf("%d",&choice);
        switch (choice){
            case 1:
            {
                printf("\nEnter Card No. you want to Drop : ");
                scanf("%d",&no);
                userHand = deleteany(userHand,no);
              
                display(userHand);
              
                f=0;
            }
            break;
            case 2:
            {
                printf("Enter two Card no. you want to Swap : ");
                scanf("%d%d",&no,&no2);
                userHand = manuual_sorting(userHand,no,no2);
                printf("\nAfter swap \n");
                display(userHand);
            }
            break;
            default:
                printf("Please enter valid choice !");
                break;
        }
    }
  //  printf("................ Returned ...............");
    
    whose_turn = whose_turn =='A'?'B':'A';
    
    return userHand;
} 



void show_hand (N *A){
    
    // A=sort_list(A);
     display(A);

     }

//delete from user and store it in open deck
N *deleteany(N *start,int cardNo){
    N *temp=start,*temp2=temp;
    int item=cardNo;
    if(!temp->next){ //if user has only one card,impossible case
        printf("\nCard Droped \n");
        push(temp->data,temp->suit);
        return start->next;
    }
     if(start == NULL){  //impossible case as it will never happen,users have always 13 card
        printf("\nList is empty\n");
        return NULL;
    }

    if(temp->data == item){ //if dropped card is in first node
         printf("\nCard Droped \n");
         push(temp->data,temp->suit);
        start = start->next;
        return start;
    }

    while(temp->data != item && temp->next){//go to the node which is to drop
        temp2=temp; //temp2 hold the previous node
        temp=temp->next;
    }

     if (temp->data !=item)
    {
        printf("\nCArd is not exists\n");
        return start;
    }

    if(!temp->next){        //if dropped card found in last node
        push(temp->data,temp->suit);
        temp2->next = NULL;
    //    free(temp);  //freed the node
        printf("\nCard Droped \n");
       // printf("Returned");
        return start;
    }
    //drop card found in middle of 13 card
    push(temp->data,temp->suit);
    temp2->next=temp->next;
    printf("\nCard Droped \n");
    return start;
    
   
  
}


//adding value to stack(open deck) after dropping card
void push(int data,char s){
 N *temp = createnode(data,s);
 if(stack == NULL){
     stack = temp;
 }
 else{
     temp->next = stack;
     stack = temp;
 }
}
N* popFromOpenDeck(){
    N* temp = stack;
    if(stack == NULL){
        printf("\n Open Deck empty");
    }else{
    stack = stack->next;
    //popped from open deck and store it in user hand
    }
    return temp;

}

N* addCardToUserHand(N* userHand,N* card){
    N* temp = userHand;
    while(temp != NULL){
        temp = temp->next;
    }
    temp = card;
    return userHand;
}

void moveOpenDeckToClosedDeck(){
    N* temp;
    closedDeck = 27; //reassign to initial deck index
    for(int i=27; i<=52; i++){
        temp = popFromOpenDeck();
        deck[i] = temp->data;
    }
}

///display the open deck 1st card
void displayOpenDeck(){
    if(stack != NULL){
        printf("\nOpen deck: \n");
        printf("\nCard No.\tCard Rank\tcard Suit\n");
        printf("%d\t\t%c\t\t%c\n",stack->data,get_rank(stack->data),stack->suit);
    }
}

//Display for checking 


void display(N *A){
      N *temp=A;
    if(temp==NULL){
        printf("Empty list");
        return ;
    }
    else{
        printf("\nCard No.\tCard Rank\tcard Suit\n");
        while(temp){
            printf("%d\t\t%c\t\t%c\n",temp->data,get_rank(temp->data),temp->suit);
            temp=temp->next;
        }
    }
}