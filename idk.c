#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


typedef struct card
{
    int number;
    char* colour;
    int used;
    struct card* next;
}CARD;

typedef struct player
{
    CARD* handCard;
}PLAYER;


typedef struct stackOfCards
{
    CARD* top;
}STACK;

void init_screen(STACK* discard, CARD* deck);
void printScreen(int playerNumber);
void clear(void);


void printCard(CARD card);
void putACard(PLAYER* player,STACK* discard,int number, char* colour,int comp);
void drawACard(PLAYER* player ,int cardNum, CARD* deck);
int drawCardNum(int number);


void makeUsed1(CARD*deck, int n);
void makeUsed0(CARD*deck);
CARD pop(CARD* deck);

void computerPlay(PLAYER* player, STACK* discard, CARD* deck,CARD stackTop);

void play(PLAYER* player, STACK* discard, CARD* deck,CARD stackTop);

void insertNode(PLAYER* player, int number, char* colour);
void deleteNode(PLAYER* player, int number, char* colour, int computer);
void create7(PLAYER* player, CARD* deck);
void printLinkedList(PLAYER* player);


void push(STACK* stack,int number, char* colour);
void swap (CARD *a, CARD *b);
void randomize ( CARD arr[], int n );



int main()
{
    CARD deck[108] = {
        { 0, "RED" },
        { 1, "RED" },
        { 1, "RED" },
        { 2, "RED" },
        { 2, "RED" },
        { 3, "RED" },
        { 3, "RED" },
        { 4, "RED" },
        { 4, "RED" },
        { 5, "RED" },
        { 5, "RED" },
        { 6, "RED" },
        { 6, "RED" },
        { 7, "RED" },
        { 7, "RED" },
        { 8, "RED" },
        { 8, "RED" },
        { 9, "RED" },
        { 9, "RED" },
        { 10, "RED" },
        { 10, "RED" },
        { 20, "RED" },
        { 20, "RED" },
        { 30, "RED" },
        { 30, "RED" },
        { 0, "BLUE" },
        { 1, "BLUE" },
        { 1, "BLUE" },
        { 2, "BLUE" },
        { 2, "BLUE" },
        { 3, "BLUE" },
        { 3, "BLUE" },
        { 4, "BLUE" },
        { 4, "BLUE" },
        { 5, "BLUE" },
        { 5, "BLUE" },
        { 6, "BLUE" },
        { 6, "BLUE" },
        { 7, "BLUE" },
        { 7, "BLUE" },
        { 8, "BLUE" },
        { 8, "BLUE" },
        { 9, "BLUE" },
        { 9, "BLUE" },
        { 10, "BLUE" },
        { 10, "BLUE" },
        { 20, "BLUE" },
        { 20, "BLUE" },
        { 30, "BLUE" },
        { 30, "BLUE" },
        { 0, "GREEN" },
        { 1, "GREEN" },
        { 1, "GREEN" },
        { 2, "GREEN" },
        { 2, "GREEN" },
        { 3, "GREEN" },
        { 3, "GREEN" },
        { 4, "GREEN" },
        { 4, "GREEN" },
        { 5, "GREEN" },
        { 5, "GREEN" },
        { 6, "GREEN" },
        { 6, "GREEN" },
        { 7, "GREEN" },
        { 7, "GREEN" },
        { 8, "GREEN" },
        { 8, "GREEN" },
        { 9, "GREEN" },
        { 9, "GREEN" },
        { 10, "GREEN" },
        { 10, "GREEN" },
        { 20, "GREEN" },
        { 20, "GREEN" },
        { 30, "GREEN" },
        { 30, "GREEN" },
        { 0, "YELLOW" },
        { 1, "YELLOW" },
        { 1, "YELLOW" },
        { 2, "YELLOW" },
        { 2, "YELLOW" },
        { 3, "YELLOW" },
        { 3, "YELLOW" },
        { 4, "YELLOW" },
        { 4, "YELLOW" },
        { 5, "YELLOW" },
        { 5, "YELLOW" },
        { 6, "YELLOW" },
        { 6, "YELLOW" },
        { 7, "YELLOW" },
        { 7, "YELLOW" },
        { 8, "YELLOW" },
        { 8, "YELLOW" },
        { 9, "YELLOW" },
        { 9, "YELLOW" },
        { 10, "YELLOW" },
        { 10, "YELLOW" },
        { 20, "YELLOW" },
        { 20, "YELLOW" },
        { 30, "YELLOW" },
        { 30, "YELLOW" },
        { 50, "WHITE" },
        { 50, "WHITE" },
        { 50, "WHITE" },
        { 50, "WHITE" }
    };
    
    STACK discard;
    randomize(deck,108);
    init_screen(&discard,deck);
    makeUsed0(deck);
    
    PLAYER player1;
    PLAYER player2;
    player1.handCard=NULL;
    player2.handCard=NULL;
    
    create7(&player1,deck);
    printf("\nPlayer 1\n");
    printLinkedList(&player1);
    printf("\n");
    
    printf("\nPlayer 2\n");
    create7(&player2,deck);
    printLinkedList(&player2);
    printf("\n\n");
    
    int i=0;
    while(player1.handCard!=NULL && player2.handCard!=NULL)
    {
        clear();
        printf("\ntop of pile:\n");
        printCard(*(discard.top));
        printf("\n\nPlayer\n");
        printLinkedList(&player1);
        printf("\n\nComp\n");
        printLinkedList(&player2);
        printf("\n\n               PLAYER\n\n");
        if(getchar()=='\n')
            play(&player1,&discard,deck,*(discard.top));
        printf("\n\n             COMPUTER\n\n");
        if(getchar()=='\n')
            computerPlay(&player2,&discard,deck,*(discard.top));
    }
    if(player1.handCard==NULL)
    {
        printf("Player  won\n");
    }
    else if (player2.handCard==NULL) {
        printf("Computer won\n");
    }
    printf("\n");
    printLinkedList(&player1);
    printf("\n");
}

