#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

typedef struct account
{
   char name[20],username[20],password[20],gender[5];
   long long int mobile;
   int age;
   
   char following[20][100];
   char followers[20][100];
   int cfollowing,cfollowers;
   
   int ctweets;
   struct tweet{
		char body[100];
		
		int clikes;
		char likes[20][100];
		
		int ccomments;
		char commenter[20][100];
		char comments[100][100];	
						
		long long int t;
						
	} tweets[100];

   char nqueue[50][100];
   int ntop;
   
   int visit;
   
   struct account *next;
   
} account;

account *head=NULL,*last=NULL,*temp,*current_acc;

void import_all();
void export_all();
void free_all();
void import_list();
void export_list();
void import_tweets();
void export_tweets();
void import_tc();
void export_tc();
void import_tlc();
void export_tlc();
void import_notify();
void export_notify();
void twitter_layout();
void signup();
account *login();
void userhome(account *);
void search_user(account*);		
void search_all(account*);	
void search_hash(account*);													
account *address(char[]);
void follow(account*,account*);
void unfollow(account*,account*);
char* charto_(char[]);
char* _tochar(char[]);
void add_tweet(account*);
void delete_tweet(account*);
void display_tweets(account*,account*);
void like_tweet(account*,account*,struct tweet*);
void unlike_tweet(account*,account*,struct tweet*);
void comment_tweet(account*,account*,struct tweet*);
void view_tweet(struct tweet*,account*,account*);
void view_following(account*,account*);
void view_followers(account*,account*);
void view_profile(account*,account*);
void more_details(account*,account*);
int isfollower(account*,account*);
int isfollowing(account*,account*);
char* to_upper(char[]);
char* to_lower(char[]);
void displayall_tweets(account*);
account* tweet_owner(struct tweet*);
int compare(const void*, const void*);
void edit_profile(account*);
int countdigit(long long);
int access(char[],int,account*,long long);
int password_access(char[]);
void push_notify(account*,char[],account*);
void pop_notify(account*,char[]);
void notification(account*);
void mention(char[],account*);

char L[]=" liked your tweet : ",
C[]=" commented on your tweet : ",
F[]=" started following you!",
M[]=" mentioned you in a comment : ",
dot[]="....";

int choice1,choice2,choice3,i,j,k;
int main()
{

    import_all();
    
    start :	
    do{
    twitter_layout();
    printf("         1:LOGIN                    2:SIGN UP        \n");
	printf("                      0:EXIT                         ");
	printf("\n\nYour Choice : ");
	scanf_s("%d",&choice1,1);
	switch(choice1){
		
		case 1: current_acc = login();
				if(current_acc == NULL)
					goto start; 
				break;
				
		case 2: signup();
				goto start;
 
	}
	if(choice1!=0)
	{
	do{
	userhome :
		
	system("CLS");
	twitter_layout();
    printf(" %-20s	%20s\n",current_acc->name,current_acc->username);
    printf("------------------------------------------------------\n");
	printf("                                   |  Followers : %d  \n",current_acc->cfollowers);
	printf("                                   |  Following : %d  \n",current_acc->cfollowing);
	printf("                                   |  Tweets    : %d  \n",current_acc->ctweets);
	printf("------------------------------------------------------\n");
	
	printf("\nSELECT YOUR CHOICE : \n");
	if(current_acc->visit==1)
		printf("\n1: You have (%d) new notifications\n",current_acc->ntop);
	else
		printf("\n1: View recent notifications\n");
	printf("2: Search Twitter\n3: Tweet\n4: View Followers\n");
	printf("5: View Following\n6: Settings\n0: logout\n\nYour Choice : ");
	scanf("%d",&choice2);

	system("CLS");
	twitter_layout();
	switch(choice2)
	{
		case 1 : notification(current_acc);
				 break;
		case 2 : do{
				 printf("\nSELECT YOUR CHOICE : \n\n");
				 printf("1 : Search Everything\n2 : Search Account\n3 : Search #hashtag\n");
				 printf("\n0 : <-- Back\n\nYour Choice : ");
				 scanf("%d",&choice3);
				 
				 switch(choice3){
				 	case 1 : search_all(current_acc);
				 			 break;
				 	case 2 : search_user(current_acc);
				 			 break;
				 	case 3 : search_hash(current_acc);
				 			 break;
				 }
				 system("CLS");
				 twitter_layout();
				 }while(choice3!=0);
				 
				 break;
		case 3 : do{
				 printf("\nSELECT YOUR CHOICE : \n\n");
				 printf("1 : Add Tweet\n2 : Delete Tweet\n3 : View my Tweets\n4 : View all Tweets\n\n0 : <-- Back");
				 //add more attributes 
				 printf("\n\nYour Choice : ");
				 scanf("%d",&choice3);
				 
				 switch(choice3){
				 	case 1 : add_tweet(current_acc);
				 			 break;
				 	case 2 : delete_tweet(current_acc);
				 			 break;
				 	case 3 : display_tweets(current_acc,current_acc);
				 			 break;
				 	case 4 : displayall_tweets(current_acc);
				 			 break;
				 }
				 system("CLS");
				 twitter_layout();
				 }while(choice3!=0);
				 break;
				 
		case 4 : view_followers(current_acc,current_acc);
				 break;
		case 5 : view_following(current_acc,current_acc);
				 break;
		case 6 : edit_profile(current_acc); 
				 break;
		case 0 : system("CLS");
				printf("\n\nDo you want to logout?\n\n");
				printf("1 : Yes\n\n0 : CANCEL\n\nYour Choice : ");
				int logout;
				scanf("%d",&logout);
				if(logout==0)
					choice2=7;
				break;
	}	
	}while(choice2!=0);
	}
	}while(choice1!=0);
	system("CLS");
	printf("\n\n\n\n  THANK YOU VISIT AGAIN! :) \n\n");
	export_all();
	free_all();
	return 0;
}


void free_all(){
	account *t=head;
	temp=head->next;
	while(temp!=NULL){
		free(t);
		t=temp;
		temp=temp->next;
	}
	free(t);
}


void export_all()
{
	export_notify();
	export_tlc();
	export_tweets();
	export_tc();
    export_list();
}

