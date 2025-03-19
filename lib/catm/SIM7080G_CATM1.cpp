#include "SIM7080G_CATM1.hpp"

void setup_CATM1()
{
    //You must turn off GNSS before turning on CATM1

    //see datasheet
    Send_AT("AT+CNMP=38");

    /*
    WARNING on the ARGALI SIM C3 V1.0 the SIMCOM processor used is
    SIM7080G-M that does not feature NB-IOT.
    1 -> CAT-M1 et 2 -> NB-IOT
    */
    Send_AT("AT+CMNB=1");

    //APP Network Deactive(PDP context)
    Send_AT("AT+CNACT=0,0");

    //paramétrage de l'APN (Access Point Name)
    Send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
    Send_AT("AT+CGNAPN");
    Send_AT("AT+CNCFG=0,1,iot.1nce.net");

    /*
    We wait for the SIM7080G to register to the local 4G antenna
    Correct registration : 
    AT+CEREG?
    +CEREG: 0,5
    */
    Send_AT("AT+CEREG?");

    //APP Network Active (PDP context)
    //You should wait for a valid response : +APP PDP: 0,ACTIVE
    Send_AT("AT+CNACT=0,1");
    

    //informations for you on CAT-M1 connexion
    Send_AT("AT+CGATT?");
    Send_AT("AT+CNACT?");
    Send_AT("AT+GSN");
    Send_AT("AT+CCID");
    Send_AT("AT+COPS?");
    Send_AT("AT+CEREG?");
    //signal quality
    Send_AT("AT+CSQ");
}

void loop_CATM1()
{
    Send_AT("AT+CEREG?");
    Send_AT("AT+CSQ");
}