//=============================================================================

//clears the screen hand cards to the two players, puts a card to discard pile from the main pile

void init_screen(STACK* discard, CARD* deck)
{
    printf("game starts\n\n");
    push(discard,deck[14].number,deck[14].colour);
    printCard(deck[14]);
}

void printScreen(int playerNumber)
{
    printf("PLAYER %d's TURN\n\n",playerNumber);
    
}
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

//=============================================================================

//CARD FUNCTIONS
void printCard(CARD card)
{
    printf("================\n");
    printf("(%d , %s)\n",card.number, card.colour);
    printf("================\n");
    
}
void putACard(PLAYER* player,STACK* discard,int number, char* colour,int comp)
{
    deleteNode(player,number,colour,comp);
    push(discard,number,colour);
}

void drawACard(PLAYER* player ,int cardNum, CARD* deck)
{
    int i=0;
    for(i=0;i<cardNum;i++)
    {
        CARD temp = pop(deck);
        printCard(temp);
        insertNode(player,temp.number,temp.colour);
    }
}

int drawCardNum(int number)
{
    switch (number) {
        case 30:
            return 2;
        case 50:
            return 4;
        default:
            return 1;
    }
}

//=============================================================================
//DECK FUNCTIONS

//used=1
void makeUsed1(CARD*deck, int n)
{
    deck[n].used =1;
}
//used =0
void makeUsed0(CARD*deck)
{
    int i;
    for(i=0;i<108;i++)
    {
        deck[i].used=0;
    }
}
CARD pop(CARD* deck)
{
    static int i = 15;
    deck[i].used=1;
    i++;
    return deck[i-1];
}


//=============================================================================


//Does what a player should do when it is her move
void computerPlay(PLAYER* player, STACK* discard, CARD* deck, CARD stackTop)
{
    //printf("1 ");
    CARD* nodePtr= player->handCard;
    while((nodePtr != NULL) && strcmp(nodePtr->colour,stackTop.colour)!=0 && nodePtr->number!=stackTop.number)
    {
        nodePtr = nodePtr->next;
        //printf("2 ");
    }
    printf("result of play function: \n");
    if(nodePtr==NULL)
    {
        CARD* head =player->handCard;
        while(head!=NULL && strcmp(head->colour,"WHITE"))
        {
            head=head->next;
        }
        
        //printf("\n\n num card %d\n\n",drawCardNum(stackTop.number));
        if(head==NULL)
        {
            drawACard(player,drawCardNum(stackTop.number),deck);
            CARD* head=player->handCard;
            if(head->number == stackTop.number || strcmp(head->colour,stackTop.colour)==0)
            {
                putACard(player,discard,head->number,head->colour,1);
            }
            else
            {
                //printf("7 ");
                return;
            }
            //printf("3 ");
        }
        else
        {
            putACard(player,discard,head->number,head->colour,1);
        }
        
        
    }
    else
    {
        putACard(player,discard,nodePtr->number,nodePtr->colour,1);
        //printf("4 ");
    }
    //printLinkedList(player);
    
}