void notification(account *acc){
	
	int x,choice;
	A:
	system("cls");
	twitter_layout();
	if(acc->ntop==0){
		printf("You have No Notifications!\n");
		getch();
		return;
	}
	printf("Your Notifications :\n\n");
	for(x=1;x<=acc->ntop;x++){
		printf("%d: %s\n\n",x,_tochar(acc->nqueue[x]));
	}
	acc->visit=0;
	printf("\n%d: Clear all notifications\n0: <-- Back\n\nYour Choice : ",acc->ntop+1);
	scanf("%d",&choice);
	if(choice==0)
		return;
	if(choice==acc->ntop+1)
		{
			acc->ntop=0;
			system("CLS");
			twitter_layout();
			printf("\nYour Notifications have been Cleared!\n");
			getch();
			return;
		}
	goto A;	
}
void import_all(){
	import_list();
    import_tc();
    import_tweets();
    import_tlc();
    import_notify();
}

void push_notify(account *acc1,char str[],account *acc2){
	if(acc1==acc2)
		return;
	if(strstr(str,L)!=NULL  || strstr(str,C)!=NULL)
		strcat(str,dot);
	acc1->ntop++;
	strcpy(acc1->nqueue[acc1->ntop],str);
	acc1->visit=1;
}
void pop_notify(account *acc,char str[]){
	int x;
	for(x=1;x<=acc->ntop;x++){
		if(strcmp(acc->nqueue[x],str)==0){
			while(x <= acc->ntop){
			strcpy(acc->nqueue[x],acc->nqueue[x+1]);
			x++;
			}
			break;
		}
	}
	acc->ntop--;
	if(acc->ntop!=0)
		acc->visit=1;
}

void export_notify(){
	if(head==NULL)
		return;
	
	FILE *fcn;
	fcn = fopen("cnotify.txt","w");
	temp = head;
	while(temp!=NULL){
		fprintf(fcn,"%d\t",temp->ntop);
		temp=temp->next;
	}
	fclose(fcn);
	
	FILE *fn;
	fn = fopen("notify.txt","w");
	temp=head;
	int x;
	while(temp!=NULL){
		for(x=1 ; x<=temp->ntop ; x++){
			fprintf(fn,"%s\t",charto_(temp->nqueue[x]));
		}
		temp=temp->next;
	}
	fclose(fn);
	
	FILE *fv;
	fv = fopen("visit.txt","w");
	temp=head;
	while(temp!=NULL){
		fprintf(fv,"%d\t",temp->visit);
		temp=temp->next;
	}
	fclose(fv);
	
}

void import_notify(){
	
	FILE *fcn;
	if(feof(fcn))	return;
	fcn = fopen("cnotify.txt","r");
	if(feof(fcn))	return;
	temp = head;
	while(temp!=NULL){
		fscanf(fcn,"%d\t",&temp->ntop);
		temp=temp->next;
	}
	fclose(fcn);
	
	FILE *fn;
	fn = fopen("notify.txt","r");
	if(feof(fn))	return;
	temp=head;
	int x;
	while(temp!=NULL){
		for(x=1 ; x<=temp->ntop ; x++){
			fscanf(fn,"%s\t",temp->nqueue[x]);
		}
		temp=temp->next;
	}
	fclose(fn);
	
	FILE *fv;
	fv = fopen("visit.txt","r");
	if(feof(fv))	return;
	temp=head;
	while(temp!=NULL){
		fscanf(fv,"%d\t",&temp->visit);
		temp=temp->next;
	}
	fclose(fv);
}

void edit_profile(account* acc)
{
	A:
	system("CLS");
	twitter_layout();
	
	printf("\nSETTINGS :\n\n");
	printf("1: Change Name\n2: Change UserName\n3: Change Password\n4: Change PhoneNumber\n\n0: <--Back\n\nYour Choice : ");
	int choice1,choice2,p;
	scanf("%d",&choice1);
	if(choice1==0)
		return;
		
	system("CLS");
	twitter_layout();
	
	char str[20],str2[20];
	
	switch(choice1)
	{
		case 1 : printf("CHANGE NAME : \n\n");
				 printf("Current Name : %s\n",acc->name);
				 printf("Enter New Name : ");
				 fflush(stdin);
				 scanf("%s",str);
				 if(access(str,1,acc,0)==0)
					break;	
				 printf("\nDo you want to save changes to Name?\n1: Yes    0: No\n\nYour Choice : ");
				 scanf("%d",&choice2);
				 if(choice2==0)
				 	break;
				 strcpy(acc->name,str);
				 printf("\nSaved changes to Name!\n");
				 getch();
				 break;
		
		case 2 : printf("CHANGE USERNAME : \n\n");
				 printf("Current UserName : %s\n",acc->username);
				 printf("Enter New UserName : ");
				 fflush(stdin);
				 scanf("%s",str);
				 if(access(str,2,acc,0)==0)
					break;	
					
				 printf("\nDo you want to save changes to UserName?\n\n1: Yes    0: No\n\nYour Choice : ");
				 scanf("%d",&choice2);
				 if(choice2==0)
				 	break;
				 strcpy(acc->username,str);
				 printf("\nSaved Changes to Username!\n");
				 getch();
				 break;
		
		case 3 : B:
				 printf("CHANGE PASSWORD : \n\n");	 
				 printf("Enter Current Password : ");
				 
				 p=0;
				 fflush(stdin);
				 do{ 
        			str[p]=getch(); 
       			    if(str[p]!='\r'){ 
            			printf("*"); 
        			} 
       				p++; 
   					}while(str[p-1]!='\r'); 
    			 str[p-1]='\0';
				  
				 if(access(str,3,acc,0)==0)
						break;
						
				 printf("Enter new Password : ");
				 p=0;
				 fflush(stdin);
				 do{ 
        			str[p]=getch(); 
       			    if(str[p]!='\r'){ 
            			printf("*"); 
        			} 
       				p++; 
   					}while(str[p-1]!='\r'); 
    			 str[p-1]='\0';
				 
				 printf("Enter new Password Again : ");
			     p=0;
				 fflush(stdin);
				 do{ 
        			str2[p]=getch(); 
       			    if(str2[p]!='\r'){ 
            			printf("*"); 
        			} 
       				p++; 
   					}while(str2[p-1]!='\r'); 
    			 str2[p-1]='\0';
				 
				 if(strcmp(str,str2)!=0)
				 	{
				 		printf("Password Mismatched! Tryagain!\n");
				 		goto B;
					}
				 printf("\nDo you want to save changes to PassWord?\n\n1: Yes    0: No\n\nYour Choice : ");
				 scanf("%d",&choice2);
				 if(choice2==0)
				 	break;
				 strcpy(acc->password,str);
				 printf("\nPassword has been Changed!\n");
				 getch();
				 break;
		case 4:  printf("CHANGE PHONE NUMBER : \n\n");
				 printf("Current PhNo : %lld\n",acc->mobile);
				 printf("Enter New PhNo : ");
				 long long ph;
				 fflush(stdin);
				 scanf("%lld",&ph);
				 if(access(NULL,1,acc,ph)==0)
						break;	
				 printf("\nDo you want to save changes to PhoneNumber?\n1: Yes    0: No\n\nYour Choice : ");
				 scanf("%d",&choice2);
				 if(choice2==0)
				 	break;
				 acc->mobile=ph;
				 printf("\nPhoneNumber has been saved successfully\n");
				 getch();
				 break;
	}
	export_all();
	import_all();
	goto A;
}

