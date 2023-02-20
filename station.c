#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"


/* Creeaza o gara cu un numar fix de peroane.
 * 
 * platforms_no: numarul de peroane ale garii
 *
 * return: gara creata
 */
TrainStation* open_train_station(int platforms_no) {
    TrainStation* gara = malloc(sizeof(TrainStation));
    gara->platforms_no = platforms_no;
    gara->platforms = malloc(platforms_no*sizeof(Train));
    for(int i=0; i<gara->platforms_no;i++) {
        gara->platforms[i] = NULL;
    }
    return gara;
}


/* Elibereaza memoria alocata pentru gara.
 *
 * station: gara existenta
 */
void close_train_station(TrainStation *station) {
    if(station == NULL) {
         free(station);
    }
    else {
        if(station->platforms == NULL) {
            free(station->platforms);
            free(station);
        }
        else {
            
            for(int i = 0;i< station->platforms_no; i++) {
                if(station->platforms[i]!= NULL) {
                    if(station->platforms[i]->train_cars != NULL) {
                        TrainCar* vagon = station->platforms[i]->train_cars;
                        while(vagon != NULL) {
                            TrainCar* anterior = vagon;
                            vagon = vagon->next;
                            free(anterior);
                        }
                    }
                    free(station->platforms[i]);
                }
            }
            free(station->platforms);
            free(station);
        }
        
    }
}


/* Afiseaza trenurile stationate in gara.
 *
 * station: gara existenta
 * f: fisierul in care se face afisarea
 */
void show_existing_trains(TrainStation *station, FILE *f) {
    if(station != NULL && station->platforms != NULL ) {
        for(int i = 0 ;i< station->platforms_no; i++){
            fprintf(f,"%d: ",i);
            if(station->platforms[i] != NULL ){
                    fprintf(f,"(%d)", station->platforms[i]->locomotive_power);
                        if(station->platforms[i]->train_cars != NULL) {
                            TrainCar* vagon = station->platforms[i]->train_cars;
                            while(vagon != NULL) {
                                fprintf(f,"-|%d|",vagon->weight);
                                vagon = vagon->next;
                            } 
                        }
                    }fprintf(f,"\n");
                    
                }   
            }
}
       



/* Adauga o locomotiva pe un peron.
 * 
 * station: gara existenta
 * platform: peronul pe care se adauga locomotiva
 * locomotive_power: puterea de tractiune a locomotivei
 */
void arrive_train(TrainStation *station, int platform, int locomotive_power) {
    if(station != NULL && station->platforms != NULL ) {
        if(platform >=0 && platform < station->platforms_no) {
            if(station->platforms[platform] == NULL) {
                station->platforms[platform] = malloc(sizeof(Train));
                station->platforms[platform]->locomotive_power = locomotive_power;
                station->platforms[platform]->train_cars = NULL; 
            }
            
        }
    }
}


/* Elibereaza un peron.
 * 
 * station: gara existenta
 * platform: peronul de pe care pleaca trenul
 */
void leave_train(TrainStation *station, int platform) {
    if(station != NULL && station->platforms != NULL) {
        if(platform >=0 && platform < station->platforms_no) {
            if(station->platforms[platform] == NULL) {
                return;
            }
            else {
                if(station->platforms[platform]->train_cars != NULL ) {
                    TrainCar* vagon = station->platforms[platform]->train_cars;
                    while(vagon != NULL) {
                        TrainCar* precedent = vagon;
                        vagon = vagon->next;
                        free(precedent);
                        precedent = NULL;
                        
                    }
                    station->platforms[platform]->train_cars = NULL;
                    
                }
                free(station->platforms[platform]);
                station->platforms[platform] = NULL;
                
            }
        }
    }
    
}


/* Adauga un vagon la capatul unui tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului adaugat
 */
void add_train_car(TrainStation *station, int platform, int weight) {
    
    if(station != NULL && station->platforms != NULL) {
        if(platform >=0 && platform < station->platforms_no) {
            if(station->platforms[platform] != NULL ){
                if(station->platforms[platform]->train_cars == NULL){
                    station->platforms[platform]->train_cars = malloc(sizeof(TrainCar));
                    station->platforms[platform]->train_cars->weight = weight;
                    station->platforms[platform]->train_cars->next = NULL;
                }
                else {
                    TrainCar* vagon = station->platforms[platform]->train_cars;
                    while(vagon->next != NULL) {
                        vagon = vagon->next;
                    }
                    TrainCar* inserat = malloc(sizeof(TrainCar));
                    inserat->weight = weight;
                    inserat->next = NULL;
                    vagon->next = inserat;
                }
            }
        }
    }
    
}


