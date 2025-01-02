#include"header.h"
/*Macro*/
#define REQ_QUEUE 5

/*Function Decleration*/
static void handleClient(int);

/*Function Definetion*/
void handleClient(int cfd)
{
    long long result;
    struct st data;

    while(1) 
    {
        result=0; 
        read(cfd, &data, sizeof(data));

        switch(data.Op)
        {
            case '+':
                result = data.Num1 + data.Num2;
                break;
            case '-':
                result = data.Num1 - data.Num2;
                break;
            case '*':
                result = data.Num1 * data.Num2;
                break;
            case '/':
                if(data.Num2 != 0)
                {
                    result = data.Num1 / data.Num2;
                }
                else 
                {
                    printf(RED"Dividing By Zero"END"\n");
                    continue;
                }
                break;
            default:
                printf(RED"Invalid Input"END"\n");
                break;
        }
        printf(GREEN"Result Send %lld"END "\n",result);
        write(cfd, &result, sizeof(result));
    }
}

void main(int argc, char **argv) 
{
    int sfd, cfd,len,flag;
    struct sockaddr_in server, client;

    if(argc != 2) 
    {
        printf(RED"Usage: Enter Valid Port Number...."END"\n:");
        return;
    }

    /*Port NUmber Validation*/
    flag=atoi(argv[1]);
    if(flag < PORTMIN || flag > PORTMAX)
    {
        printf(RED"Invalid Port No Please Enter Again"END"\n");
        return;
    }
    printf(GRAYBG"\nInput Format For Client: <IP Address> <Port Number> <Enter>"END"\n\n");

    /*SOCKET*/
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("Socket..");
        return;
    }
    perror(BLUEU "Socket: "END);

    /*BIND*/
    server.sin_family=AF_INET;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    len = sizeof(server);

    if(bind(sfd, (struct sockaddr*)&server, len) < 0)
    {
        perror("Bind..");
        return;
    }
    perror(BLUEU "Bind: "END);

    /*LISTEN*/
    if(listen(sfd, REQ_QUEUE) < 0)
    {
        perror("Listen..");
        return;
    }
    perror(BLUEU "Listen:"END);

    /*ACCEPT*/
    printf(RED"Before Accepting Client Req(Wait..)..."END"\n");

    while(1) 
    {
        cfd = accept(sfd, (struct sockaddr*)&client, &len);

        if(cfd < 0) 
        {
            perror("Accept:..");
            continue;
        }
        perror(BLUEU "Accept:"END);

        printf(GREENB"Client Request Accepted"END"\n");

        if(fork() == 0)
        { // Child process
            close(sfd); // Close listening socket in child process
            handleClient(cfd); // Handle client request
            close(cfd); // Close client socket in child process
            exit(0); // Terminate child process after handling client
        }

        close(cfd); // Close client socket in parent process
    }

    close(sfd); // Close listening socket
}