int access(char str[],int choice,account* acc,long long int ph){
	
	if(choice==3)
		{
			if(strcmp(acc->password,str)==0)
				return 1;
			else
			{
				printf("Incorrect Password!\n\nTry Again!!\n");
				getch();
				return 0;
			}
	}
	temp=head;
	while(temp!=NULL){
		if(temp!=acc){
		switch(choice){
			case 1 : if(strcmpi(str,temp->name)==0){
						printf(" '%s' is Already taken!\n\nTry Again!!\n",str);
						getch();
						return 0;
						}	
			case 2 : if(strcmpi(str,temp->username)==0){
						printf(" '%s' is Already taken!\n\nTry Again!!\n",str);
						getch();
						return 0;
						}
			case 4 : if(temp->mobile==ph){
						printf(" '%lld' number is Already taken!\n\nTry Again!!\n",ph);
						getch();
						return 0;
						}
		}
		temp=temp->next;
	}
	return 1;
}
}
void view_profile(account *acc1,account *acc2){
	
	A:
	system("CLS");
	twitter_layout();
    printf(" %-20s	%20s\n",acc2->name,acc2->username);
    printf("------------------------------------------------------\n");
	printf("                                   |  Followers : %d  \n",acc2->cfollowers);
	printf("                                   |  Following : %d  \n",acc2->cfollowing);
	printf("                                   |  Tweets    : %d  \n",acc2->ctweets);
	printf("------------------------------------------------------\n");
	
	if(isfollowing(acc1,acc2)==1 && isfollower(acc1,acc2)==1)
		printf("\nYou and %s are following eachother!\n",acc2->username);
	else if(isfollowing(acc1,acc2)==1 && isfollower(acc1,acc2)==0)
		printf("\nYou are following %s !\n",acc2->username);
	else if(isfollowing(acc1,acc2)==0 && isfollower(acc1,acc2)==1)
		printf("\n%s is following you!\n",acc2->username);
	else
		printf("\nYou and %s are not following eachother!\n",acc2->username);

	printf("\nSelect :\n\n");
	if(acc2==current_acc)
		{
			printf("1: Return to your profile\n");
		}
	else if(isfollowing(acc1,acc2)==1)
		{
			printf("1: UnFollow %s\n",acc2->username);
		}
	else
		{
			printf("1: Follow %s\n",acc2->username);
		}
	printf("2: View Tweets\n3: View Followers\n4: View Following\n5: View More Details\n");
	printf("\n0: <-- Back\n\nYour Choice : ");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
		return;
	
	switch(choice){
		case 1: if(current_acc == acc2)
				{
					return;
				}
				else if(isfollowing(acc1,acc2)==1)
				{
					unfollow(acc1,acc2);
				}
				else
				{
					follow(acc1,acc2);
				}
				break;
				
		case 2: display_tweets(acc1,acc2);
				break;
		case 3: view_followers(acc1,acc2);
				break;
		case 4: view_following(acc1,acc2);
				break;
		case 5: more_details(acc1,acc2);
				break;		
	}
	goto A;
}

void more_details(account* acc1,account* acc2){
	
	int choice;
	A:
	system("CLS");
	twitter_layout();
	printf("\n\nNAME     : %s\nUSERNAME : %s\n",acc2->name,acc2->username);
	printf("------------------------------------------------------\n");
	printf("Followers : %d\nFollowing : %d\nTweets    : %d\n",acc2->cfollowers,acc2->cfollowing,acc2->ctweets);
	printf("------------------------------------------------------\n");
	printf("PhoneNumber : %lld*****\n",acc2->mobile/100000);
	if(acc2->gender[0]=='m'||acc2->gender[0]=='M')
		printf("Gender      : Male\n");
	else if(acc2->gender[0]=='f'||acc2->gender[0]=='F')
		printf("Gender      : Female\n");
	else
		printf("Gender      : Others\n");
	printf("------------------------------------------------------\n");
	printf("0 : <-- Back\n\nYour Choice : ");
	scanf("%d",&choice);
	if(choice==0)
		return;
	goto A;
}

void view_followers(account *acc1,account *acc2){
	int op,x;
	fflush(stdin);
	A:	
	system("CLS");
	twitter_layout();
	
	if(acc2->cfollowers==0){
		printf("\n\nNo followers to show\n\nEnter any key to continue...");
		getch();
		return;
	}
	
	account *t;
	for(x=1 ; x <= acc2->cfollowers ; x++){
		t = address(acc2->followers[x]);
		printf("\n%d : %s\n",x,t->name);
		printf("Followers: %d | Following: %d | Tweets: %d\n\n",t->cfollowers,t->cfollowing,t->ctweets);
	}
	
	printf("0 : <-- Back\n\nYour Choice : ");
	scanf("%d",&op);
	if(op==0)
		return;
	else if(op<=x)
		view_profile(acc1,address(acc2->followers[op]));
	goto A;
}

