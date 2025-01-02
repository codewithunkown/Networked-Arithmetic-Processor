#include"header.h"

/* Macro */
#define BUFFER 50 

/* Function Prototype */
static int validateString(const char*);
static int validateOperator(const char);

/* Function Definition */
int validateString(const char *str) 
{
    int c = 0;
    long num;
    if (*str == '-' || *str == '+') {
        str++; 
    }

    while (*str) {
        if (!isdigit(*str)) { // isdigit() returns non zero value if it's Digit 
            return 1; // not a digit
        } else {
            c++;
            str++;
        }
    }

    if (c > 10) {
        printf(GRAYBG"Overflow: Input Value Ranges [-2147483647] To [2147483647]."END"\n");
        return 1;
    } else {
        c = 0;
        num = atol(str);

        if (num < INT_MIN || num > INT_MAX) {
            printf(GRAYBG"Overflow: Input Value Ranges [-2147483647] To [2147483647]."END"\n");
            return 1;
        }
    }

    return 0;
}

int validateOperator(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}

void main(int argc, char** argv)
{
    ////////////////////////////////////////////////////////////////////////////////
    int sfd, len, flag, flag2;
    int num1Valid, num2Valid;
    char str1[BUFFER], str2[BUFFER], strOp[BUFFER];
    long long result;
    struct sockaddr_in server, client;
    struct in_addr addr;
    struct st data;

    if (argc != 3) {
        printf(RED"Usage:Enter Valid Server IP and Port No..."END"\n");
        return;
    }

    /* Port Number Validation */
    flag = atoi(argv[2]);
    if (flag < PORTMIN || flag > PORTMAX) {
        printf(RED"Invalid Port No Please Enter Again."END"\n");
        return;
    }

    /* IP Address Validation */
    if (inet_pton(AF_INET, argv[1], &addr) != 1) {
        printf(RED"Invalid IP Address Please Enter Again."END"\n");
        return;
    }

    /* SOCKET */
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("Socket...");
        return;
    }
    perror(BLUEU "Socket:"END);

    /* CONNECT */
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    len = sizeof(server);

    if (connect(sfd, (struct sockaddr*)&server, len) < 0) {
        perror("Connect..");
        return;
    }
    perror(BLUEU "Connect:"END);

    /* Printing Use Case Message */
    printf(GRAYBG"The Client will Take 3 Input i.e Two Integer Numbers and One Operator."END"\n\n");
    printf(GRAYBG"Input Format: Num1 <ENTER> Operator <ENTER> Num2 <ENTER>):"END"\n\n");
    printf(GRAYBG"Valid Operators: '+', '-', '*', '/'"END"\n\n");

    while (1) {
        printf(RED"Enter The Data Num1 <ENTER> OP <ENTER> Num2 <ENTER>):"END"\n");
        str1[BUFFER] = 0, str2[BUFFER] = 0, strOp[BUFFER] = 0;
        scanf("%s %s %s", str1, strOp, str2);

        /* Printing Proper Message Related To num1 & num2 Input */
        num1Valid = validateString(str1);
        num2Valid = validateString(str2);
        flag2 = (strlen(strOp) != 1) || (!validateOperator(strOp[0]));

        if (num1Valid && num2Valid) 
        {
            printf((flag2 ? RED"Invalid Input: Num1, Num2 & Operator. Please Enter Again."END"\n\n" :
                            RED"Invalid Input: Num1 or Num2 Please Enter Again."END"\n\n"));
            continue;
        } 
        else if (num1Valid || num2Valid) {
            printf((flag2 ? (num1Valid ?RED"Invalid Input: Num1 & Operator. Please Enter Again."END"\n\n" :
                                        RED"Invalid Input: Num2 & Operator. Please Enter Again."END"\n\n") :
                            (num1Valid ? RED"Invalid Input: Num1 Should Be a Valid Integer."END"\n\n" :
                                         RED"Invalid Input: Num2 Should Be a Valid Integer."END"\n\n")));
            continue;
        }

        data.Num1 = atoi(str1);
        data.Num2 = atoi(str2);

        /* Validate operator */
        if (strlen(strOp) != 1 || !validateOperator(strOp[0])) {
            printf(RED"Invalid Input: Operator Should Be '+' '-' '*' '/'"END"\n\n");
            continue;
        }
        data.Op = strOp[0];

        write(sfd, &data, sizeof(data));
        read(sfd, &result, sizeof(result));

        if (result < INT_MIN || result >INT_MAX) {
            printf(GRAYBG"Result Overflow."END"\n");
            continue;
        }

        printf(GREENWFG"Result: %lld"END"\n", result);
    }
}