void play(PLAYER* player, STACK* discard, CARD* deck, CARD stackTop)
{
    //printf("1 ");
    
    CARD* nodePtr= player->handCard;
    if(strcmp("WHITE",stackTop.colour)==0)
    {
        putACard(player,discard,nodePtr->number,nodePtr->colour,0);
    }
    while((nodePtr != NULL) && nodePtr->number!=stackTop.number && strcmp(nodePtr->colour,stackTop.colour)!=0)
    {
        nodePtr = nodePtr->next;
        //printf("2 ");
    }
    printf("result of play function: \n");
    if(nodePtr==NULL)
    {
        
        CARD* head =player->handCard;
        while(head!=NULL && strcmp(head->colour,"WHITE"))
        {
            head=head->next;
        }
        if(head==NULL)
        {
            drawACard(player,drawCardNum(stackTop.number),deck);
            CARD* head=player->handCard;
            if(head->number == stackTop.number || strcmp(head->colour,stackTop.colour)==0)
            {
                putACard(player,discard,head->number,head->colour,0);
            }
            else
            {
                return;
            }
        }
        else{
            putACard(player,discard,head->number,head->colour,0);
        }
        
        
    }
    else
    {
        int number;
        char colour[10];
        fflush(stdin);
        printf("Enter num: ");
        scanf("%d",&number);
        printf("Enter colour: ");
        scanf("%s",colour);
        putACard(player,discard,nodePtr->number,nodePtr->colour,0);
        //printLinkedList(player);
    }
    //printLinkedList(player);
    
}

//=============================================================================
//LINKED LIST

//deletes a node using the info given
void deleteNode(PLAYER* player, int number, char* colour, int computer)
{
    CARD *current = player->handCard, *previous;
    CARD *head = player->handCard;
    if (head == NULL) {
        printf("Error : Invalid node pointer !!!\n");
        return;
    }
    
    if ((current->number == number)&& strcmp(current->colour,colour)==0 )
    {
        CARD* temp = current;
        player->handCard = temp->next;
        free(current);
        return;
    }
    
    if(computer)
    {
        while ((current != NULL )&& (current->number != number) && (strcmp(current->colour,colour)))
        {
            previous = current;
            current = current->next;
        }
    }
    else
    {
        while ((current != NULL )&& ((strcmp(current->colour,colour))||(current->number != number)))
        {
           // printf("here\n");
            previous = current;
            current = current->next;
        }
    }
    
    if (current == NULL)
    {
        printf("not found in Linked List\n");
        return;
    }
    CARD* temp=current;
    previous->next = temp->next;
    free(current);
    
    
    
}

//adds a node with the given info to the end
void insertNode(PLAYER* player, int number, char* colour)
{
    CARD* head = player->handCard;
    CARD* newNode = (CARD*) malloc(sizeof(CARD));
    newNode->number  = number;
    newNode->colour=(char*)malloc(100*sizeof(char));
    strcpy(newNode->colour,colour);
    newNode->next = head;
    player->handCard = newNode;
}
void create7(PLAYER* player, CARD* deck)
{
    int i,count=0;
    for(i=0;count<7;i++)
    {
        if(deck[i].used==0)
        {
            insertNode(player,deck[i].number,deck[i].colour);
            makeUsed1(deck,i);
            count++;
        }
    }
}
//Prints the list
void printLinkedList(PLAYER* player) {
    CARD* nodePtr= player->handCard;
    while (nodePtr != NULL)
    {
        printf("%d, %s", nodePtr->number, nodePtr->colour);
        nodePtr = nodePtr->next;
        if(nodePtr != NULL)
        { printf("\n");}
    }
}

//=============================================================================
//Adds to the stack checks for duplicates. if duplicates are present it is invalid
void push(STACK* stack,int number, char colour[])
{
    CARD* temp = stack->top;
    CARD* newCard = (CARD*)malloc(sizeof(CARD));
    newCard->number=number;
    newCard->colour = (char*)malloc(100*sizeof(char));
    strcpy(newCard->colour,colour);
    newCard->used=1;
    
    if(temp==NULL)
    {
        stack->top=newCard;
        newCard->next=NULL;
    }
    else
    {
        newCard->next=stack->top;
        stack->top=newCard;
    }
    printCard(*newCard);
    printf("\n");
}
//=============================================================================
//SHUFFLE FUNCTIONS
// A utility function to swap to integers
void swap (CARD *a, CARD *b)
{
    CARD temp = *a;
    *a = *b;
    *b = temp;
}

// A function to generate a random permutation of arr[]
void randomize ( CARD arr[], int n )
{
    int i;
    srand ( time(NULL) );
    for ( i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        
        swap(&arr[i], &arr[j]);
    }
}

//=============================================================================