void view_following(account *acc1,account *acc2){
	int op,t;
	A:
	fflush(stdin);	
	system("CLS");
	twitter_layout();
	
	if(acc2->cfollowing==0){
		printf("\n\nUser is not following any account!\n\nEnter any key to continue...");
		getch();
		return;
	}
	
	account *tp;
	for(t=1 ; t <= acc2->cfollowing ; t++){
		tp = address(acc2->following[t]);
		printf("\n%d : %s\n",t,tp->name);
		printf("Followers: %d | Following: %d | Tweets: %d\n\n",tp->cfollowers,tp->cfollowing,tp->ctweets);
	}
	
	printf("0 : <-- Back\n\nYour Choice : ");
	scanf("%d",&op);
	if(op==0)
		return;
	else if(op<=acc2->cfollowing)	
		view_profile(acc1,address(acc2->following[op]));
	goto A;
}

void display_tweets(account *acc1,account *acc2)
{
	A:
	system("CLS");
	twitter_layout();
	if(acc2->ctweets == 0){
		printf("\nYou have no Tweets to display!\n");
		goto down;
	}
	
	struct tweet *dict[23];
	int count=1,k=1,choice;
	
	printf("Your Tweets : \n\n");
	for(count=acc2->ctweets;count>=1;count--,k++){
		printf("%d: %s\n",k,_tochar(acc2->tweets[count].body));
		dict[k]=&acc2->tweets[count];
		printf("    %d likes    %d comments\n\n",acc2->tweets[count].clikes,acc2->tweets[count].ccomments);
	}
	down:
	printf("0: <-- Back\n\nYour Choice : ");
	scanf("%d",&choice);
	
	if(choice==0)
		return;
	else if(choice<=k);
		view_tweet(dict[choice],acc1,acc2);	
	goto A;
}

void view_tweet(struct tweet twt[],account *acc1,account *acc2){
	
	B:
	system("CLS");
	twitter_layout();
	printf("TWEET : \n\n");
	printf("------------------------------------------------------\n");
	printf(" %s\n",_tochar(twt->body));
	printf("------------------------------------------------------\n");
	if(twt->clikes==0)
		printf("-> No likes for the Tweet\n");
	else if(twt->clikes==1)
		printf("-> Liked by %s\n",twt->likes[1]);
	else
		printf("-> Liked by %s and %d others\n",twt->likes[1],twt->clikes-1);
		
		
	if(twt->ccomments==0)
		printf("-> No comments for the Tweet\n");
	else if(twt->ccomments==1)
		printf("-> %s commented on the Tweet\n",twt->commenter[1]);
	else
		printf("-> View all %d comments\n",twt->ccomments);
	printf("------------------------------------------------------\n");
	int found = 0;	
	for(k=1;k<=twt->clikes;k++){
		if(strcmp(twt->likes[k],acc1->username)==0){
			found = 1;
			break;
		}
	}
	if(acc1==acc2)
		printf("1: Return to your profile\n");
	else if(found==0)
		printf("1: Like\n");
	else
		printf("1: Unlike\n");
	printf("2: Add Comment\n3: View likes\n4: View Comments\n0: <-- Back\n\nYour Choice : ");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
		return;
	switch(choice){
		case 1 : if(acc1==acc2)
					return;
				 if(found==0)
				 	like_tweet(acc1,acc2,twt);
				 else
				 	unlike_tweet(acc1,acc2,twt);
				 break;
		case 2 : comment_tweet(acc1,acc2,twt);
				 break;
		case 3 : if(twt->clikes==0)
					printf("\nNo likes for the Tweet!\n");
				 else{
				 	account *STACK[50];
				 	int top=0;
				 	for(k=1;k<=twt->clikes;k++){
						printf("%d: %s\n",k,twt->likes[k]);
						STACK[++top] = address(twt->likes[k]);
						}
					printf("\n0: <-- Back\n\nYour Choice : ");
					int choice2;
					scanf("%d",&choice2);
					if(choice2==0)
						break;
					else if(choice2<=top)
						view_profile(acc1,STACK[choice2]);
				 	}
				 break;
		case 4 : if(twt->ccomments==0)
					printf("\nNo comments for the Tweet!\n");
				 else{
				 	account *STACK[50];
				 	int top=0,c;
				 	for(c=1;c<=twt->ccomments;c++){
						printf("%d: %s -> %s\n\n",c,twt->commenter[c],_tochar(twt->comments[c]));
						STACK[++top] = address(twt->commenter[c]);
						}
					printf("0: <-- Back\n\nYour Choice : ");
					int choice2;
					scanf("%d",&choice2);
					if(choice2==0)
						break;
					else if(choice2<=twt->ccomments)
						view_profile(acc1,STACK[choice2]);
				 }
				 break;
	//	default : printf("\nEnter Valid Inputs!\n");	break;
	}
	goto B;
}

void add_tweet(account* acc)
{
	A:
	system("CLS");
	twitter_layout();
	printf(" %-20s	%20s\n",acc->name,acc->username);
    printf("------------------------------------------------------\n");
	printf("                                   |  Followers : %d  \n",acc->cfollowers);
	printf("                                   |  Following : %d  \n",acc->cfollowing);
	printf("                                   |  Tweets    : %d  \n",acc->ctweets);
	printf("------------------------------------------------------\n");
	
	char str[100];
	int choice,chash;
	
	printf("\n\nType your tweet :\n");
	fflush(stdin);
	gets(str);
	
	int choice2;
	printf("\nDo you want to upload the tweet?\n1: Yes\n2: Edit again\n0: No\n\nYour Choice : ");
	scanf("%d",&choice2);
	if(choice2==2)
		goto A;
	else if(choice2==0)
		return;
	else if(choice2==1){

	strcpy(acc->tweets[++acc->ctweets].body,str);
	acc->tweets[acc->ctweets].clikes=0;
	acc->tweets[acc->ctweets].ccomments=0;
	acc->tweets[acc->ctweets].t=time(NULL);
	
	mention(str,acc);
	
	printf("\nTweet upload Successful !!\n");
	}
	else
		printf("Enter valid input!!");
	getch();
}