/* Scoate vagoanele de o anumita greutate dintr-un tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void remove_train_cars(TrainStation *station, int platform, int weight) {
    if(station == NULL || station->platforms == NULL)
        return;
    if(platform < 0 || platform >= station->platforms_no)
        return;
    if(station->platforms[platform] == NULL)
        return;
    if(station->platforms[platform]->train_cars == NULL)
        return;
    TrainCar* vagon = station->platforms[platform]->train_cars;
    TrainCar* prev = NULL;
    while(vagon != NULL){
        if(vagon->weight == weight && prev == NULL) {
            prev = vagon;
            station->platforms[platform]->train_cars = vagon->next;
            vagon = vagon->next;
            free(prev);
            prev = NULL;
            continue;
        }
        else if (vagon->weight == weight && vagon->next == NULL) {
            prev->next = NULL;
            free(vagon);
            //vagon = NULL;
            break;
        }
        else if (vagon->weight == weight) {
            prev->next = vagon->next;
            free(vagon);
            vagon = prev->next;
            continue;
        }
        prev = vagon;
        vagon = vagon->next;

    }
}


/* Muta o secventa de vagoane dintr-un tren in altul.
 * 
 * station: gara existenta
 * platform_a: peronul pe care se afla trenul de unde se scot vagoanele
 * pos_a: pozitia primului vagon din secventa
 * cars_no: lungimea secventei
 * platform_b: peronul pe care se afla trenul unde se adauga vagoanele
 * pos_b: pozitia unde se adauga secventa de vagoane
 */
void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
    if(station == NULL )
        return;
    if(station->platforms == NULL)
        return;
    if(platform_a < 0 || platform_a >= station->platforms_no)
        return;
    if(platform_b < 0 || platform_b >= station->platforms_no)
        return;
    if(station->platforms[platform_a] == NULL)
        return;
    if(station->platforms[platform_b] == NULL)
        return;
    if(station->platforms[platform_a]->train_cars == NULL)
        return;
    if(pos_a < 1 || pos_b < 1)
        return;
    if(cars_no <= 0)
        return;
    TrainCar* vagon_start = station->platforms[platform_a]->train_cars;
    TrainCar* prev = NULL;
    for(int i = 0;i < pos_a -1 ; i++) {
        prev = vagon_start;
        vagon_start = vagon_start->next;
        if(vagon_start == NULL)
            return;
    }
    TrainCar* vagon_final = vagon_start;
    for(int i = 0; i< cars_no - 1; i++) {
        
        vagon_final = vagon_final->next;
        if(vagon_final == NULL) 
            return;
        
    }
    TrainCar* vagonB = station->platforms[platform_b]->train_cars;
    
    if(station->platforms[platform_b]->train_cars == NULL && pos_b == 1) {
        
        if(pos_a == 1)
            station->platforms[platform_a]->train_cars = vagon_final->next;
        else {
            prev->next = vagon_final->next;
            
        }
        station->platforms[platform_b]->train_cars = vagon_start;
        vagon_final->next = NULL;
        
        
    }
    else if (station->platforms[platform_b]->train_cars != NULL) {
        if(pos_b == 1) {
            if(pos_a == 1)
                station->platforms[platform_a]->train_cars = vagon_final->next;
            else 
                prev->next = vagon_final->next;
            vagon_final->next = station->platforms[platform_b]->train_cars;
            station->platforms[platform_b]->train_cars = vagon_start;
        }
        else {
            for(int i = 0; i< pos_b - 2; i++) {
                vagonB = vagonB->next;
                if(vagonB == NULL)
                    return;
            }
            if(pos_a == 1)
                station->platforms[platform_a]->train_cars = vagon_final->next;
            else 
                prev->next = vagon_final->next;
            vagon_final->next = vagonB->next;
            vagonB->next = vagon_start;
            
        }
    }  
}


