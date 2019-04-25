//
// Created by chauncey on 18-6-11.
//

#include "TrafficLight.h"

void TrafficLight::setAllRed() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = 0;
        }
    }
}

void TrafficLight::setAllGreen() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = 1;
        }
    }
}

void TrafficLight::changeStatus() {
    switch (type) {
        case 3:
            this->setType(3);
            if(emStatus == 0){
                status[0][5] = 1;
            }else if(emStatus % 3 == 1){
                status[4][7] = 1;
            }else{
                status[6][1] = 1;
            }
            break;
        case 4:
            this->setType(4);
            switch (emStatus) {
                case 1:
//                    平衡左右
                    status[0][5]=status[4][1]=1;
                    break;
                case 2:
//                    平衡上下
                    status[6][3]=status[2][7]=1;
                    break;
                case 3:
                    status[0][3]=status[4][7]=1;
                    break;
                case 4:
                    status[6][1]=status[2][5]=1;
                case 5:
                    status[6][1]=status[4][1]=1;
                    break;
                case 6:
                    status[6][3]=status[0][3]=1;
                    break;
                case 7:
                    status[0][5]=status[2][5]=1;
                    break;
                case 8:
                    status[2][7]=status[4][7]=1;
                    break;
                case 9:
                    status[6][1]=status[6][3]=1;
                    break;
                case 10:
                    status[0][5]=status[0][3]=1;
                    break;
                case 11:
                    status[2][7]=status[2][5]=1;
                    break;
                case 12:
                    status[4][1]=status[4][7]=1;
                    break;
            }
    }

}

void TrafficLight::clock(int time) {
    switch (this->type) {
        case 3:
        if(wait[0][5] >= wait[4][7] >= wait[6][1]){

        }
            break;
    }
    changeStatus();
}
void TrafficLight::addWait(int from, int to) {
    wait[from][to]++;
}
void TrafficLight::subWait(int from, int to) {
    if(wait[from][to] > 0) {
        wait[from][to]--;
    }
}
bool TrafficLight::getStatus(int from, int to) {
    int from_site=-1, to_site=-1;
    for (int i = 0; i < 8; i++) {
        if (from == roadID[i]) {
            from_site = i;
        } else if (to == roadID[i]) {
            to_site = i;
        }
        if(i % 2 == 0 && roadID[i] == roadID[i+1] && roadID[i] != 0){
            cout << roadID[i] << " " << roadID[i+1 ] << endl;
            exit(1);
        }
    }
    if(from_site == -1 || to_site == -1){
        cout << RED << "TrafficLight::getStatus判断异常" << endl << "未找到对应的交通灯,程序出错被迫终止" << endl;
        cout << BLUE << from << " -> " << to << endl;
        for (int i = 0; i < 8; i++) {
            cout << roadID[i] << "-";
        }
        cout << endl;
        exit(1);
    }
    if(status[from_site][to_site] == 1){
        return true;
    }else if(from_site % 2 == to_site % 2){
        cout << RED << "从" << from_site << "方向转至" << to_site << "方向,通行状态" << status[from_site][to_site] << endl;
        cout << "出现不存在的状态" << endl;
        exit(1);
    }else{
        cout << RED << "从" << from_site << "方向转至" << to_site << "方向,通行状态" << status[from_site][to_site] << endl;
        return false;
    }
}
void TrafficLight::setType(int type) {
    this->type = type;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = -1;
        }
    }
    switch (type) {
        case 2:
            status[0][5] = status[4][1] = 1;
        case 3:
            status[0][7] = status[0][1] = status[4][1] = status[4][5] = status[6][7] = status[6][5] = 1;
            break;
        case 4:
            status[0][7] = status[0][1] = status[2][1] = status[2][3] = status[4][3] = status[4][5] = status[6][5] = status[6][7] = 1;
            break;
    }
}
TrafficLight::TrafficLight() {

}