void delete_tweet(account *acc){
	
	B:
	system("CLS");
	twitter_layout();
	if(acc->ctweets == 0){
		printf("\nYou have no Tweets to display!\n");
		goto down;
	}
	
	int count=1,choice;
		
	printf("TWEETS : \n\n");
	for(count=1;count<=acc->ctweets;count++){
		printf("%d: %s\n",count,_tochar(acc->tweets[count].body));
		printf("%d likes    %d comments\n\n",acc->tweets[count].clikes,acc->tweets[count].ccomments);
	}
	down:
	printf("0: <-- Back\n\nSelect Tweet to delete : ");
	scanf("%d",&choice);
	
	if(choice==0)
		return;
	else if(choice<=count){
	printf("TWEET :\n");
	printf("------------------------------------------------------\n");
	printf(" %s\n",_tochar(acc->tweets[choice].body));
	printf("------------------------------------------------------\n");
	printf("    %d likes    %d comments\n\n",acc->tweets[choice].clikes,acc->tweets[choice].ccomments);
		
	int ch;
	printf("Are you sure you want to delete tweet ?\n\n");
	printf("1: Yes    2: No\n\nYour Choice : ");
	scanf("%d",&ch);
	if(ch==2)
		return;
	if(ch!=1)
		goto B;
	for(i=choice ; i <= acc->ctweets-1 ; i++)
			acc->tweets[i]=acc->tweets[i+1];
	
	acc->ctweets--;	
	printf("Tweet Deletion Successfull!");
	}
	else
			printf("\nEnter valid input!");
	getch();
}

void like_tweet(account *acc1,account *acc2,struct tweet twt[]){
	
	twt->clikes++;
	strcpy(twt->likes[twt->clikes],acc1->username);
	printf("\nYou liked %s's Tweet\n",acc2->username);
	
	char str[50],t[50];
	strcpy(str,acc1->username);
	strncpy(t,twt->body,10);
	t[10]='\0';
	strcat(str,L);
	strcat(str,t);
	push_notify(acc2,str,acc1);
}

void unlike_tweet(account *acc1,account *acc2,struct tweet twt[]){

	for(k=1 ; k <= twt->clikes ; k++){
		if(strcmp(acc1->username,twt->likes[k])==0){
			while( k<= twt->clikes-1){
				strcpy(twt->likes[k],twt->likes[k+1]);
				k++;
			}
			break;
		}
	}
	twt->clikes--;
	printf("\nYou Unliked %s's Tweet\n",acc2->username);
	
	char str[50],t[50];
	strcpy(str,acc1->username);
	strncpy(t,twt->body,10);
	t[10]='\0';
	strcat(str,L);
	strcat(str,t);
	pop_notify(acc2,str);
	
}

void comment_tweet(account *acc1,account *acc2,struct tweet twt[]){
	
	twt->ccomments++;
	printf("\nType your comment...\n\n");
	fflush(stdin);
	scanf("%[^\n]s",charto_(twt->comments[twt->ccomments]));
	strcpy(twt->commenter[twt->ccomments],acc1->username);
	mention(twt->comments[twt->ccomments],acc1);
	printf("\nYou commented on %s's Tweet\n",acc2->username);
	
	char str[50],t[50];
	strcpy(str,acc1->username);
	strncpy(t,twt->body,10);
	t[10]='\0';
	strcat(str,C);
	strcat(str,t);
	push_notify(acc2,str,acc1);

}

void import_tc()
{
	FILE *fp;
	fp=fopen("tc.txt","r");
	rewind(fp);
	if(feof(fp))
		return;
	temp=head;
	while(fscanf(fp,"%d\t",&temp->ctweets))
	{
		temp=temp->next;
		if(temp==NULL)
			break;
    }
	fclose(fp);
}
void export_tc()
{
	FILE *fp;
	fp=fopen("tc.txt","w");
	temp=head;
	while(temp!=NULL)
	{
		fprintf(fp,"%d\t",temp->ctweets);
		temp=temp->next;
	}
	fclose(fp);
}

void export_tlc(){
	FILE *fp;
	fp = fopen("tlc.txt","w");
	if(feof(fp))
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				fprintf(fp,"%d\t",temp->tweets[j].clikes);
				fprintf(fp,"%d\t",temp->tweets[j].ccomments);
			}
		}
		temp = temp->next;
	}
	fclose(fp);
	
	FILE *fl;
	fl = fopen("tlikers.txt","w");
	if(feof(fl))
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].clikes ; k++)
					fprintf(fl,"%s\t",temp->tweets[j].likes[k]);
			}
		}
		temp = temp->next;
	}
	fclose(fl);
	
	FILE *fc;
	fc = fopen("tcommenters.txt","w");
	if(feof(fc))
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].ccomments ; k++)
					fprintf(fc,"%s\t",temp->tweets[j].commenter[k]);
			}
		}
		temp = temp->next;
	}
	fclose(fc);
	
	FILE *fcc;
	fcc = fopen("tcomments.txt","w");
	if(feof(fcc))
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].ccomments ; k++)
					fprintf(fcc,"%s\t",charto_(temp->tweets[j].comments[k]));
			}
		}
		temp = temp->next;
	}
	fclose(fcc);
	
	FILE *ft;
	ft = fopen("ttime.txt","w");
	if(feof(ft))
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				fprintf(ft,"%lld\t",temp->tweets[j].t);
			}
		}
		temp = temp->next;
	}
	fclose(ft);
	
}

void import_tlc(){
	FILE *fp;
	fp = fopen("tlc.txt","r");
	if(head==NULL)
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				fscanf(fp,"%d\t",&temp->tweets[j].clikes);
				fscanf(fp,"%d\t",&temp->tweets[j].ccomments);
			}
		}
		temp=temp->next;
	}
	fclose(fp);
	
	FILE *fl;
	fl = fopen("tlikers.txt","r");
	if(head==NULL)
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].clikes ; k++)
					fscanf(fl,"%s\t",temp->tweets[j].likes[k]);
			}
		}
		temp = temp->next;
	}
	fclose(fl);
	
	FILE *fc;
	fc = fopen("tcommenters.txt","r");
	if(head==NULL)
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].ccomments ; k++)
					fscanf(fc,"%s\t",temp->tweets[j].commenter[k]);
			}
		}
		temp = temp->next;
	}
	fclose(fc);
	
	FILE *fcc;
	fcc = fopen("tcomments.txt","r");
	if(head==NULL)
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				for(k=1 ; k<=temp->tweets[j].ccomments ; k++)
					fscanf(fcc,"%s\t",temp->tweets[j].comments[k]);
			}
		}
		temp = temp->next;
	}
	fclose(fcc);
	
	FILE *ft;
	ft = fopen("ttime.txt","r");
	if(head==NULL)
		return;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(j=1;j<=temp->ctweets;j++){
				fscanf(ft,"%lld\t",&temp->tweets[j].t);
			}
		}
		temp = temp->next;
	}
	fclose(ft);
	
}
void export_tweets(){
	if(head==NULL)
		return;
	FILE  *fp;
	fp = fopen("tweets.txt","w");
	rewind(fp);
	temp = head;
    int k;
    while(temp!=NULL){
		if(temp->ctweets != 0){
			for(k=1 ; k <= temp->ctweets ; k++){
				
				fprintf(fp,"%s\t",charto_(temp->tweets[k].body));
			
			}
		}
		temp = temp->next;
	}
	fclose(fp);
	
}