/* Gaseste trenul cel mai rapid.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station) {
    int diferenta = 0, difmax = 0;
    int poz = -1;
    if(station != NULL && station->platforms != NULL) {
        for(int i = 0; i < station->platforms_no; i++){
            if(station->platforms[i] != NULL) {
                diferenta = station->platforms[i]->locomotive_power;
                if(station->platforms[i]->train_cars != NULL) {
                    TrainCar* vagon = station->platforms[i]->train_cars;
                    while (vagon != NULL) {
                        diferenta = diferenta - vagon->weight;
                        vagon = vagon->next;
                    }
                }
                if(diferenta > difmax) {
                    poz = i;
                    difmax = diferenta;
                }
            }
        }
    }
    return poz;
}


/* Gaseste trenul supraincarcat.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station) {
    int diferenta = 0;
    if(station != NULL && station->platforms != NULL) {
        for(int i = 0; i < station->platforms_no; i++){
            if(station->platforms[i] != NULL) {
                diferenta = station->platforms[i]->locomotive_power;
                if(station->platforms[i]->train_cars != NULL) {
                    TrainCar* vagon = station->platforms[i]->train_cars;
                    while (vagon != NULL) {
                        diferenta = diferenta - vagon->weight;
                        vagon = vagon->next;
                    }
                }
                if(diferenta < 0) {
                    return i;
                }
            }
        }
    }
    return -1;
}


/* Gaseste trenul cu incarcatura optima.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station) {
    int diferenta = 0, difmax = 999999;
    int poz = -1;
    if(station != NULL && station->platforms != NULL) {
        for(int i = 0; i < station->platforms_no; i++){
            if(station->platforms[i] != NULL) {
                diferenta = station->platforms[i]->locomotive_power;
                if(station->platforms[i]->train_cars != NULL) {
                    TrainCar* vagon = station->platforms[i]->train_cars;
                    while (vagon != NULL) {
                        diferenta = diferenta - vagon->weight;
                        vagon = vagon->next;
                    }
                }
                if(diferenta < difmax && diferenta >= 0) {
                    poz = i;
                    difmax = diferenta;
                }
            }
        }
    }
    return poz;
}


/* Gaseste trenul cu incarcatura nedistribuita bine.
 * 
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    int greutate = 0, gmax = 0, poz = -1;
    if(station != NULL && station->platforms != NULL) {
        for(int i = 0; i < station->platforms_no; i++) {
            if(station->platforms[i] != NULL) {
                if(station->platforms[i]->train_cars != NULL) {
                    TrainCar* vagon = station->platforms[i]->train_cars;
                    while(vagon != NULL) {
                        TrainCar* secventa = vagon;
                        greutate = 0;
                        for(int j=0; j <cars_no; j++){
                            if(secventa == NULL){
                                greutate = 0;
                                break;
                            }
                            greutate = greutate + secventa->weight;
                            secventa = secventa->next;
                        }
                        if(greutate > gmax) {
                            gmax = greutate;
                            poz = i;
                            *start_car = vagon;
                        }
                        vagon = vagon->next;
                    }
                }
            }
        }
    }
    if(gmax == 0) {
        *start_car = NULL;
        return -1;
    }
    return poz;
}


/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void order_train(TrainStation *station, int platform) {
    if(station == NULL)
        return;
    if(station->platforms == NULL)
        return;
    if(platform < 0 || platform >= station->platforms_no)
        return;
    if(station->platforms[platform] == NULL) 
        return;
    TrainCar* vagon = station->platforms[platform]->train_cars;
    while (vagon != NULL) {
        TrainCar* urm = vagon->next;
        while(urm != NULL) {
            if(urm->weight > vagon->weight) {
                int aux = urm->weight;
                urm->weight = vagon->weight;
                vagon->weight = aux;
            }
            urm = urm->next;
        }
        vagon = vagon->next;
    }
    

}


/* Scoate un vagon din trenul supraincarcat.
 * 
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station) {
    if(station == NULL)
        return;
    if(station->platforms == NULL)
        return;
    int platform = find_overload_train(station);
    if(platform < 0 || platform >= station->platforms_no)
        return ;
    if(station->platforms[platform] == NULL)
        return ;
    if(station->platforms[platform]->train_cars == NULL)
        return;


    TrainCar* vagon = station->platforms[platform]->train_cars;
    int greutate = 0;
    while(vagon != NULL){
        greutate = greutate + vagon->weight;
        vagon = vagon->next;
    }
    int poz = -1, minim = 99999,contor = -1, ok = 0;
    vagon = station->platforms[platform]->train_cars;
    int putere  = station->platforms[platform]->locomotive_power;
    while(vagon != NULL){
        contor ++;
        int diferenta = greutate - vagon->weight;
        if(putere - diferenta < minim && diferenta <= putere){
            minim = station->platforms[platform]->locomotive_power - diferenta;
            poz = contor;
            ok = 1;
        }
        vagon = vagon->next;
    }
    vagon = station->platforms[platform]->train_cars;
    if(poz == 0 ) {
        TrainCar* aux = vagon;
        station->platforms[platform]->train_cars = aux->next;
        free(aux);
        return;
    }
    for(int i =0; i<poz-1 && ok == 1; i++){
        vagon = vagon->next;
    }
    if(ok == 1){
        TrainCar* aux = vagon->next;
        vagon->next = vagon->next->next;
        free(aux);
    }
}
