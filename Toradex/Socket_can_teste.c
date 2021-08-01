//Definições e bibliotecas
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

#include <string.h>
#include <sys/ioctl.h>
#include <sys/timerfd.h>

#ifndef __DEFS_H_
#define __DEFS_H_

#define SUCCESS          (0)
#define FAILURE          (1)

#define IF_VCAN0		"vcan0"

#endif

//Declaração das funções e variaveis estáticas
static void MakeAndSendFrame(void);
static void PrintCANFrame(struct can_frame *fra);
static uint8_t CANIfcInit(void);
static int can_fd;


/*Função que cria a mensagem no padrão do protocolo can com o ID e tamanho da mensgem e depois envia a mensagem "frente" via a struct do formato can_frame */
static void MakeAndSendCANFrame_frente(void)
{
    struct can_frame fra;
    uint8_t size = 0;
    
    
    fra.can_id = 0x100; //coloca o id da comunicação CAN
    fra.can_dlc = 2; //número de bytes da mensagem
   
    fra.data[0] = 0x66;
    fra.data[1] = 0x72;
    //fra.data[2] = ;
    //fra.data[3] = ;
    //fra.data[4] = ;
    //fra.data[5] = ;
    //fra.data[6] = ;
    //fra.data[7] = ;

//Check se a mensagem conseguiu ser criada e enviada com sucesso
    size = send(can_fd, &fra, sizeof(struct can_frame), MSG_DONTWAIT);
    if(size != sizeof(struct can_frame))
    {
        printf("A mensagem não pode ser criada e enviada\n");
        return;
    }
    else
    {
        //se ela for enviada com sucesso, printa a mensagem
        PrintCANFrame(&fra);
        printf("mensagem enviada com sucesso\n");
    }
}


/*Função que cria a mensagem no padrão do protocolo can com o ID e tamanho da mensgem e depois envia a mensagem "tras" via a struct do formato can_frame */
static void MakeAndSendCANFrame_tras(void)
{
    struct can_frame fra;
    uint8_t size = 0;
    
    
    fra.can_id = 0x100; //coloca o id da comunicação CAN
    fra.can_dlc = 2; //número de bytes da mensagem
   
    fra.data[0] = 0x74;
    fra.data[1] = 0x72;
    //fra.data[2] = ;
    //fra.data[3] = ;
    //fra.data[4] = ;
    //fra.data[5] = ;
    //fra.data[6] = ;
    //fra.data[7] = ;

//Check se a mensagem conseguiu ser criada e enviada com sucesso
    size = send(can_fd, &fra, sizeof(struct can_frame), MSG_DONTWAIT);
    if(size != sizeof(struct can_frame))
    {
        printf("A mensagem não pode ser criada e enviada\n");
        return;
    }
    else
    {
        //se ela for enviada com sucesso, printa a mensagem
        PrintCANFrame(&fra);//função que printa a mensagem no formato CAN
        printf("mensagem enviada com sucesso\n");
    }
}

/*Função utilizada para printar a mensagem enviada via o protocolo CAN */
static void PrintCANFrame(struct can_frame *fra)
{
    if(fra != NULL)
    {
        printf("ID = %04x ", (*fra).can_id);
        printf("DLC = [%02x] - ", (*fra).can_dlc);
        for(int i = 0; i < (*fra).can_dlc; i++)
        {
            printf("B%d|%02x ", i, (*fra).data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Mensagem Vazia\n");
    }
}


/*Função que cria o socket e estabelece a comunicação via can */
static uint8_t CANIfcInit(void)
{
    //cria as variaveis do tipo struct
    struct ifreq ifr;
    struct sockaddr_can addr;

    /*cria o socket */
    can_fd = socket(AF_CAN, SOCK_RAW, CAN_RAW); //abertura do socket do tipo RAW, segundo a documentação do CAN_Utils
    
    if (can_fd < 0)//verifica se o socket conseguiu ser criado
    {
        printf("Falha na abertura do Socket... Saindo!\n");
        return FAILURE;
    }
    strcpy(ifr.ifr_name, IF_VCAN0);

    //Associa o socket com a interface "Vcan0"
    if(ioctl(can_fd, SIOCGIFINDEX, &ifr) < 0) //verifica se existe a interface Vcan0
    {
        printf("Não foi encontrada a porta Vcan0...\n");
        return FAILURE;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)//Verifica se a conexão foi estabelecida com sucesso
    {
        printf("Não foi possível estabelecer a conexão via socket\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* Função main para realizar a escolha da mensagem a ser enviada*/
 int escolha;
int main(int argc, char *argv[])
{
    
    if (CANIfcInit() == SUCCESS) //inicia a comunicação Can e entra no programa caso ela tenha sucedido
    {
    	while(1)
    	{
    		printf("Escolha o número da função a ser realizada pela Formiga:\n 1 - Formiga ir pra frente \n 2 - Formiga ir para trás\n 3 - Fechar conexão\n");
    		printf("Digite o número:");
    		scanf("%d", &escolha);
    		
    	
    		if(escolha==1)
    		{
    			MakeAndSendCANFrame_frente();
    		}
    	
    		if(escolha==2)
    		{
    			MakeAndSendCANFrame_tras();
    		}
    		if(escolha==3)
    		{
    			break;
    		}
    	}
    }

    //fechando a conexão
    if(can_fd > 0)
    {
        close(can_fd);
    }

    printf("Saindo...\n");
    return 0;
}