void import_tweets(){
	FILE *fp;
	fp = fopen("tweets.txt","r");
	rewind(fp);
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(i=1 ; i<=temp->ctweets ; i++){
				fscanf(fp,"%s\t",temp->tweets[i].body);
			}
		}
		temp= temp->next;
	}
	fclose(fp);
	
	}

void twitter_layout(){
	system("CLS");
	printf("\n======================================================\n");
    printf("                   T W I T T E R                           ");
    printf("\n======================================================\n\n");
}

void import_list(){
	account *newacc;	
	FILE *fp,*fing,*fwers,*ft;
	fp = fopen("accounts.txt","r");
	fing = fopen("following.txt","r");
	fwers = fopen("followers.txt","r");
	rewind(fp);
	rewind(fing);
	rewind(fwers);
	if(feof(fp))
		return;
	newacc = (account*)malloc(sizeof(account));
	newacc->next=NULL;
	while(fscanf(fp,"%s\t",newacc->name),
		fscanf(fp,"%s\t",newacc->username),
		fscanf(fp,"%s\t",newacc->password),
		fscanf(fp,"%s\t",&newacc->gender),
		fscanf(fp,"%lld\t",&newacc->mobile),
		fscanf(fp,"%d\t",&newacc->age),
		fscanf(fp,"%d\t",&newacc->cfollowing),
		fscanf(fp,"%d\t",&newacc->cfollowers),
		fscanf(fp,"%d\t",&newacc->ctweets))
		{
			for( i=1 ; i<=newacc->cfollowing ; i++)
				fscanf(fing,"%s\t",newacc->following[i]);
			for( i=1 ; i<=newacc->cfollowers ; i++)
				fscanf(fwers,"%s\t",newacc->followers[i]);
			if(head==NULL) {
					head = newacc;
					last = newacc;
				}
			if(feof(fp))
				break;

			newacc->next = (account*)malloc(sizeof(account));
			newacc = newacc->next;
			newacc->next=NULL;
			last = newacc;	
		}
	fclose(fp);	
	fclose(fing);
	fclose(fwers);
}

void export_list(){
	FILE *fp,*fing,*fwers;
	temp = head;
	if(temp == NULL)
		return;
	fp = fopen("accounts.txt","w");
	fing = fopen("following.txt","w");
	fwers = fopen("followers.txt","w");
	rewind(fp);
	rewind(fwers);
	rewind(fing);
	while(temp!=NULL){
	fprintf(fp,"%s\t",temp->name);
	fprintf(fp,"%s\t",temp->username);
	fprintf(fp,"%s\t",temp->password);
	fprintf(fp,"%s\t",temp->gender);
	fprintf(fp,"%lld\t",temp->mobile);
	fprintf(fp,"%d\t",temp->age);
	fprintf(fp,"%d\t",temp->cfollowing);
	fprintf(fp,"%d\t",temp->cfollowers);
	fprintf(fp,"%d\t",temp->ctweets);
	
	for( i=1 ; i<=temp->cfollowing ; i++)
		fprintf(fing,"%s\t",temp->following[i]);
	for( i=1 ; i<=temp->cfollowers ; i++)
		fprintf(fwers,"%s\t",temp->followers[i]);	
		
	temp=temp->next;
	}
	
	fclose(fing);
	fclose(fwers);
	fclose(fp);
}

void signup()
{

    account *newacc;
    newacc = (account*)malloc(sizeof(account));
    char ch,str[20];
    int p;
    
	tag1:
	system("CLS");
    twitter_layout();
    printf("\nCREATE YOUR ACCOUNT:\n");
    printf("(1) -> 2 -> 3 -> 4 \n\n");
    printf("Enter Name : ");        scanf("%s",newacc->name);
    if(access(newacc->name,1,newacc,0)==0)
    	goto tag1;
    
	tag2:
	system("CLS");
    twitter_layout();
    printf("\nCREATE YOUR ACCOUNT:\n");
    printf("1 -> (2) -> 3 -> 4 \n\n");
    printf("Enter UserName : ");    fflush(stdin);   scanf("%s",newacc->username);  
    if(access(newacc->username,2,newacc,0)==0)
    	goto tag2;
    
    fflush(stdin);
	tag3:	
	system("CLS");
    twitter_layout();
    printf("\nCREATE YOUR ACCOUNT:\n");
    printf("1 -> 2 -> (3) -> 4 \n\n");
    printf("Enter Password : ");	
    
    p=0;
	fflush(stdin);
	do{ 
        newacc->password[p]=getch(); 
        if(newacc->password[p]!='\r'){ 
            printf("*"); 
        } 
        p++; 
    }while(newacc->password[p-1]!='\r'); 
    newacc->password[p-1]='\0';
    
    if(password_access(newacc->password)==0)
    	goto tag3;
    
    printf("\nEnter Password Again : "); 
    
    p=0;
	fflush(stdin);
	do{ 
        str[p]=getch(); 
        if(str[p]!='\r'){ 
            printf("*"); 
        } 
        p++; 
    }while(str[p-1]!='\r'); 
    str[p-1]='\0';
    
    printf("\n");
    
    if(strcmp(newacc->password,str)!=0){
    	printf("PassWord Mismatched Tryagain!\n");
		getch();
    	goto tag3;
		}
    
		
    printf("\nGender (M/F) : ");  scanf("%s",newacc->gender);
	fflush(stdin);
    
    tag4:
    system("CLS");
    twitter_layout();
    printf("\nCREATE YOUR ACCOUNT:\n");
    printf("1 -> 2 -> 3 -> (4) \n\n");
	
	printf("Phone Number : ");
	scanf("%lld",&newacc->mobile);
	if(countdigit(newacc->mobile) != 10)
		{
			printf("\nEnter Valid PhoneNumber!");
			getch();
			goto tag4;
		}
    if(access(NULL,4,newacc,newacc->mobile)==0)
    	goto tag4;
    	
    printf("\nAge : ");           scanf("%d",&newacc->age);
    
    newacc->cfollowing = 0;
    newacc->cfollowers = 0;
    newacc->ctweets = 0;
    newacc->next=NULL;
    
    int x;
    printf("\nDo you want to continue the signup process?\n1: Yes    0: No\n\nYour Choice : ");
    scanf("%d",&x);
    if(x==0){
    	system("CLS");
    	twitter_layout();
    	printf("\nCREATE YOUR ACCOUNT:\n");
    	printf("1 -> 2 -> 3 -> 4 -> (CANCEL)\n\n");
    	printf("Signup process Cancelled Successfully!\n");
    	getch();
    	return;
	}

    if(head==NULL){
    	head=newacc;
    	last=newacc;
		}
	else{
		last->next=newacc;
		last=newacc;
	}

	system("CLS");
    twitter_layout();
    printf("\nCREATE YOUR ACCOUNT:\n");
    printf("1 -> 2 -> 3 -> 4 -> (DONE)\n\n"); 
	printf("YOUR ACCOUNT DETAILS IMPORTED SUCCESSFULLY!!\n\nPlease login again...\n"); 
	getch();
	
	export_notify(); 
	export_tlc();
	export_tweets();
	export_tc();
    export_list();
    
}

