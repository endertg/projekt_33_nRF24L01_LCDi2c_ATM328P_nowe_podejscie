#ifndef KOMUNIKACJA_H
#define KOMUNIKACJA_H

#define NEW_LINE uart_puts("\n\r")
#define echo 1


extern uint8_t odbierz_komende(void);
//stare komendy
void odbierz(void);
void odbierz_ciag(int dlugosc,char *tresc);
int oczekuj_ciag(const char *tresc);
void wyslij_SMS(char numer[],char tresc[]);
void pokaz_siec(void);
void lista_SMS(void);
void sim_info(void);
void text_mode(void);
void komenda_AT(char komenda[]);
#endif //KOMUNIKACJA_H