account* login(){
	char usern[20],passw[10],ch;
	int p=0;
	system("CLS");
	twitter_layout();
	printf("\n\nLOGIN TO TWITTER\n");
	printf("(1) -> 2 \n\n");
	printf("Enter UserName : ");	
	scanf("%s",usern);
	
	system("CLS");
	twitter_layout();
	printf("\n\nLOGIN TO TWITTER\n");
	printf("1 -> (2) \n\n");
	printf("Enter UserName : %s\n",usern);
	printf("Enter Password : ");
	fflush(stdin);
	do{ 
        passw[p]=getch(); 
        if(passw[p]!='\r'){ 
            printf("*"); 
        } 
        p++; 
    }while(passw[p-1]!='\r'); 
    passw[p-1]='\0';
	
	system("CLS");
	twitter_layout();
	printf("\n\nLOGIN TO TWITTER\n");
	printf("1 -> 2 -> DONE\n\n");
	printf("Gathering Information...\n\nPress any key to continue ->");
	getch();
	temp = head;
	while(temp!=NULL){
		if(strcmp(temp->username,usern)==0 && strcmp(temp->password,passw)==0)
			return temp;
		temp=temp->next;
	}
	
	printf("Invalid UserName or Password\nPlease Check Again :)");
	getch();
	return NULL;	
}

void search_user(account* acc){
	

	account *STACK[50];
	int top;
	system("cls");
	twitter_layout();
	printf("SEARCH USER : ");
	top=0;
    printf("\n\nEnter UserName : ");
    char str[20];
    int found  = 0,choice;
    scanf("%s",str);
	temp = head;
	int count = 1;
	printf("\nSelect : \n\n");
	while(temp!=NULL){
		if(strstr(temp->name,str)!=NULL || strstr(temp->username,str)!=NULL)
			{
				found = 1;
				printf("%d : %s\n",count++,to_upper(temp->name));
				printf("    Followers : %d | Following : %d \n\n",temp->cfollowers,temp->cfollowing);	
				STACK[++top]=temp;
			}
		temp=temp->next;
	}
	if(found == 0){
		printf("\nUser Not Found!");
	}
	printf("\n\n0 : <-- Back\n\nYour Choice : ");
	scanf("%d",&choice);
	if(choice==0)
		return;
	else if (choice<=top)
		view_profile(acc,STACK[choice]);
}

account* address(char str[]){

	int found=0;
	account *add;
	add = head;
	while(add!=NULL){
		if(strcmp(str,add->username)==0){
			found=1;
			break;
		}
		add=add->next;
	}
	if(found==1)
		return add;
	else	
		return NULL;
}

char * to_upper(char str[]){
	for(i=0;i<strlen(str);i++)
		str[i]=toupper(str[i]);
	return str;
}

char * to_lower(char str[]){
	for(i=0;i<strlen(str);i++)
		str[i]=tolower(str[i]);
	return str;
}

void follow(account *acc1,account *acc2){
	
	strcpy(acc1->following[++acc1->cfollowing],acc2->username);
	strcpy(acc2->followers[++acc2->cfollowers],acc1->username);
	printf("\n%s started following %s\n",acc1->username,acc2->username);
	
	char str[50];
	strcpy(str,acc1->username);
	strcat(str,F);
	push_notify(acc2,str,acc1);	
}

void unfollow(account *acc1,account *acc2){
	
	int ii;
	for( ii=1 ; ii<=acc1->cfollowing ; ii++){
		if(strcmp(acc1->following[ii],acc2->username)==0){
			while(ii<=acc1->cfollowing){
				strcpy(acc1->following[ii],acc1->following[ii+1]);
				ii++;
			}
			acc1->cfollowing--;
			break;
		}
	}
	
	for( ii=1 ; ii<=acc2->cfollowers ; ii++){
		if(strcmp(acc2->followers[ii],acc1->username)==0){
			while(ii<=acc2->cfollowers){
				strcpy(acc2->followers[ii],acc2->followers[ii+1]);
				ii++;
			}
			acc2->cfollowers--;
			break;
		}
	}
	printf("\n%s unfollowed %s\n",acc1->username,acc2->username);
	
	char str[50];
	strcpy(str,acc1->username);
	strcat(str,F);
	pop_notify(acc2,str);
}

char* charto_(char str[]){
	for(i=0;i<strlen(str);i++){
		if(str[i]==' ')
			str[i]='_';
	}
	return str;
}

char* _tochar(char str[]){
	for(i=0;i<strlen(str);i++){
		if(str[i]=='_')
			str[i]=' ';
	}
	return str;
}

int isfollowing(account *acc1,account *acc2){
	int x;
	for(x=1;x<=acc1->cfollowing;x++){
		if(strcmp(acc1->following[x],acc2->username)==0)
			return 1;
	}
	return 0;
}

int isfollower(account *acc1,account *acc2){
	int x;
	for(x=1;x<=acc1->cfollowers;x++){
		if(strcmp(acc1->followers[x],acc2->username)==0)
			return 1;
	}
	return 0;
}
int countdigit(long long n) 
{ 
    if (n == 0) 
        return 0; 
    return 1 + countdigit(n / 10); 
}
void search_all(account *acc1){
	
	system("CLS");
	twitter_layout();
	printf("SEARCH EVERYTHING : ");
	
	account *acc[100];
	struct tweet *twt[100];
	int count=0,x;
	temp = head;
	char string[50];
	printf("\n\nType something you want to search : ");
	fflush(stdin);
	scanf("%[^\n]s",string);
	printf("\n\nAccounts : \n");
	int found=0;
	while(temp!=NULL){
		if(strstr(temp->name,string)!=NULL || strstr(temp->username,string)!=NULL){
			found=1;
			acc[++count]=temp;
			printf("\n%d : %s\n",count,temp->name);
			printf("Followers: %d | Following: %d | Tweets: %d\n\n",temp->cfollowers,temp->cfollowing,temp->ctweets);
		}
		temp=temp->next;
	}
	if(found==0)
		printf("No account found!\n\n");
	int base = count;
	printf("Tweets : \n");
	found=0;
	temp = head;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(x=1;x<=temp->ctweets;x++){
				if(strstr(temp->tweets[x].body,string)!=NULL){
					found = 1;
					twt[++count]=&temp->tweets[x];
					acc[count]=temp;
					printf("\n%d : %s\n",count,_tochar(temp->tweets[x].body));
					printf("Tweeted by : %s | Likes : %d | Comments : %d\n\n",temp->username,temp->tweets[x].clikes,temp->tweets[x].ccomments);
				}
			}
		}
		temp=temp->next;
	}
	if(found==0)
		printf("No related tweets found!\n\n");
	printf("0 : <-- Back\n\nYour Choice : ");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
		return;
	else if(choice<=base)
		view_profile(acc1,acc[choice]);
	else if(choice<=count)
		view_tweet(twt[choice],acc1,acc[choice]);
}

void search_hash(account *acc1){
	

	system("CLS");
	twitter_layout();
	printf("SEARCH HASHTAGS : ");
	
	printf("\n\nType #hashtag you want to search : ");
	char str[20];
	int x;
	scanf("%s",str);
	if(str[0]!='#')
		{
			char *hash;
			strcpy(hash,"#");
			strcat(hash,str);
			strcpy(str,hash);
		}
	temp = head;
	struct tweet *twt[100];
	account *acc[100];
	int count=0,found=0;
	while(temp!=NULL){
		if(temp->ctweets > 0){
			for(x=1;x<=temp->ctweets;x++){
				if(strstr(temp->tweets[x].body,str)!=NULL){
					found = 1;
					twt[++count]=&temp->tweets[x];
					acc[count]=temp;
					printf("\n%d : %s\n",count,_tochar(temp->tweets[x].body));
					fflush(stdin);
					printf("Tweeted by : %s | Likes : %d | Comments : %d\n\n",temp->username,temp->tweets[x].clikes,temp->tweets[x].ccomments);
				}
			}
		}
		temp=temp->next;
	}
	if(found==0)
		printf("No related tweets found!\n\n");
	printf("0 : <-- Back\n\nYour Choice : ");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
		return;
	else if(choice<=count)
		view_tweet(twt[choice],acc1,acc[choice]);
}


void displayall_tweets(account *acc1){
	
	twitter_layout();
	struct tweet twt[100];
	int top,l,choice;
	A:
	top=0;	
	for(j=1;j<=acc1->cfollowing;j++){
		temp=address(acc1->following[j]);
		for(k=1;k<=temp->ctweets;k++){
			twt[top++]=temp->tweets[k];
		}	
	}
	for(j=1;j<=acc1->ctweets;j++)
		twt[top++]=acc1->tweets[j];
	
	qsort(twt,top,sizeof(struct tweet),compare);
	
	int k=1;
	for(j=0;j<top;j++){
		printf("%d: %s\n",j+1,_tochar(twt[j].body));
		printf("    %d likes    %d comments\n\n",twt[j].clikes,twt[j].ccomments);
	}
	
	printf("0: <-- Back\n\nYour Choice : ");
	scanf("%d",&choice);
	
	if(choice==0)
		return;
	else 
		view_tweet(&twt[choice-1],acc1,tweet_owner(&twt[choice-1]));	
	system("CLS");
	twitter_layout();
	goto A;
}

int compare(const void * x, const void * y)
{
  long long int l = ((struct tweet *)x)->t;
  long long int r = ((struct tweet *)y)->t;
  return (r-l);
}

account* tweet_owner(struct tweet twt[]){
	temp=head;
	while(temp!=NULL){
		if(temp->ctweets>0){
			for(j=1;j<=temp->ctweets;j++){
				if(twt==&temp->tweets[j])
					return temp;
			}
		}
		temp=temp->next;
	}
	return NULL;
}

int password_access(char str[]){
	
	if(strlen(str)<8){
		printf("\nPassword length should be atleast 8 character!");
		getch();
		return 0;
	}
	int x,dcheck=0,ccheck=0;
	for(x=0;x<strlen(str);x++){
		if(isdigit(str[x]))
			dcheck=1;
		if(isalpha(str[x]))
			ccheck=1;
	}
	if(dcheck==0){
		printf("\nPassword should contain atleast one digit (0/9)");
		getch();
		return 0;
	}
	if(ccheck==0){
		printf("\nPassword should contain atleast one character (a/z),(A/Z)");
		getch();
		return 0;
	}
	return 1;
}

void mention(char str[],account *acc){
	int x;
	for(x=0;x<strlen(str);x++){
		if(str[x]=='@'){
			x++;
			char newstr[20];
			int count=0;
			while(1){
				if(str[x]=='_')	break;
				if(str[x]==' ')	break;
				if(str[x]=='\0')break;
				newstr[count++]=str[x];
				x++;
			}
			newstr[count]='\0';
			for(temp=head;temp!=NULL;temp=temp->next){
				if(strcmpi(temp->username,newstr)==0){
					char nstr[30],t[30];
					strcpy(nstr,acc->username);
					strcat(nstr,M);
					strncpy(t,str,10);
					t[10]='\0';
					strcat(nstr,t);
					push_notify(temp,nstr,acc);
				}
			}
		}
	}
}
